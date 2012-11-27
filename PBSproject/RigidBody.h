#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <vector>
#include "RungeKuttaODESolver.h"

class RigidBody {
public:
	virtual void setXAcc(const float &x, const float &v, float &a);
	virtual void setYAcc(const float &x, const float &v, float &a);
	virtual void setAngularAcc(const float &x, const float &v, float &a);
	virtual void update(RigidBody *newRb);
	virtual void handleCollision(RigidBody *rb);
	virtual void handleResponseImpulse(const float &dvx, const float &dvy);
	virtual RigidBody * clone() {return 0;};

	float xPos,yPos,angularPos;
	float xVel,yVel,angularVel;

	std::vector<float> vertices;
	int nVertices;

	double color[3];

	float Tx,Ty,Rx,Ry;

	RungeKuttaODESolver *solver;

protected:
	float mass, momentOfInertia;
	float oneOverMass, oneOverI;
	float gravityScale;
	float friction;

	virtual void updateVertices() {};
};

#endif