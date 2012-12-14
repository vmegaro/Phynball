#ifndef C_LeftWall
#define C_LeftWall
#include "RectangleWall.h"
#include <vector>

using namespace std;

class LeftWall: public RectangleWall{
public:
	LeftWall();

	virtual void draw();

protected:

};

#endif