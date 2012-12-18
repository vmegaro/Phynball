#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <vector>
#include "RungeKuttaODESolver.h"
#include "Shape.h"

using namespace std;
/*
Parent class describing rigid bodies. Subclasses are used to describe specific objects such as circles or rectangles.
It is a subclass of Shape.
*/
class RigidBody: public Shape {
public:
	//compute acceleration in x direction and store it in 'a'
	virtual void setXAcc(const float &x, const float &v, float &a);
	//compute acceleration in y direction and store it in 'a'
	virtual void setYAcc(const float &x, const float &v, float &a);
	//compute angular acceleration and store it in 'a'
	virtual void setAngularAcc(const float &x, const float &v, float &a);
	// update all parameters of the objects and put the new values in 'newSh'
	virtual void update(Shape *newSh);
	// create a 'collision' object regarding a collision occuring with vertex 'pointIndex' of 'collidingSh' on edge 'edgeIndex' of 'this'
	virtual void setCollisionResponse(Shape *collidingSh, const int &pointIndex, const int &edgeIndex, Collision *collision);
	// update the state of 'this' after a collision occurs on vertices in 'cv' with an impulse coefficient of 'impulseCoeff'
	// along the vector given by 'nx' and 'ny'. 'rx' and 'ry' are distances used to sompute the influence on the rotation of 'this'
	virtual void handleResponseImpulse(const float &nx, const float &ny, const float &rx, const float &ry,
						const std::vector<int> &cv, const float &impulseCoeff);
	virtual void copyTo(Shape *newShape);
	virtual RigidBody * clone() {return 0;};
	int nature(){return 1;};

	float Tx,Ty,Rx,Ry;

	float e;
	float mass;
	float oneOverMass;

	RungeKuttaODESolver *solver;

	virtual bool containsShape(Shape *sh, vector<int> &resp, vector<int >&resq) {return 0;};
	//coefficient to control of influence of gravity
	float gravityScale;

protected:
	float momentOfInertia;
	float oneOverI;
	float friction;

	virtual void updateVertices() {};
};

#endif
