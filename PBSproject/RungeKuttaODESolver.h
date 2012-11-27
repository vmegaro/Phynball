#ifndef C_RungeKuttaODESolver
#define C_RungeKuttaODESolver
#include "RigidBody.h"

class RungeKuttaODESolver {
public:
	RungeKuttaODESolver(float deltaT, int nIterations);
	void updateRigidBodyPositionAngleAndVelocities(RigidBody *rb, RigidBody *newRb);
	void updateRigidBodyPositionAngleAndVelocitiesWithCustomDt(RigidBody *rb, RigidBody *newRb, float customDt);
private:
	float h,hHalf,hSixth;
	float hc,hHalfc,hSixthc;
	int iterations;
};

#endif