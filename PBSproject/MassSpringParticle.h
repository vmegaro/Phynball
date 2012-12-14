#ifndef C_MassSpringParticle
#define C_MassSpringParticle
#include <vector>
#include "RungeKuttaODESolver.h"
#include "RigidBody.h"
#include "Constants.h"

using namespace std;

class MassSpringParticle: public RigidBody {
public:
	MassSpringParticle(float xPosition, float yPosition,
						float xVelocity, float yVelocity,
						float m, float frictionCoeff, float gravityResistance,
						float springCoeff, float springEquilibrium,
						RungeKuttaODESolver *odeSolver);
	//virtual void update(Shape *newSh);
	void updateForces();
	virtual MassSpringParticle * clone() {return 0;};

	vector<MassSpringParticle *> neighbors;

protected:
	float springK;
	float springEq;
};

#endif