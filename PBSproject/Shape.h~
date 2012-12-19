#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include "Collision.h"
#include "Constants.h"
#include "../libs/Simple OpenGL Image Library/src/SOIL.h"
/*
Base class of all objects in the scene
*/
class Shape {
public:
	Shape() {textureName = 0;};
	// clonin function to duplicate the object
	virtual Shape *clone() {return 0;};
	// update all parameters of the objects and put the new values in 'newSh'
	virtual void update(Shape *newSh) {};
	// create a 'collision' object regarding a collision occuring with vertex 'pointIndex' of 'collidingSh' on edge 'edgeIndex' of 'this'
	virtual void setCollisionResponse(Shape *collidingSh, const int &pointIndex, const int &edgeIndex, Collision *collision) {};
	// update the state of 'this' after a collision occurs on vertices in 'cv' with an impulse coefficient of 'impulseCoeff'
	// along the vector given by 'nx' and 'ny'. 'rx' and 'ry' are distances used to sompute the influence on the rotation of 'this'
	virtual void handleResponseImpulse(const float &nx, const float &ny, const float &rx, const float &ry,
						const std::vector<int> &cv, const float &impulseCoeff){};
	virtual void copyTo(Shape *newShape) {};
	// used to determine if this shape is a rigid body or a deformable object
	virtual int nature(){return 0;};
	// coordinates of the vertices of the contour of this shape
	std::vector<float> vertices;
	//number of vertices of the contour
	int nVertices;
	// position and angle of the center of mass
	float xPos,yPos,angularPos;
	// velocities of the center of mass
	float xVel,yVel,angularVel;
	// default color
	double color[3];
	GLuint texture;
	//texture path
	char *textureName;
	// load the texture
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
	//rendering function
	virtual void draw() {
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
	// radius of the bounding circle
	float criticalRadius;
};


#endif
