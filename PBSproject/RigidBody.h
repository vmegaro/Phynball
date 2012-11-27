#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <vector>

class RigidBody {
public:
	virtual void setXAcc(const float &x, const float &v, float &a){};
	virtual void setYAcc(const float &x, const float &v, float &a){};
	virtual void setAngularAcc(const float &x, const float &v, float &a){};
	virtual void update(RigidBody *newRb){};
	virtual RigidBody * clone() {return 0;};

	float xPos,yPos,angularPos;
	float xVel,yVel,angularVel;

	std::vector<float> vertices;
	int nVertices;

	double color[3];

	float Tx,Ty,Rx,Ry;

protected:
	float mass, momentOfInertia;
	float oneOverMass, oneOverI;
	float gravityScale;
	float friction;
};

#endif