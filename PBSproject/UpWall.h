#ifndef C_UpWall
#define C_UpWall
#include "RectangleWall.h"
#include <vector>

using namespace std;

class UpWall: public RectangleWall{
public:
	UpWall();

	virtual void draw();

protected:

};

#endif