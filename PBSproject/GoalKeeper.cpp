#include "GoalKeeper.h"

#define standardVel 1.0f
#define minPos 30.0f
#define maxPos 70.0f

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

GoalKeeper::GoalKeeper(Shape *_playBall) : RectangleWall(50.0f, 76.5f,
										5.0f, 10.0f,
										0.0f,
										0.5f) {

	textureName = "../images/goalKeeper.png";

	solver = new RungeKuttaODESolver(timeStep);
	playBall = (RigidBody *)_playBall;

}

GoalKeeper * GoalKeeper::clone() {
	return this;
}

void GoalKeeper::update(Shape *newSh) {
	if(playBall->xPos > xPos+1.0f && xPos < maxPos) {
		xVel = standardVel;
	}
	else if(playBall->xPos < xPos-1.0f && xPos > minPos) {
		xVel = -standardVel;
	}
	else {
		xVel = 0.0f;
	}
	this->RigidBody::update(newSh);
	this->RectangleWall::updateVertices();
}

void GoalKeeper::draw() {
	glEnable(GL_TEXTURE_2D);	

	glBindTexture (GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		setVertexOpenGL(vertices.at(swx),vertices.at(swy));
		glTexCoord2f(0.0, 1.0);
		setVertexOpenGL(vertices.at(nwx),vertices.at(nwy));
		glTexCoord2f(1.0, 1.0);
		setVertexOpenGL(vertices.at(nex),vertices.at(ney));
		glTexCoord2f(1.0, 0.0);
		setVertexOpenGL(vertices.at(sex),vertices.at(sey));
	glEnd();

	glDisable(GL_TEXTURE_2D);
}