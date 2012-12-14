#include "RectangleRB.h"
#include <cmath>
#include "Constants.h"

enum VerticesPositions
{
	nex = 0,
	ney,
	nwx,
	nwy,
	swx,
	swy,
	sex,
	sey,
	NUM_Vertices
};

RectangleRB::RectangleRB(float xPosition, float yPosition,
						 float xVelocity, float yVelocity,
						 float recWidth, float recHeight,
						 float angularPosition, float angularVelocity,
						 float m, float frictionCoeff, float gravityResistance,
						 float elasticity,
						 RungeKuttaODESolver *odeSolver) {

							 xPos = xPosition; yPos = yPosition;
							 xVel = xVelocity; yVel = yVelocity;
							 width = recWidth; heigth = recHeight;
							 halfWidth = width*0.5f; halfHeight = heigth*0.5f;
							 angularPos = angularPosition; angularVel = angularVelocity;
							 mass = m; friction = frictionCoeff; gravityScale = gravityResistance;
							 e = elasticity;
							 momentOfInertia = mass*(width*width+heigth*heigth)/12.0f;
							 oneOverMass = 1.0f/mass; oneOverI = 1.0f/momentOfInertia;
							 Tx = 0.0f; Ty = 0.0f; Rx = 0.0f; Ry = 0.0f;
							 solver = odeSolver;

							 nVertices = NUM_Vertices/2;
							 vertices = vector<float>(nVertices*2,0.0f);
							 updateVertices();

							 color[0] = 0.8;
							 color[1] = 0.6;
							 color[2] = 0.1;

							 criticalRadius = sqrt(halfWidth*halfWidth+halfHeight*halfHeight);
}

RectangleRB * RectangleRB::clone() {
	return new RectangleRB(
		xPos, yPos,
		xVel,yVel,
		width, heigth,
		angularPos, angularVel,
		mass, friction, gravityScale,
		e,
		solver);
}

void RectangleRB::updateVertices() {
	eastVecX = cos(angularPos)*halfWidth; // deltaX
	eastVecY = sin(angularPos)*halfWidth; // deltaY

	relength = halfHeight/sqrt(eastVecX*eastVecX+eastVecY*eastVecY);

	northVecX = -eastVecY*relength;
	northVecY = eastVecX*relength;

	vertices.at(nex) = xPos + eastVecX + northVecX;
	vertices.at(ney) = yPos + eastVecY + northVecY;
	vertices.at(sex) = xPos + eastVecX - northVecX;
	vertices.at(sey) = yPos + eastVecY - northVecY;
	vertices.at(nwx) = xPos - eastVecX + northVecX;
	vertices.at(nwy) = yPos - eastVecY + northVecY;
	vertices.at(swx) = xPos - eastVecX - northVecX;
	vertices.at(swy) = yPos - eastVecY - northVecY;
}

void RectangleRB::draw() {
	glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0); setVertexOpenGL(vertices.at(0),vertices.at(1));
		glTexCoord2f(0.0, 1.0); setVertexOpenGL(vertices.at(2),vertices.at(3));
		glTexCoord2f(0.0, 0.0); setVertexOpenGL(vertices.at(4),vertices.at(5));
		glTexCoord2f(1.0, 0.0); setVertexOpenGL(vertices.at(6),vertices.at(7));
	glEnd();
}

bool RectangleRB::containsShape(Shape *sh, vector<int> &resp, vector<int >&resq) {
	for(int i = 0; i < sh->nVertices; i++) {
		float Mx = sh->vertices.at(2*i);
		float My = sh->vertices.at(2*i+1);

		float AMx = vertices.at(0)-Mx;
		float AMy = vertices.at(1)-My;
		float ABx = vertices.at(0) - vertices.at(2);
		float ABy = vertices.at(1) - vertices.at(3);
		float ADx = vertices.at(0) - vertices.at(6);
		float ADy = vertices.at(1) - vertices.at(7);

		float AMdotAB = AMx*ABx+AMy*ABy;
		float ABdotAB = ABx*ABx+ABy*ABy;
		float AMdotAD = AMx*ADx+AMy*ADy;
		float ADdotAD = ADx*ADx+ADy*ADy;

		if(0 < AMdotAB && AMdotAB < ABdotAB &&
			0 < AMdotAD && AMdotAD < ADdotAD) {
				
				// Point index inside rect
				resq.push_back(i);

				// Anchor edge 
				for(int k = 0; k < sh->nVertices && resp.empty(); k++) {
					float Ax = sh->vertices.at((2*(i+k))%(2*sh->nVertices));
					float Ay = sh->vertices.at((2*(i+k)+1)%(2*sh->nVertices));
					float Bx = sh->vertices.at((2*(i+k+1))%(2*sh->nVertices));
					float By = sh->vertices.at((2*(i+k+1)+1)%(2*sh->nVertices));

					// Edge detection for normal computation
					for(int j = 0; j < nVertices; j++) {
						float Cx = vertices.at(2*j);
						float Cy = vertices.at(2*j+1);
						float Dx = vertices.at((2*j+2)%(nVertices*2));
						float Dy = vertices.at((2*j+3)%(nVertices*2));

						float x00 = Ax, y00 = Ay,
							  x01 = Bx-Ax, y01 = By-Ay,
							  x10 = Cx, y10 = Cy,
							  x11 = Dx-Cx, y11 = Dy-Cy;

						float d = (x11*y01 - x01*y11);
						if (d == 0) continue;
						float oneOverd = 1.0f/d;

						float s = oneOverd*((x00-x10)*y01 - (y00-y10)*x01);
						float t = -oneOverd*(-(x00-x10)*y11 + (y00-y10)*x11);

						if(t >= 0.0f && t <= 1.0f &&
							s >= 0.0f && s <= 1.0f) {
							resp.push_back(j);resp.push_back(j+1);
							break;
						}
					}
				}

				return resp.size();
		}
	}

	return false;
}