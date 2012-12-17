#ifndef C_Const
#define C_Const
#include <limits.h>
#include <iostream>
#if LINUXVERSION==1
#include "GL/glut.h"
#else
#include "GLUT/glut.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#define keyPress -32767
#define keyX 0x59
#define keyN 0x4F

#define nl '\n'

#define totTimeStep 0.03f
#define intermediateSteps 30.0f

const float windowHeight = 800.0f;
const float windowWidth = 800.0f;

const float worldWidth = 100.0f;
const float worldHeight = 100.0f;

const float timeStep = totTimeStep/intermediateSteps;
const float inf = std::numeric_limits<float>::max();
const float eps = 0.00000001f;
const float clamp = 0.5f;

const float goalWidth = 30.0f;
const float goalHeight = 3.0f;
const float leftGoalPole = 50.0f-(goalWidth/2.0f);
const float rightGoalPole = 50.0f+(goalWidth/2.0f);
const float bottomGoal = 85.0f;
const float upGoal = bottomGoal+goalHeight;
const float middleGoal = bottomGoal+goalHeight/2.0f;

enum wallOrder {
	kWallUp = 0,
	kWallLeft = 1,
	kWallRight = 2,
};

enum wallTypes {
	kStandardWall = 0
};

enum paleTypes {
	kLeftPale = 0,
	kRightPale,
};

enum shapeType {
	kShapeNatureShape = 0,
	kShapeNatureRB,
	kShapeNatureDO,
	kShapeNatureMSO,
};

#define kPaleDownDir 0
#define kPaleUpDir 1

#define maxRigidVel 40.0f
#define maxRigidAngularVel 8.0f
#define minRigidVel 0.0f
#define minRigidAngularVel 0.0f

#define kg 9.81f

#define ccw(Ax,Ay,Bx,By,Cx,Cy) ((Cy-Ay)*(Bx-Ax)>(By-Ay)*(Cx-Ax))
#define setVertexOpenGL(x,y) glVertex2d(x/worldWidth*2.0-1.0,y/worldHeight*2.0-1.0)
#define sign(fl) ((fl>=0.0f)-(fl<0.0f))

#endif