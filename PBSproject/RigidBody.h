#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <vector>
#include "RungeKuttaODESolver.h"
#include "Shape.h"

class RigidBody: public Shape {
public:
	virtual void setXAcc(const float &x, const float &v, float &a);
	virtual void setYAcc(const float &x, const float &v, float &a);
	virtual void setAngularAcc(const float &x, const float &v, float &a);
	virtual void update(Shape *newSh);
	virtual void handleCollision(RigidBody *rb, const float &xCollision, const float &yCollision, const int &edgeIndex);
	virtual void handleResponseImpulse(const float &dvx, const float &dvy, const float &dva);
	virtual RigidBody * clone() {return 0;};

	float xPos,yPos,angularPos;
	float xVel,yVel,angularVel;

	float Tx,Ty,Rx,Ry;

	RungeKuttaODESolver *solver;

protected:
	float mass, momentOfInertia;
	float oneOverMass, oneOverI;
	float e;
	float gravityScale;
	float friction;

	virtual void updateVertices() {};
};

#endif