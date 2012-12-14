#include "RectangleMSO.h"
#include "Constants.h"

RectangleMSO::RectangleMSO(float xPosition, float yPosition,
				float xVelocity, float yVelocity,
				float width, float height,
				int nParticleX, int nParticleY,
				float m, float frictionCoeff, float gravityResistance,
				float springCoeff,
				RungeKuttaODESolver *odeSolver) {

					color[0] = 0.0;
					color[1] = 0.7;
					color[2] = 0.3;

					nVertices = 2*nParticleX+2*(nParticleY-2);
					nParticles = nParticleX*nParticleY;
					this->nParticleX = nParticleX;
					this->nParticleY = nParticleY;

					mass = m; oneOverMass = 1.0f/mass;
					friction = frictionCoeff; gravityScale = gravityResistance;
					solver = odeSolver;

					float dx = width/(nParticleX-1);
					float dy = width/(nParticleY-1);
					float halfWidth = width*0.5f;
					float halfHeight = height*0.5f;

					criticalRadius = sqrt(halfHeight*halfHeight+halfWidth*halfWidth);

					// Add all particles
					for(float xi = 0; xi < nParticleX; xi ++) {
						for(float yi = 0; yi < nParticleY; yi ++) {
							float x = xPosition-halfWidth+xi*dx;
							float y = yPosition-halfHeight+yi*dy;
							float r = 0.0f;//(float)rand()*5.0f/(float)RAND_MAX -2.5f;
							MassSpringParticle *part = new MassSpringParticle(x+r,y+r,
																				xVelocity,yVelocity,
																				mass/nParticles,frictionCoeff,gravityResistance,
																				1,dx,
																				odeSolver);
							particles.push_back(part);
						}
					}

					center = particles.at(nParticleX/2*nParticleY+nParticleY/2);

					MassSpringParticle *currentPart, *lastPart;

					// Contour used to draw
					// ********************

					// Contour: form SouthWest to NorthWest
					for(int i = 0; i < nParticleY; i++) {
						currentPart = particles.at(i);
						contour.push_back(currentPart);
						vertices.push_back(currentPart->xPos);
						vertices.push_back(currentPart->yPos);
					}

					// Contour: form NorthWest to NorthEast
					for(int i = 1; i < nParticleX; i++) {
						currentPart = particles.at((i+1)*nParticleY-1);
						contour.push_back(currentPart);
						vertices.push_back(currentPart->xPos);
						vertices.push_back(currentPart->yPos);
					}

					// Contour: form NorthEast to SouthEast
					for(int i = nParticleX*nParticleY - 2; i > (nParticleX-1)*nParticleY - 1; i--) {
						currentPart = particles.at(i);
						contour.push_back(currentPart);
						vertices.push_back(currentPart->xPos);
						vertices.push_back(currentPart->yPos);
					}

					// Contour: form SouthEast to SouthWest
					for(int i = (nParticleX-2); i > 0; i--) {
						currentPart = particles.at(i*nParticleY);
						contour.push_back(currentPart);
						vertices.push_back(currentPart->xPos);
						vertices.push_back(currentPart->yPos);
					}


					// Connect particles (with implicit springs)
					// *****************************************

					// Vertical springs
					for(int i = 0; i < nParticleX; i++) {
						lastPart = particles.at(i*nParticleY);
						for(int j = 1; j < nParticleY; j++) {
							currentPart = particles.at(i*nParticleY+j);
							// Add neighbors
							currentPart->neighbors.push_back(lastPart);
							lastPart->neighbors.push_back(currentPart);
							// Update
							lastPart = currentPart;
						}
					}

					// Horizontal springs
					for(int j = 0; j < nParticleY; j++) {
						lastPart = particles.at(j);
						for(int i = 1; i < nParticleX; i++) {
							currentPart = particles.at(i*nParticleY+j);
							// Add neighbors
							currentPart->neighbors.push_back(lastPart);
							lastPart->neighbors.push_back(currentPart);
							// Update
							lastPart = currentPart;
						}
					}

					MassSpringParticle *currentPartSWNE, *lastPartSWNE;
					MassSpringParticle *currentPartNWSE, *lastPartNWSE;

					// Diagonal (lowerLeft) springs
					for(int i = 1; i < nParticleY; i++) {
						lastPartNWSE = particles.at(i);
						lastPartSWNE = particles.at(i-1);
						for(int ii = 1, ij = i-1; ij >= 0 && ii < nParticleX; ii++, ij--) {
							currentPartNWSE = particles.at(ii*nParticleY+ij);
							currentPartSWNE = particles.at(ii*nParticleY+ij+1);
							// Add neighbors
							currentPartSWNE->neighbors.push_back(lastPartSWNE);
							lastPartSWNE->neighbors.push_back(currentPartSWNE);

							currentPartNWSE->neighbors.push_back(lastPartNWSE);
							lastPartNWSE->neighbors.push_back(currentPartNWSE);
							// Update
							lastPartNWSE = currentPartNWSE;
							lastPartSWNE = particles.at(ii*nParticleY+ij-1);
						}
					}

					// Diagonal (upperRight) springs
					for(int i = 1; i <= nParticleY-2; i++) {
						lastPartNWSE = particles.at((nParticleX-1)*nParticleY + i);
						lastPartSWNE = particles.at((nParticleX-1)*nParticleY + i + 1);
						for(int ii = i+1, ij = nParticleX-2; ii <= nParticleY-1; ii++, ij--) {
							currentPartNWSE = particles.at(ij*nParticleY+ii);
							currentPartSWNE = particles.at(ij*nParticleY+ii-1);
							// Add neighbors
							currentPartSWNE->neighbors.push_back(lastPartSWNE);
							lastPartSWNE->neighbors.push_back(currentPartSWNE);

							currentPartNWSE->neighbors.push_back(lastPartNWSE);
							lastPartNWSE->neighbors.push_back(currentPartNWSE);
							// Update
							lastPartNWSE = currentPartNWSE;
							lastPartSWNE = particles.at(ij*nParticleY+ii+1);
						}
					}

					e = 0.8f;
}

RectangleMSO * RectangleMSO::clone() {
	return this;
}

void RectangleMSO::draw() {
	//glBegin(GL_TRIANGLE_FAN);
	//	glTexCoord2f(0.5, 0.5);
	//	setVertexOpenGL(center->xPos,center->yPos);
	//	// Contour: form SouthWest to NorthWest
	//	//cout << "Drawing!" << nl;
	//	MassSpringParticle *currentPart;
	//	float dx = 1.0f/(nParticleX-1);
	//	float dy = 1.0f/(nParticleY-1);
	//	for(int i = 0; i < nParticleY; i++) {
	//		currentPart = contour.at(i);
	//		glTexCoord2f(0.0, dy*i); setVertexOpenGL(currentPart->xPos,currentPart->yPos);
	//		//cout << 0 << "-" << dy*i << "___" << currentPart->xPos << "-" <<currentPart->yPos << nl;
	//	}
	//	for(int i = nParticleY; i < nParticleY+nParticleX-1; i++) {
	//		currentPart = contour.at(i);
	//		glTexCoord2f((i-nParticleY+1)*dx, 1.0); setVertexOpenGL(currentPart->xPos,currentPart->yPos);
	//		//cout << (i-nParticleY+1)*dx << "-" << 1 << "___" << currentPart->xPos << "-" <<currentPart->yPos << nl;
	//	}
	//	for(int i = nParticleY+nParticleX-1; i < nParticleX+2*nParticleY-2; i++) {
	//		currentPart = contour.at(i);
	//		glTexCoord2f(1.0, 1.0-(i-nParticleY-nParticleX+2)*dy); setVertexOpenGL(currentPart->xPos,currentPart->yPos);
	//		//cout << 1 << "-" << 1.0-(i-nParticleY-nParticleX+2)*dy << "___" << currentPart->xPos << "-" <<currentPart->yPos << nl;
	//	}
	//	for(int i = nParticleX+2*nParticleY-2; i < contour.size(); i++) {
	//		currentPart = contour.at(i);
	//		glTexCoord2f(1.0-(i-nParticleX-2*nParticleY+3)*dx, 0.0); setVertexOpenGL(currentPart->xPos,currentPart->yPos);
	//		//cout << 1.0-(i-nParticleX-2*nParticleY+3)*dx << "-" << 0 << "___" << currentPart->xPos << "-" <<currentPart->yPos << nl;
	//	}
	//	glTexCoord2f(0.0, 0.0);
	//	setVertexOpenGL(particles.front()->xPos,particles.front()->yPos);
	//glEnd();
}

