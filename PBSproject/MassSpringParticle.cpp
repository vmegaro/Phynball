#include "MassSpringParticle.h"

MassSpringParticle::MassSpringParticle(float xPosition, float yPosition,
										float xVelocity, float yVelocity,
										float m, float frictionCoeff, float gravityResistance,
										float springCoeff, float springEquilibrium,
										RungeKuttaODESolver *odeSolver) {
	xPos = xPosition; xVel = xVelocity;
	yPos = yPosition; yVel = yVelocity;
	angularPos = 0.0f; angularVel = 0.0f;
	Ty = 0.0f; Tx = 0.0f; 


	springK = springCoeff;
	springEq = springEquilibrium;

	friction = frictionCoeff;

	mass = m; oneOverMass = 1.0f/m;
	gravityScale = gravityResistance;

	solver = odeSolver;
}

void MassSpringParticle::updateForces() {
	MassSpringParticle *currentPart;
	int nNeighbors = neighbors.size();
	for(int i = 0; i < nNeighbors; i ++) {
		currentPart = neighbors.at(i);
		float dx = currentPart->xPos-xPos;
		float dy = currentPart->yPos-yPos;
		float dist = sqrt(dx*dx+dy*dy);
		float mag = (dist-springEq)*springK;
		Tx += dx/dist*mag;
		Ty += dy/dist*mag;
	}
}