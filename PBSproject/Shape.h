#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include "Collision.h"

class Shape {
public:
	virtual Shape *clone() {return 0;};
	virtual void update(Shape *newSh) {};
	virtual void setCollisionResponse(Shape *collidingSh, const float &xCollision, const float &yCollision, const int &edgeIndex, Collision *collision) {};
	virtual void handleResponseImpulse(const float &nx, const float &ny,
										const float &rx, const float &ry,
										const float &impulseCoeff){};
	virtual void copyTo(Shape *newShape) {};

	std::vector<float> vertices;
	int nVertices;
	double color[3];
};


#endif
