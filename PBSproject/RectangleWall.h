#ifndef C_RecWall
#define C_RecWall
#include "Wall.h"

class RectangleWall: public Wall{
public:
	RectangleWall(float xPosition, float yPosition,
				float recWidth, float recHeight,
				float angularPosition,
				float elasticity);
	virtual RectangleWall* clone();

protected:
	float width,heigth;
	float halfWidth, halfHeight;
	void updateVertices();

	float eastVecX, eastVecY, northVecX, northVecY, relength;
};

#endif