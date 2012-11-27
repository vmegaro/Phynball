#include "RigidBody.h"
#include "RungeKuttaODESolver.h"
#include <vector>

#define nVert 16

using namespace std;

class CircleRB: public RigidBody{
public:
	CircleRB(float xPosition, float yPosition,
			 float xVelocity, float yVelocity,
			 float radius,
			 float angularPosition, float angularVelocity,
			 float m, float frictionCoeff, float gravityResistance,
			 RungeKuttaODESolver *odeSolver);
	void setXAcc(const float &x, const float &v, float &a);
	void setYAcc(const float &x, const float &v, float &a);
	void setAngularAcc(const float &x, const float &v, float &a);
	void update(RigidBody *newRb);
	RigidBody * clone();

	RungeKuttaODESolver *solver;

protected:
	float r;
	void updateVertices();
};