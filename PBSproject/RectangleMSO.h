#ifndef C_RectangleMSO
#define C_RectangleMSO
#include <vector>
#include "MassSpringObject.h"
#include "Constants.h"

using namespace std;

class RectangleMSO: public MassSpringObject {
public:
	RectangleMSO(float xPosition, float yPosition,
				float xVelocity, float yVelocity,
				float width, float height,
				int nParticleX, int nParticleY,
				float m, float frictionCoeff, float gravityResistance,
				float springCoeff,
				RungeKuttaODESolver *odeSolver);
	virtual RectangleMSO * clone();

	virtual void draw();

protected:
	void initParticlePosition();
};

#endif