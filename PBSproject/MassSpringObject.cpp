#include "MassSpringObject.h"

void MassSpringObject::update(Shape *newSh) {
	for(int i = 0; i < nParticles; i++) {
		particles.at(i)->updateForces();
	}
	for(int i = 0; i < nParticles; i++) {
		particles.at(i)->update(particles.at(i));
		particles.at(i)->Tx = 0.0f;
		particles.at(i)->Ty = 0.0f;
	}
	updateVertices();
	xPos = center->xPos;
	yPos = center->yPos;
}

void MassSpringObject::updateVertices() {
	for(int i = 0; i < nVertices; i++) {
		vertices.at(2*i) = contour.at(i)->xPos;
		vertices.at(2*i+1) = contour.at(i)->yPos;
	}
}

void MassSpringObject::setCollisionResponse(Shape *collidingSh, const int &pointIndex, const int &edgeIndex, Collision *collision) {

}

void MassSpringObject::handleResponseImpulse(const float &nx, const float &ny, const float &rx, const float &ry,
												const std::vector<int> &cv, const float &impulseCoeff){


	int n = nParticles;
	MassSpringParticle *currentParticle;
	for(int i = 0; i < n; i++){
		currentParticle = particles.at(i);
		float dx = rx-(currentParticle->xPos-xPos);
		float dy = ry-(currentParticle->yPos-yPos);
		if(dx*dx+dy*dy > 15.0) continue;
		currentParticle->Tx = (nx*impulseCoeff-currentParticle->mass*currentParticle->xVel)/(n*timeStep);
		currentParticle->Ty = (ny*impulseCoeff-currentParticle->mass*currentParticle->yVel)/(n*timeStep);
	}
}