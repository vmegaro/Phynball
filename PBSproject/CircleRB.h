#ifndef C_CircleRB
#define C_CircleRB
#include "RigidBody.h"
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
			 float elasticity,
			 RungeKuttaODESolver *odeSolver);
	CircleRB * clone();

	virtual bool containsShape(Shape *sh, vector<int> &resp, vector<int >&resq);

protected:
	float r;
	void updateVertices();
};

#endif