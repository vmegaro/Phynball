#ifndef C_Player
#define C_Player
#include "RectangleRB.h"

class Player: public RectangleRB{
public:
	Player(float xPosition, float yPosition);

	virtual void update(Shape *newSh);

	virtual Player * clone();

	virtual void draw();

protected:
};

#endif