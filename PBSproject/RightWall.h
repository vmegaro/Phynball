#ifndef C_RightWall
#define C_RightWall
#include "RectangleWall.h"
#include <vector>

using namespace std;

class RightWall: public RectangleWall{
public:
	RightWall();

	virtual void draw();

protected:

};

#endif