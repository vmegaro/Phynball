#ifndef C_Collision
#define C_Collision

#include <vector>

class Shape;
/*
this objects store all shapes and values needed to solve one collision 
between two objects and one method to ask them to resolve the collision.
*/
class Collision {
public:
	Collision();
	Collision(Shape *_shapeA);
	Collision(Shape *_shapeA, Shape *_shapeB,
				float _nx, float _ny,
				float _rxa, float _rya,
				float _rxb, float _ryb,
				float _j);

	Shape *shapeA;
	Shape *shapeB;
	// coordinates of the normal where forces and impulses should be applied
	float nx,ny;
	float rxa, rya;
	//vector of vertices concerned by the collision of 'shapeA' 
	std::vector<int> cva;
	float rxb, ryb;
	//vector of vertices concerned by the collision of 'shapeB'
	std::vector<int> cvb;
	//impluse coefficient
	float j;
	//state if the collision has been resolved or not
	bool resolved;
	//ask both objects to make the necessary changes
	void resolve();

protected:
};

#endif
