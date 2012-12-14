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
				float elasticity,
				RungeKuttaODESolver *odeSolver);
	RectangleRB * clone();

	virtual bool containsShape(Shape *sh, vector<int> &resp, vector<int >&resq);

	virtual void draw();

protected:

	float width,heigth;
	float halfWidth, halfHeight;
	void updateVertices();

	float eastVecX, eastVecY, northVecX, northVecY, relength;
};

#endif