#ifndef C_MassSpringObject
#define C_MassSpringObject
#include <vector>
#include "RungeKuttaODESolver.h"
#include "Shape.h"
#include "Constants.h"
#include "MassSpringParticle.h"

using namespace std;

class MassSpringObject: public Shape {
public:
	MassSpringObject(){};
	virtual void update(Shape *newSh);
	virtual void setCollisionResponse(Shape *collidingSh, const int &pointIndex, const int &edgeIndex, Collision *collision);
	virtual void handleResponseImpulse(const float &nx, const float &ny, const float &rx, const float &ry,
						const std::vector<int> &cv, const float &impulseCoeff);
	virtual MassSpringObject * clone() {return 0;};
	int nature(){return kShapeNatureMSO;};

	float e;
	float oneOverMass;

	RungeKuttaODESolver *solver;

	int nParticles;
	int nParticleX;
	int nParticleY;
	vector<MassSpringParticle *> particles;

	vector<MassSpringParticle *>contour;

	MassSpringParticle *center;

protected:
	float mass;
	float gravityScale;
	float friction;

	virtual void updateVertices();
};

#endif