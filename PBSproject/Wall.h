#ifndef C_Wall
#define C_Wall
#include "RigidBody.h"
#include <vector>

using namespace std;

class Wall: public RigidBody{
public:
	Wall() {};
	Wall(int type);
	Wall(vector<float> &vert,
		float elasticity);
	virtual void update(Shape *newSh);
	virtual Wall *clone();
	virtual void handleResponseImpulse(const float &nx, const float &ny,
										const float &rx, const float &ry,
										const float &impulseCoeff) {};

protected:
	void buildStandardWall();
};

#endif