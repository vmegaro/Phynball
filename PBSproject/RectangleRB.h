#ifndef C_RectangleRB
#define C_RectangleRB
#include "RigidBody.h"
#include <vector>

using namespace std;

class RectangleRB: public RigidBody{
public:
	RectangleRB(float xPosition, float yPosition,
				float xVelocity, float yVelocity,
				float width, float height,
				float angularPosition, float angularVelocity,
				float m, float frictionCoeff, float gravityResistance,
				RungeKuttaODESolver *odeSolver);
	RigidBody * clone();

protected:

	float width,heigth;

	void updateVertices();
};

#endif