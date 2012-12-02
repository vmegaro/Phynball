#ifndef C_Pale
#define C_Pale
#include "RigidBody.h"
#include <vector>

using namespace std;

class Pale: public RigidBody {
public:
	Pale(int position, RungeKuttaODESolver *odeSolver);
	virtual void update(Shape *newSh);
	virtual Pale *clone();

	void setGoUp();
	void setGoDown();

private:
	float minAngle, maxAngle;
	float upAngularVel;

	void updateVertices();

	float longVecX, longVecY;
	float shortVecX, shortVecY;
	float heightVecX, heightVecY;
	float relength;
};

#endif