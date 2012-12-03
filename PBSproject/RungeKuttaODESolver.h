#ifndef C_RKODES_H
#define C_RKODES_H
class RigidBody;

class RungeKuttaODESolver {
public:
	RungeKuttaODESolver(float deltaT);
	void updateRigidBodyPositionAngleAndVelocities(RigidBody *rb, RigidBody *newRb);
	void updateRigidBodyPositionAngleAndVelocitiesWithCustomDt(RigidBody *rb, RigidBody *newRb, float customDt);
private:
	float h,hHalf,hSixth;
	float hc,hHalfc,hSixthc;

	float kx1,kx2,kx3,kx4;
	float kv1,kv2,kv3,kv4;

	float finalValue;

};

#endif