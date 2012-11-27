#ifndef WALLS_H
#define WALLS_H

#include "RigidBody.h"

class Walls: public RigidBody{
public:
	Walls(float x1Position, float x2Position, float y1Position, float y2Position);
	float x1Pos, x2Pos, y1Pos, y2Pos;
};

#endif