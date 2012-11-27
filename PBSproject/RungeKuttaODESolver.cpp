#include "RungeKuttaODESolver.h"
#include <iostream>

using namespace std;

float kx1,kx2,kx3,kx4;
float kv1,kv2,kv3,kv4;

float h,hHalf,hSixth;

RungeKuttaODESolver::RungeKuttaODESolver(float deltaT, int nIterations) {
	h = deltaT;
	hHalf = h*0.5f;
	hSixth = h/6.0f;
	iterations = nIterations;
}

void RungeKuttaODESolver::updateRigidBodyPositionAngleAndVelocities(RigidBody *rb, RigidBody *newRb) {
	//X position and velocity
	cout << rb->xPos << ' ' << rb->yPos << '\n';

	kx1 = rb->xVel;
	rb->setXAcc(rb->xPos,rb->xVel,kv1);
	kx2 = rb->xVel + kv1*hHalf;
	rb->setXAcc(rb->xPos+kx1*hHalf,kx2,kv2);
	kx3 = rb->xVel + kv2*hHalf;
	rb->setXAcc(rb->xPos+kx2*hHalf,kx3,kv3);
	kx4 = rb->xVel + kv3*h;
	rb->setXAcc(rb->xPos+kx3*h,kx4,kv4);

	newRb->xPos = rb->xPos + hSixth*(kx1+2.0f*kx2+2.0f*kx3+kx4);
	newRb->xVel = rb->xVel + hSixth*(kv1+2.0f*kv2+2.0f*kv3+kv4);

	for (int i = 1; i < iterations; i++)
	{
		kx1 = newRb->xVel;
		newRb->setXAcc(newRb->xPos,newRb->xVel,kv1);
		kx2 = newRb->xVel + kv1*hHalf;
		newRb->setXAcc(newRb->xPos+kx1*hHalf,kx2,kv2);
		kx3 = newRb->xVel + kv2*hHalf;
		newRb->setXAcc(newRb->xPos+kx2*hHalf,kx3,kv3);
		kx4 = newRb->xVel + kv3*h;
		newRb->setXAcc(newRb->xPos+kx3*h,kx4,kv4);

		newRb->xPos = newRb->xPos + hSixth*(kx1+2.0f*kx2+2.0f*kx3+kx4);
		newRb->xVel = newRb->xVel + hSixth*(kv1+2.0f*kv2+2.0f*kv3+kv4);
	}

	cout << newRb->xPos << " " << newRb->yPos << "\n";

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
	newRb->yVel = rb->yVel + hSixth*(kv1+2.0f*kv2+2.0f*kv3+kv4);

	for (int i = 1; i < iterations; i++)
	{
		kx1 = newRb->yVel;
		rb->setYAcc(newRb->yPos,newRb->yVel,kv1);
		kx2 = newRb->yVel + kv1*hHalf;
		rb->setYAcc(newRb->yPos+kx1*hHalf,kx2,kv2);
		kx3 = newRb->yVel + kv2*hHalf;
		rb->setYAcc(newRb->yPos+kx2*hHalf,kx3,kv3);
		kx4 = newRb->yVel + kv3*h;
		rb->setYAcc(newRb->yPos+kx3*h,kx4,kv4);

		newRb->yPos = newRb->yPos + hSixth*(kx1+2.0f*kx2+2.0f*kx3+kx4);
		newRb->yVel = newRb->yVel + hSixth*(kv1+2.0f*kv2+2.0f*kv3+kv4);
	}

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
	newRb->angularVel = rb->angularVel + hSixth*(kv1+2.0f*kv2+2.0f*kv3+kv4);

	for (int i = 1; i < iterations; i++)
	{
		kx1 = newRb->angularVel;
		rb->setAngularAcc(newRb->angularPos,newRb->angularVel,kv1);
		kx2 = newRb->angularVel + kv1*hHalf;
		rb->setAngularAcc(newRb->angularPos+kx1*hHalf,kx2,kv2);
		kx3 = newRb->angularVel + kv2*hHalf;
		rb->setAngularAcc(newRb->angularPos+kx2*hHalf,kx3,kv3);
		kx4 = newRb->angularVel + kv3*h;
		rb->setAngularAcc(newRb->angularPos+kx3*h,kx4,kv4);

		newRb->angularPos = newRb->angularPos + hSixth*(kx1+2.0f*kx2+2.0f*kx3+kx4);
		newRb->angularVel = newRb->angularVel + hSixth*(kv1+2.0f*kv2+2.0f*kv3+kv4);
	}
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