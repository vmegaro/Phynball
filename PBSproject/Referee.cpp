#include "Referee.h"
#include "Constants.h"

Referee::Referee() : DeformableObject(DeformableObject::VertexList_Rectangle(10,40,5,10),DeformableObject::FaceList_Rectangle(),
						DeformableObject::Contour_Rectangle(),0.03f,1.0f,0.3f,0.3f,0.3f,0.3f) {

	textureName = "../images/referee.png";
}

Referee * Referee::clone() {
	return this;
}

void Referee::update(Shape *newSh) {
	this->DeformableObject::update(newSh);
}

void Referee::draw() {
	glEnable(GL_TEXTURE_2D);	

	glBindTexture (GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5, 0.5);
		setVertexOpenGL(12.5,45);

		glTexCoord2f(0.0, 0.0);
		setVertexOpenGL(vertices.at(0),vertices.at(1));
		glTexCoord2f(0.25, 0.0);
		setVertexOpenGL(vertices.at(2),vertices.at(3));
		glTexCoord2f(0.5, 0.0);
		setVertexOpenGL(vertices.at(4),vertices.at(5));
		glTexCoord2f(0.75, 0.0);
		setVertexOpenGL(vertices.at(6),vertices.at(7));
		glTexCoord2f(1.0, 0.0);
		setVertexOpenGL(vertices.at(8),vertices.at(9));
		glTexCoord2f(1.0, 1.0);
		setVertexOpenGL(vertices.at(10),vertices.at(11));
		glTexCoord2f(0.75, 1.0);
		setVertexOpenGL(vertices.at(12),vertices.at(13));
		glTexCoord2f(0.5, 1.0);
		setVertexOpenGL(vertices.at(14),vertices.at(15));
		glTexCoord2f(0.25, 1.0);
		setVertexOpenGL(vertices.at(16),vertices.at(17));
		glTexCoord2f(0.0, 1.0);
		setVertexOpenGL(vertices.at(18),vertices.at(19));
		glTexCoord2f(0.0, 0.0);
		setVertexOpenGL(vertices.at(0),vertices.at(1));

	glEnd();

	glDisable(GL_TEXTURE_2D);
}