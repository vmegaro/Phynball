#ifndef C_Collision
#define C_Collision
class Shape;

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
	float nx,ny;
	float rxa, rya;
	float rxb, ryb;
	float j;
	bool resolved;

	void resolve();

protected:
};

#endif