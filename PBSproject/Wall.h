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

protected:
	void buildStandardWall();
};

#endif