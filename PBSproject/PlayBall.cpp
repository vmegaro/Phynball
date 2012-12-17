#include "PlayBall.h"
#include "Constants.h"

PlayBall::PlayBall(RungeKuttaODESolver *solver) : CircleRB(75.0f, 65.0f,
															0.0f, 100.0f,
															2.5f,
															0.0f, 0.0f,
															1.0f, 0.0f, 1.0f,
															1.0f,
															solver) {

																textureName = "../images/ball.png";

}

void PlayBall::update(Shape *newSh) {
	this->CircleRB::update(newSh);
}

void PlayBall::draw() {
	glEnable(GL_TEXTURE_2D);	

	glBindTexture (GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5, 0.5);
	setVertexOpenGL(xPos,yPos);
	float s = (float)(2*M_PI/nVert);
	float t = 0;
	for(int k = 0; k < nVertices; t += s, k++){
		float tx = 0.5f + 0.5f*cos(t);
		float ty = 0.5f + 0.5f*sin(t);
		glTexCoord2f(tx, ty);
		setVertexOpenGL(vertices.at(2*k),vertices.at(2*k+1));
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

PlayBall * PlayBall::clone() {
	return this;
}