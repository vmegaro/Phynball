#include "RectangleWall.h"
#include "Constants.h"

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

RectangleWall::RectangleWall(float xPosition, float yPosition,
						 float recWidth, float recHeight,
						 float angularPosition,
						 float elasticity) {
							 xPos = xPosition; yPos = yPosition;
							 xVel = 0.0f; yVel = 0.0f;
							 width = recWidth; heigth = recHeight;
							 halfWidth = width*0.5f; halfHeight = heigth*0.5f;
							 angularPos = angularPosition; angularVel = 0.0f;
							 mass = inf; friction = 0.0f; gravityScale = 0.0f;
							 e = elasticity;
							 momentOfInertia = inf;
							 oneOverMass = 0.0f; oneOverI = 0.0f;
							 Tx = 0.0f; Ty = 0.0f; Rx = 0.0f; Ry = 0.0f;
							 solver = NULL;

							 nVertices = NUM_Vertices/2;
							 vertices = vector<float>(nVertices*2,0.0f);
							 updateVertices();

							 color[0] = 0.8;
							 color[1] = 0.0;
							 color[2] = 0.1;
}

RectangleWall* RectangleWall::clone() {
	return new RectangleWall(xPos, yPos, width,heigth, angularPos, e);
}

void RectangleWall::updateVertices() {
	eastVecX = cos(angularPos)*halfWidth; // deltaX
	eastVecY = sin(angularPos)*halfWidth; // deltaY

	relength = halfHeight/sqrt(eastVecX*eastVecX+eastVecY*eastVecY);

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