#include "RectangleRB.h"
#include <cmath>

#define g 9.81f

enum VerticesPositions
{
	nex = 0,
	ney,
	nwx,
	nwy,
	swx,
	swy,
	sex,
	sey,
	NUM_Vertices
};

float halfWidth, halfHeight;

RectangleRB::RectangleRB(float xPosition, float yPosition,
						 float xVelocity, float yVelocity,
						 float recWidth, float recHeight,
						 float angularPosition, float angularVelocity,
						 float m, float frictionCoeff, float gravityResistance,
						 RungeKuttaODESolver *odeSolver) {

							 xPos = xPosition; yPos = yPosition;
							 xVel = xVelocity; yVel = yVelocity;
							 width = recWidth; heigth = recHeight;
							 halfWidth = width*0.5f; halfHeight = heigth*0.5f;
							 angularPos = angularPosition; angularVel = angularVelocity;
							 mass = m; friction = frictionCoeff; gravityScale = gravityResistance;
							 momentOfInertia = mass*(width*width+heigth*heigth)/12.0f;
							 oneOverMass = 1.0f/mass; oneOverI = 1.0f/momentOfInertia;
							 Tx = 0.0f; Ty = 0.0f; Rx = 0.0f; Ry = 0.0f;
							 solver = odeSolver;

							 nVertices = NUM_Vertices/2;
							 vertices = vector<float>(nVertices*2,0.0f);
							 updateVertices();

							 color[0] = 0.8;
							 color[1] = 0.6;
							 color[2] = 0.1;
}

RigidBody * RectangleRB::clone() {
	return new RectangleRB(
		xPos, yPos,
		xVel,yVel,
		width, heigth,
		angularPos, angularVel,
		mass, friction, gravityScale,
		solver);
}

float eastVecX, eastVecY, northVecX, northVecY, relength;
void RectangleRB::updateVertices() {
	eastVecX = cos(angularPos)*halfWidth; // deltaX
	eastVecY = sin(angularPos)*halfWidth; // deltaY

	relength = sqrt(eastVecX*eastVecX+eastVecY*eastVecY)*halfHeight;

	northVecX = -eastVecY*relength;
	northVecY = eastVecX*relength;

	vertices.at(nex) = xPos + eastVecX + northVecX;
	vertices.at(ney) = yPos + eastVecY + northVecY;
	vertices.at(sex) = xPos + eastVecX - northVecX;
	vertices.at(sey) = yPos + eastVecY - northVecY;
	vertices.at(nwx) = xPos - eastVecX + northVecX;
	vertices.at(nwy) = yPos - eastVecY + northVecY;
	vertices.at(swx) = xPos - eastVecX - northVecX;
	vertices.at(swy) = yPos - eastVecY - northVecY;
}