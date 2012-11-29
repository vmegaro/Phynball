#include "RigidBody.h"
#include "Constants.h"
#include <cmath>

void RigidBody::setXAcc(const float &x, const float &v, float &a) {
	a = (Tx - friction*xVel)*oneOverMass;
}

void RigidBody::setYAcc(const float &x, const float &v, float &a){
	a = (Ty - friction*yVel)*oneOverMass - gravityScale*g;
}

void RigidBody::setAngularAcc(const float &x, const float &v, float &a){
	a = (Rx*Ty-Ry*Tx - friction*angularVel)*oneOverI;
}

void RigidBody::update(Shape *newSh){
	RigidBody *newRb = (RigidBody *)newSh;
	solver->updateRigidBodyPositionAngleAndVelocities(this, newRb);
	updateVertices();	
}

float deltaVx, deltaVy, deltaVa, impulseCoeff;
float nx,ny,r;
float vabx, vaby;
float rxa, rya, rxb, ryb;
float jOverMass;
void RigidBody::handleCollision(RigidBody *rb, const float &xCollision, const float &yCollision, const int &edgeIndex){
	// Compute relative velocity
	rxa = xCollision - rb->xPos;
	rya = yCollision - rb->yPos;
	rxb = xCollision - xPos;
	ryb = yCollision - yPos;

	vabx = rb->xVel - (rb->angularVel*rya) - (xVel - (angularVel*ryb));
	vaby = rb->yVel + (rb->angularVel*rxa) - (yVel + (angularVel*rxb));

	// compute unit normal: nx = dy, ny = -dx
	nx = vertices.at((edgeIndex+1)*2+1)-vertices.at((edgeIndex)*2+1);
	ny = -vertices.at((edgeIndex+1)*2)-vertices.at((edgeIndex)*2);
	r = sqrt(nx*nx+ny*ny);
	nx /= r;
	ny /= r;

	// Compute j (impulse coeff)
	impulseCoeff = -((1.0f+e)*(vabx*nx+vaby*ny))/
		((rb->oneOverMass)+oneOverMass+(rxa*ny-nx*rya)*(rxa*ny-nx*rya)*(rb->oneOverI)+(rxb*ny-nx*ryb)*(rxb*ny-nx*ryb)*oneOverI);

	// Compute delta velocities
	jOverMass = impulseCoeff*oneOverMass;
	deltaVx = -jOverMass*nx;
	deltaVy = -jOverMass*ny;
	deltaVa = -(rxb*ny-nx*ryb)*impulseCoeff*oneOverI;

	// Send inverse impulse to colliding object
	rb->handleResponseImpulse(-deltaVx,-deltaVy,-deltaVa);
}

void RigidBody::handleResponseImpulse(const float &dvx, const float &dvy, const float &dva){
	xVel += dvx;
	yVel += dvy;
	angularVel += dva;
}