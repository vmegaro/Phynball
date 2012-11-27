#include "RigidBody.h"
#include "RungeKuttaODESolver.h"
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
	void setXAcc(const float &x, const float &v, float &a);
	void setYAcc(const float &x, const float &v, float &a);
	void setAngularAcc(const float &x, const float &v, float &a);
	void update(RigidBody *newRb);
	RigidBody * clone();

	RungeKuttaODESolver *solver;

protected:

	float width,heigth;

	void updateVertices();
};