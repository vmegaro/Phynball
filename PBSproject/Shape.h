#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>

class Shape {
public:
	virtual Shape *clone() {return 0;};
	virtual void update(Shape *newSh) {};
	virtual void handleCollision(Shape *newSh) {};
	virtual void handleResponseImpulse(const float &dvx, const float &dvy, const float &dva){};

	std::vector<float> vertices;
	int nVertices;
	double color[3];
};


#endif
