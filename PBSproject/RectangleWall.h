#ifndef C_RecWall
#define C_RecWall
#include "Wall.h"

class RectangleWall: public Wall{
public:
	RectangleWall() {};
	RectangleWall(float xPosition, float yPosition,
				float recWidth, float recHeight,
				float angularPosition,
				float elasticity);
	virtual RectangleWall* clone();

	virtual bool containsShape(Shape *sh, vector<int> &resp, vector<int >&resq);

	virtual void draw();

protected:
	float width,heigth;
	float halfWidth, halfHeight;
	void updateVertices();

	float eastVecX, eastVecY, northVecX, northVecY, relength;
};

#endif