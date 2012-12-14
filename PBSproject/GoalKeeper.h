#ifndef C_GoalKeeper
#define C_GoalKeeper
#include "RectangleWall.h"

class GoalKeeper: public RectangleWall{
public:
	GoalKeeper(Shape *_playBall);

	virtual void update(Shape *newSh);

	virtual GoalKeeper * clone();

	virtual void draw();

protected:
	RigidBody *playBall;
};

#endif