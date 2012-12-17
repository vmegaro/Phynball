#include "CharacterRB.h"
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

CharacterRB::CharacterRB(char _character, RungeKuttaODESolver *odeSolver) : RectangleRB(200.0f, 200.0f,
																						0.0f, 0.0f,
																						20.0f, 20.0f,
																						0.0f, 0.0f,
																						1.0f, 0.0f, 0.0f,
																						1.0f,
																						odeSolver) {

	character = _character;

	reinit();

	updateVertices();
}

void CharacterRB::reinit() {
	switch(character) {
	case 'g': {
		xPos = -31.0f;
		yPos = 50.0f;
		xVel = 30.0f;
		yVel = 0.0f;
		angularPos = 0.0f;
		angularVel = 0.0f;
		textureName = "../images/g.png";
		break;
	}
	case 'o': {
		xPos = 52.0f;
		yPos = 131.0f;
		xVel = 0.0f;
		yVel = -30.0f;
		angularPos = 0.0f;
		angularVel = 0.0f;
		textureName = "../images/o.png";
		break;
	}
	case 'a': {
		xPos = 50.0f;
		yPos = -28.0f;
		xVel = 0.0f;
		yVel = 30.0f;
		angularPos = 0.0f;
		angularVel = 0.0f;
		textureName = "../images/a.png";
		break;
	}
	case 'l': {
		xPos = 130.0f;
		yPos = 55.0f;
		xVel = -30.0f;
		yVel = 0.0f;
		angularPos = 0.0f;
		angularVel = 0.0f;
		textureName = "../images/l.png";
		break;
	}

	}

	updateVertices();
}

void CharacterRB::draw() {
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