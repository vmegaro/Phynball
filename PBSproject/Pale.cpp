#include "Pale.h"
#include "Constants.h"

#define xPosL -0.5f
#define xPosR 0.5f
#define yPosLR -0.5f
#define minAngL -M_PI/4.0f
#define maxAngL M_PI/4.0f
#define minAngR M_PI/4.0f*3.0f
#define maxAngR M_PI/4.0f*5.0f
#define standardAngVel 50.0f
#define longWidth 0.4f
#define shortWidth 0.05f
#define height 0.1f

enum PaleVerticesPositions
{
	innerx = 0,
	innery,
	outterUpx,
	outterUpy,
	outterBottomx,
	outterBottomy,
	NUM_Vertices
};

Pale::Pale(int position, RungeKuttaODESolver *odeSolver) {
	vertices = vector<float>(NUM_Vertices,0.0f);
	switch (position)
	{
	case kLeftPale:
		{
			xPos = xPosL;
			angularPos = minAngL;
			maxAngle = maxAngL;
			minAngle = minAngL;
			upAngularVel = standardAngVel;
			break;
		}
	case kRightPale:
		{
			xPos = xPosR;
			angularPos = maxAngR;
			maxAngle = maxAngR;
			minAngle = minAngR;
			upAngularVel = -standardAngVel;
			break;
		}
	default:
		break;
	}

	yPos = yPosLR;

	vertices.at(innerx) = (xPos+longWidth);vertices.at(innery) = (yPos);
	vertices.at(outterUpx) = (xPos-shortWidth);vertices.at(outterUpy) = (yPos+height);
	vertices.at(outterBottomx) = (xPos-shortWidth);vertices.at(outterBottomy) = (yPos-height);

	nVertices = NUM_Vertices/2;

	xVel = 0.0f; yVel = 0.0f;
	angularVel = 0.0f;

	updateVertices();

	mass = inf; friction = 0.0f; gravityScale = 0.0f;
	e = 1.0f;
	momentOfInertia = mass*(longWidth*longWidth+height*height)/20.0f;
	oneOverMass = 0.0f; oneOverI = 1.0f/momentOfInertia;
	Tx = 0.0f; Ty = 0.0f; Rx = 0.0f; Ry = 0.0f;
	solver = odeSolver;

	color[0] = 0.5;
	color[1] = 0.5;
	color[2] = 0.5;
}

Pale * Pale::clone() {
	if(upAngularVel == standardAngVel) {
		return new Pale(kLeftPale, solver);
	}else {
		return new Pale(kRightPale, solver);
	}
}

void Pale::update(Shape *newSh) {
	if(angularPos < minAngle) {
		angularPos = minAngle;
		angularVel = 0.0f;
	}else if(angularPos > maxAngle) {
		angularPos = maxAngle;
		angularVel = 0.0f;
	}else {
		solver->updateRigidBodyPositionAngleAndVelocities(this, this);
		updateVertices();
	}
}

void Pale::setGoUp() {
	angularVel = upAngularVel;
}

void Pale::setGoDown() {
	angularVel = -upAngularVel;
}

void Pale::updateVertices() {
	longVecX = cos(angularPos)*longWidth; // deltaX
	longVecY = sin(angularPos)*longWidth; // deltaY
	shortVecX = -cos(angularPos)*shortWidth;
	shortVecY = -sin(angularPos)*shortWidth;

	relength = height/sqrt(shortVecX*shortVecX+shortVecY*shortVecY);

	heightVecX = -shortVecY*relength;
	heightVecY = shortVecX*relength;

	vertices.at(innerx) = xPos + longVecX;
	vertices.at(innery) = yPos + longVecY;
	vertices.at(outterUpx) = xPos + shortVecX + heightVecX;
	vertices.at(outterUpy) = yPos + shortVecY + heightVecY;
	vertices.at(outterBottomx) = xPos + shortVecX - heightVecX;
	vertices.at(outterBottomy) = yPos + shortVecY - heightVecY;
}