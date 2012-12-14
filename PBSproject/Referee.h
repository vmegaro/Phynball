#ifndef C_Referee
#define C_Referee
#include "RectangleRB.h"

class Referee: public RectangleRB{
public:
	Referee(Shape *_playBall);

	virtual void update(Shape *newSh);

	virtual Referee * clone();

	virtual void draw();

protected:
	RigidBody *playBall;
};

#endif