#include "RungeKuttaODESolver.h"
#include "RigidBody.h"
#include "Constants.h"
#include <math.h>
#include <iostream>

using namespace std;

float sign(float f) {
	return (float*)(f > 0) - (float*)(f < 0);
}


RungeKuttaODESolver::RungeKuttaODESolver(float deltaT) {
	h = deltaT;
	hHalf = h*0.5f;
	hSixth = h/6.0f;
}

void RungeKuttaODESolver::updateRigidBodyPositionAngleAndVelocities(RigidBody *rb, RigidBody *newRb) {

	//X position and velocity
	//cout << rb->yVel << endl;

	kx1 = rb->xVel;
	rb->setXAcc(rb->xPos,rb->xVel,kv1);
	kx2 = rb->xVel + kv1*hHalf;
	rb->setXAcc(rb->xPos+kx1*hHalf,kx2,kv2);
	kx3 = rb->xVel + kv2*hHalf;
	rb->setXAcc(rb->xPos+kx2*hHalf,kx3,kv3);
	kx4 = rb->xVel + kv3*h;
	rb->setXAcc(rb->xPos+kx3*h,kx4,kv4);

	newRb->xPos = rb->xPos + hSixth*(kx1+2.0f*kx2+2.0f*kx3+kx4);
	finalValue = rb->xVel + hSixth*(kv1+2.0f*kv2+2.0f*kv3+kv4);
	float s = sign(finalValue);
	if(s*finalValue > maxRigidVel) finalValue = s*maxRigidVel;
	else if(s*finalValue < minRigidVel) finalValue = 0.0f;
	newRb->xVel = finalValue;

	// Y position and velocity

	kx1 = rb->yVel;
	rb->setYAcc(rb->yPos,rb->yVel,kv1);
	kx2 = rb->yVel + kv1*hHalf;
	rb->setYAcc(rb->yPos+kx1*hHalf,kx2,kv2);
	kx3 = rb->yVel + kv2*hHalf;
	rb->setYAcc(rb->yPos+kx2*hHalf,kx3,kv3);
	kx4 = rb->yVel + kv3*h;
	rb->setYAcc(rb->yPos+kx3*h,kx4,kv4);

	newRb->yPos = rb->yPos + hSixth*(kx1+2.0f*kx2+2.0f*kx3+kx4);
	finalValue = rb->yVel + hSixth*(kv1+2.0f*kv2+2.0f*kv3+kv4);
	s = sign(finalValue);
	if(s*finalValue > maxRigidVel) finalValue = s*maxRigidVel;
	else if(s*finalValue < minRigidVel) finalValue = 0.0f;
	newRb->yVel = finalValue;

	// Angular position and velocity
	kx1 = rb->angularVel;
	rb->setAngularAcc(rb->angularPos,rb->angularVel,kv1);
	kx2 = rb->angularVel + kv1*hHalf;
	rb->setAngularAcc(rb->angularPos+kx1*hHalf,kx2,kv2);
	kx3 = rb->angularVel + kv2*hHalf;
	rb->setAngularAcc(rb->angularPos+kx2*hHalf,kx3,kv3);
	kx4 = rb->angularVel + kv3*h;
	rb->setAngularAcc(rb->angularPos+kx3*h,kx4,kv4);

	newRb->angularPos = rb->angularPos + hSixth*(kx1+2.0f*kx2+2.0f*kx3+kx4);
	finalValue = rb->angularVel + hSixth*(kv1+2.0f*kv2+2.0f*kv3+kv4);
	s = sign(finalValue);
	if(s*finalValue > maxRigidAngularVel) finalValue = s*maxRigidAngularVel;
	else if(s*finalValue < minRigidAngularVel) finalValue = 0.0f;
	newRb->angularVel = finalValue;
}

void RungeKuttaODESolver::updateRigidBodyPositionAngleAndVelocitiesWithCustomDt(RigidBody *rb, RigidBody *newRb, float customDt) {

	hc = customDt;
	hHalfc = hc*0.5f;
	hSixthc = hc/6.0f;

	kx1 = rb->xVel;
	rb->setXAcc(rb->xPos,rb->xVel,kv1);
	kx2 = rb->xVel + kv1*hHalfc;
	rb->setXAcc(rb->xPos+kx1*hHalfc,kx2,kv2);
	kx3 = rb->xVel + kv2*hHalfc;
	rb->setXAcc(rb->xPos+kx2*hHalfc,kx3,kv3);
	kx4 = rb->xVel + kv3*hc;
	rb->setXAcc(rb->xPos+kx3*hc,kx4,kv4);

	newRb->xPos = rb->xPos + hSixthc*(kx1+2.0f*kx2+2.0f*kx3+kx4);
	newRb->xVel = rb->xVel + hSixthc*(kv1+2.0f*kv2+2.0f*kv3+kv4);

	// Y position and velocity

	kx1 = rb->yVel;
	rb->setYAcc(rb->yPos,rb->yVel,kv1);
	kx2 = rb->yVel + kv1*hHalfc;
	rb->setYAcc(rb->yPos+kx1*hHalfc,kx2,kv2);
	kx3 = rb->yVel + kv2*hHalfc;
	rb->setYAcc(rb->yPos+kx2*hHalfc,kx3,kv3);
	kx4 = rb->yVel + kv3*hc;
	rb->setYAcc(rb->yPos+kx3*hc,kx4,kv4);

	newRb->yPos = rb->yPos + hSixthc*(kx1+2.0f*kx2+2.0f*kx3+kx4);
	newRb->yVel = rb->yVel + hSixthc*(kv1+2.0f*kv2+2.0f*kv3+kv4);

	// Angular position and velocity
	kx1 = rb->angularVel;
	rb->setAngularAcc(rb->angularPos,rb->angularVel,kv1);
	kx2 = rb->angularVel + kv1*hHalfc;
	rb->setAngularAcc(rb->angularPos+kx1*hHalfc,kx2,kv2);
	kx3 = rb->angularVel + kv2*hHalfc;
	rb->setAngularAcc(rb->angularPos+kx2*hHalfc,kx3,kv3);
	kx4 = rb->angularVel + kv3*hc;
	rb->setAngularAcc(rb->angularPos+kx3*hc,kx4,kv4);

	newRb->angularPos = rb->angularPos + hSixthc*(kx1+2.0f*kx2+2.0f*kx3+kx4);
	newRb->angularVel = rb->angularVel + hSixthc*(kv1+2.0f*kv2+2.0f*kv3+kv4);
}