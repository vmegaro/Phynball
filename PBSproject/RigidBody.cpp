#include "RigidBody.h"
#include "Constants.h"

void RigidBody::setXAcc(const float &x, const float &v, float &a) {
	a = (Tx - friction*xVel)*oneOverMass;
}

void RigidBody::setYAcc(const float &x, const float &v, float &a){
	a = (Ty - friction*yVel)*oneOverMass - gravityScale*g;
}

void RigidBody::setAngularAcc(const float &x, const float &v, float &a){
	a = (Rx*Ty-Ry*Tx - friction*angularVel)*oneOverI;
}

void RigidBody::update(RigidBody *newRb){
	solver->updateRigidBodyPositionAngleAndVelocities(this, newRb);
	updateVertices();	
}

void RigidBody::handleCollision(RigidBody *rb){

}

void RigidBody::handleResponseImpulse(const float &dvx, const float &dvy){
	xVel += dvx;
	yVel += dvy;
}