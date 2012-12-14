#ifndef C_TriWall
#define C_TriWall
#include "Wall.h"

class TriangleWall: public Wall{
public:
	TriangleWall(float p1x, float p1y,
				float p2x, float p2y,
				float p3x, float p3y,
				float elasticity);
	virtual TriangleWall* clone();

	virtual bool containsShape(Shape *sh, vector<int> &resp, vector<int >&resq);

protected:
};

#endif