#include "UpWall.h"

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

UpWall::UpWall() : RectangleWall(50.0f, 95.0f,
								100.0f, 10.0f,
								0.0f,
								0.5f) {

	textureName = "../images/up.png";
}

void UpWall::draw() {
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
