#ifndef C_Net
#define C_Net
#include "DeformableObject.h"

/*
Used to represent the net to hit with the ball. This object includes texturing.
*/
class Net: public DeformableObject{
public:
	Net();

	virtual void update(Shape *newSh);

	virtual Net * clone();

	virtual void draw();

protected:
};

#endif
