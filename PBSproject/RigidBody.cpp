#include "RigidBody.h"
#include "DeformableObject.h"
#include "MassSpringObject.h"
#include "Constants.h"
#include <cmath>

void RigidBody::setXAcc(const float &x, const float &v, float &a) {
	a = (Tx - friction*xVel)*oneOverMass;
}

void RigidBody::setYAcc(const float &x, const float &v, float &a){
	a = (Ty - friction*yVel)*oneOverMass - gravityScale*kg;
}

void RigidBody::setAngularAcc(const float &x, const float &v, float &a){
	a = (Rx*Ty-Ry*Tx - friction*angularVel)*oneOverI;
}

void RigidBody::update(Shape *newSh){
	RigidBody *newRb = (RigidBody *)newSh;
	solver->updateRigidBodyPositionAngleAndVelocities(this, newRb);
	updateVertices();	
}

float deltaVx, deltaVy, deltaVa, impulseCoeff;
float nx,ny,r;
float vabx, vaby;
float rxa, rya, rxb, ryb;
float jOverMass;
float xCollision, yCollision;
void RigidBody::setCollisionResponse(Shape *collidingSh, const int &pointIndex, const int &edgeIndex, Collision *collision){
	if(collidingSh->nature() == kShapeNatureRB){
		RigidBody *collidingRb = (RigidBody *)collidingSh;
		xCollision=collidingRb->vertices.at(pointIndex*2);
		yCollision=collidingRb->vertices.at(pointIndex*2+1);
		// Compute relative velocity
		rxa = xCollision - collidingRb->xPos;
		rya = yCollision - collidingRb->yPos;
		rxb = xCollision - xPos;
		ryb = yCollision - yPos;

		vabx = collidingRb->xVel - (collidingRb->angularVel*rya) - (xVel - (angularVel*ryb));
		vaby = collidingRb->yVel + (collidingRb->angularVel*rxa) - (yVel + (angularVel*rxb));

		// compute unit normal: nx = dy, ny = -dx
		nx = vertices.at((edgeIndex+1)%nVertices*2+1)-vertices.at((edgeIndex)*2+1);
		ny = -(vertices.at((edgeIndex+1)%nVertices*2)-vertices.at((edgeIndex)*2));
		r = sqrt(nx*nx+ny*ny);
		nx /= r;
		ny /= r;
		if(nx*(xCollision-vertices.at(edgeIndex*2))+ny*(yCollision-vertices.at(edgeIndex*2+1))>0){
			nx=-nx;
			ny=-ny;
		}

		// Not an actual collision!!
		if(vabx*nx+vaby*ny > 0.0f) return;

		// Compute j (impulse coeff)
		impulseCoeff = -((1.0f+e)*(vabx*nx+vaby*ny))/
			((collidingRb->oneOverMass)+oneOverMass+(rxa*ny-nx*rya)*(rxa*ny-nx*rya)*(collidingRb->oneOverI)+(rxb*ny-nx*ryb)*(rxb*ny-nx*ryb)*oneOverI);

		// Set up collision object
		collision->shapeB = this;
		collision->shapeA = collidingRb;
		collision->nx = nx;
		collision->ny = ny;
		collision->rxa = rxa;
		collision->rya = rya;
		collision->rxb = rxb;
		collision->ryb = ryb;
		collision->j = impulseCoeff;
		collision->resolved = 0;
	}else {
		DeformableObject *collidingDo = (DeformableObject *) collidingSh;
		xCollision=collidingDo->vertices.at(pointIndex*2);
		yCollision=collidingDo->vertices.at(pointIndex*2+1);
		rxa = xCollision - collidingDo->G[0];
		rya = yCollision - collidingDo->G[1];
		rxb = xCollision - xPos;
		ryb = yCollision - yPos;
		//Compute velocity
		vabx=collidingDo->velocity(collidingDo->contour.at(pointIndex)*2)-(xVel-angularVel*ryb);
		vaby=collidingDo->velocity(collidingDo->contour.at(pointIndex)*2+1)-(yVel+angularVel*rxb);
		// compute unit normal: nx = dy, ny = -dx
		nx = vertices.at((edgeIndex+1)%nVertices*2+1)-vertices.at((edgeIndex)*2+1);
		ny = -(vertices.at((edgeIndex+1)%nVertices*2)-vertices.at((edgeIndex)*2));
		r = sqrt(nx*nx+ny*ny);
		nx /= r;
		ny /= r;
		if(nx*(xCollision-vertices.at(edgeIndex*2))+ny*(yCollision-vertices.at(edgeIndex*2+1))>0){
			nx=-nx;
			ny=-ny;
		}
		if(vabx*nx+vaby*ny > 0.0f) return;
		// Compute j (impulse coeff)
		impulseCoeff = -((1.0f+(e+collidingDo->e)/2.0f)*(vabx*nx+vaby*ny))/
			((collidingDo->oneOverMass)+oneOverMass+(rxb*ny-nx*ryb)*(rxb*ny-nx*ryb)*oneOverI);
		collision->shapeB = this;
		collision->shapeA = collidingDo;
		collision->nx = nx;
		collision->ny = ny;
		collision->rxa = rxa;
		collision->rya = rya;
		collision->cva.push_back(collidingDo->contour.at(pointIndex));
		collision->rxb = rxb;
		collision->ryb = ryb;
		collision->j = impulseCoeff;
		collision->resolved = 0;
	}
}

void RigidBody::handleResponseImpulse(const float &nx, const float &ny, const float &rx, const float &ry, 
					const std::vector<int> &cv, const float &impulseCoeff){
	jOverMass = impulseCoeff*oneOverMass;
	xVel += jOverMass*nx;
	yVel += jOverMass*ny;
	angularVel += (rx*ny-nx*ry)*impulseCoeff*oneOverI;
}


void RigidBody::copyTo(Shape *newShape) {
	RigidBody *newRb = (RigidBody *)newShape;
	newRb->xPos = xPos;
	newRb->yPos = yPos;
	newRb->angularPos = angularPos;
	//updateVertices();
}