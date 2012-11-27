#include "CircleRB.h"
#include <cmath>
#include "Constants.h"

CircleRB::CircleRB(float xPosition, float yPosition,
						 float xVelocity, float yVelocity,
						 float radius,
						 float angularPosition, float angularVelocity,
						 float m, float frictionCoeff, float gravityResistance,
						 RungeKuttaODESolver *odeSolver) {

							 xPos = xPosition; yPos = yPosition;
							 xVel = xVelocity; yVel = yVelocity;
							 angularPos = angularPosition; angularVel = angularVelocity;
							 mass = m; friction = frictionCoeff; gravityScale = gravityResistance;
							 momentOfInertia = mass*(2.0f*r*r)/12.0f;
							 oneOverMass = 1.0f/mass; oneOverI = 1.0f/momentOfInertia;
							 Tx = 0.0f; Ty = 0.0f; Rx = 0.0f; Ry = 0.0f;
							 solver = odeSolver;

							 r = radius;

							 nVertices = nVert+1;
							 vertices = vector<float>(nVertices*2,0.0f);
							 updateVertices();

							 color[0] = 0.1;
							 color[1] = 0.6;
							 color[2] = 0.8;
}

RigidBody * CircleRB::clone() {
	return new CircleRB(
		xPos, yPos,
		xVel,yVel,
		r,
		angularPos, angularVel,
		mass, friction, gravityScale,
		solver);
}

void CircleRB::setXAcc(const float &x, const float &v, float &a) {
	a = (Tx - friction*xVel)*oneOverMass;
}

void CircleRB::setYAcc(const float &x, const float &v, float &a){
	a = (Ty - friction*yVel)*oneOverMass - gravityScale*g;
}

void CircleRB::setAngularAcc(const float &x, const float &v, float &a){
	a = (Rx*Ty-Ry*Tx - friction*angularVel)*oneOverI;
}

void CircleRB::update(RigidBody *newRb){
	solver->updateRigidBodyPositionAngleAndVelocities(this, newRb);
	updateVertices();

	// Debug
	/*Rx = vertices.at(nwx)-xPos;
	Ry = vertices.at(nwy)-yPos;
	float r2 = vertices.at(nwx)*vertices.at(nwx)+vertices.at(nwy)*vertices.at(nwy);
	Tx = -vertices.at(nwx)/r2;
	Ty = -vertices.at(nwy)/r2;*/
	
	
}

float s, t;
void CircleRB::updateVertices() {
	float s = (float)(2*M_PI/nVert);
	float t = angularPos;
	for(int k = 0; k < nVert; t += s, k++){
		vertices.at(2*k) = xPos + r*cos(t);
		vertices.at(2*k+1) = yPos + r*sin(t);
	}
	vertices.at(2*nVert) = xPos;
	vertices.at(2*nVert+1) = yPos;
}