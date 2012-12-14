#include "CircleRB.h"
#include <cmath>
#include "Constants.h"

CircleRB::CircleRB(float xPosition, float yPosition,
						 float xVelocity, float yVelocity,
						 float radius,
						 float angularPosition, float angularVelocity,
						 float m, float frictionCoeff, float gravityResistance,
						 float elasticity,
						 RungeKuttaODESolver *odeSolver) {

							 r = radius;
							 criticalRadius = radius;

							 xPos = xPosition; yPos = yPosition;
							 xVel = xVelocity; yVel = yVelocity;
							 angularPos = angularPosition; angularVel = angularVelocity;
							 mass = m; friction = frictionCoeff; gravityScale = gravityResistance;
							 e = elasticity;
							 momentOfInertia = mass*(2.0f*r*r)/12.0f;
							 oneOverMass = 1.0f/mass; oneOverI = 1.0f/momentOfInertia;
							 Tx = 0.0f; Ty = 0.0f; Rx = 0.0f; Ry = 0.0f;
							 solver = odeSolver;

							 nVertices = nVert+1;
							 vertices = vector<float>(nVertices*2,0.0f);
							 updateVertices();

							 color[0] = 0.1;
							 color[1] = 0.6;
							 color[2] = 0.8;
}

CircleRB * CircleRB::clone() {
	return new CircleRB(
		xPos, yPos,
		xVel,yVel,
		r,
		angularPos, angularVel,
		mass, friction, gravityScale,
		e,
		solver);
}

float s, t;
void CircleRB::updateVertices() {
	float s = (float)(2*M_PI/nVert);
	float t = angularPos;
	for(int k = 0; k < nVertices; t += s, k++){
		vertices.at(2*k) = xPos + r*cos(t);
		vertices.at(2*k+1) = yPos + r*sin(t);
	}
	/*vertices.at(2*nVert) = xPos + r*cos(angularPos);
	vertices.at(2*nVert+1) = yPos + r*sin(angularPos);*/
}

bool CircleRB::containsShape(Shape *sh, vector<int> &resp, vector<int >&resq) {
	for(int i = 0; i < sh->nVertices; i++) {
		float Mx = sh->vertices.at(2*i);
		float My = sh->vertices.at(2*i+1);

		if((Mx-xPos)*(Mx-xPos)+(My-yPos)*(My-yPos) < r*r) {
			// Point index inside circle
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
