#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <vector>
#include "RungeKuttaODESolver.h"
#include "Shape.h"

using namespace std;

class RigidBody: public Shape {
public:
	virtual void setXAcc(const float &x, const float &v, float &a);
	virtual void setYAcc(const float &x, const float &v, float &a);
	virtual void setAngularAcc(const float &x, const float &v, float &a);
	virtual void update(Shape *newSh);
	virtual void setCollisionResponse(Shape *collidingSh, const int &pointIndex, const int &edgeIndex, Collision *collision);
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

	float gravityScale;

protected:
	float momentOfInertia;
	float oneOverI;
	float friction;

	virtual void updateVertices() {};
};

#endif