#ifndef C_RKODES_H
#define C_RKODES_H
class RigidBody;

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