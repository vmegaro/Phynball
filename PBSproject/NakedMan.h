#ifndef C_NakedMan
#define C_NakedMan
#include "RectangleRB.h"

class NakedMan: public RectangleRB{
public:
	NakedMan();

	virtual void update(Shape *newSh);

	virtual NakedMan * clone();

	virtual void draw();

protected:
};

#endif