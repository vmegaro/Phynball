#include "Player.h"
#include "Constants.h"

#define controlPoint1x 25.0f
#define controlPoint2x 75.0f
#define controlPoint12y 70.0f

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

Player::Player(float xPosition, float yPosition) : RectangleRB(xPosition, yPosition,
												0.0f, 0.0f,
												5.0f, 10.0f,
												0.0f, 0.0f,
												1.0f, 0.0f, 0.0f,
												1.0f,
												NULL) {

	textureName = "../images/goalKeeper.png";
	
	solver = new RungeKuttaODESolver(timeStep);

}

Player * Player::clone() {
	return this;
}

void Player::update(Shape *newSh) {
	this->RigidBody::update(newSh);
	this->RectangleRB::updateVertices();
}

void Player::draw() {
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