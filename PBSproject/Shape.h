#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include "Collision.h"
#include "Constants.h"
#include "../libs/Simple OpenGL Image Library/src/SOIL.h"

class Shape {
public:
	Shape() {textureName = 0;};
	virtual Shape *clone() {return 0;};
	virtual void update(Shape *newSh) {};
	virtual void setCollisionResponse(Shape *collidingSh, const int &pointIndex, const int &edgeIndex, Collision *collision) {};
	virtual void handleResponseImpulse(const float &nx, const float &ny, const float &rx, const float &ry,
						const std::vector<int> &cv, const float &impulseCoeff){};
	virtual void copyTo(Shape *newShape) {};
	virtual int nature(){return 0;};

	std::vector<float> vertices;
	int nVertices;

	float xPos,yPos,angularPos;
	float xVel,yVel,angularVel;

	double color[3];
	GLuint texture;
	char *textureName;
	virtual void setupTexture() {
		if(!textureName) return;
		const char *fname = textureName;
		texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
		(
			fname,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
		);

		if (!texture)
		{
			printf("failed to load texture: %s\n",fname);
			//exit(0);
		}else {
			printf("loaded texture: %s\n", fname);
			glBindTexture (GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
		}
	};
	void draw() {
		glColor3dv(color);
		glBegin(GL_POLYGON);
			for(int k = 0; k < nVertices; k++){
				// No scale
				//glVertex2d(vertices.at(2*k), vertices.at(2*k+1));
				// With scale
				setVertexOpenGL(vertices.at(2*k), vertices.at(2*k+1));
			}
		glEnd();

		glLineWidth(1);
		glColor3d(0,0,0);

		glDepthFunc(GL_ALWAYS);
		glBegin(GL_LINE_LOOP);
		for(int k = 0; k < nVertices; k++){
			// No scale
			//glVertex2d(vertices.at(2*k), vertices.at(2*k+1));
			// With scale
			setVertexOpenGL(vertices.at(2*k), vertices.at(2*k+1));
		}
		glEnd();
	};

	float criticalRadius;
};


#endif