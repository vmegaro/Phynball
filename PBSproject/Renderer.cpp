#if LINUXVERSION==1
#include "GL/glut.h"
#else
#include "GLUT/glut.h"
#endif

#if MACVERSION==1
#include <CoreServices/CoreServices.h>
#else
#if LINUXVERSION==1
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#else
#include <windows.h>
#endif
#endif

#include <iostream>
#include "Renderer.h"
#include "Constants.h"

#define MICROSECS_PER_FRAME  20000//50 frames per second
using namespace std;

Board *board;
unsigned int next_update;
double mspt;//millisecs per tick

unsigned int getTime()
{
	#if MACVERSION==1
	// mac
	UnsignedWide uCur;
	Microseconds(&uCur);
	return uCur.lo;
#else
#if LINUXVERSION==1
	struct timeval tv;
	struct timezone tz;
	tz.tz_minuteswest = 0;
	tz.tz_dsttime = 0;
	gettimeofday(&tv,&tz);
 	return (unsigned int) ( (tv.tv_sec*1000)+(tv.tv_usec/1000) )*10000;
#else
	LARGE_INTEGER tick;
	QueryPerformanceCounter(&tick);
	return (unsigned int) (mspt*tick.QuadPart);
#endif
#endif
}

void display(){
	if (getTime() - next_update > MICROSECS_PER_FRAME) {
		next_update += MICROSECS_PER_FRAME;
		glClearColor(0.2,0.2,0.2,1);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_CULL_FACE);

		//update
		board->update();
		
		//draw
		for(vector<Shape *>::iterator it= board->shapes->begin();it != board->shapes->end();it++){
			glColor3dv((*it)->color);

			glBegin(GL_POLYGON);
			for(int k = 0; k < (*it)->nVertices; k++){
				glVertex2d((*it)->vertices.at(2*k), (*it)->vertices.at(2*k+1));
			}
			glEnd();

			glLineWidth(1);
			glColor3d(0,0,0);

			glDepthFunc(GL_ALWAYS);
			glBegin(GL_LINE_LOOP);
			for(int k = 0; k < (*it)->nVertices; k++){
				glVertex2d((*it)->vertices.at(2*k), (*it)->vertices.at(2*k+1));
			}
			glEnd();
			glDepthFunc(GL_EQUAL);
		}
		
		glFlush();
		glutPostRedisplay();
		glutSwapBuffers();
	}
}

void reshape(int width, int height){
	/*
	width = 600;
	height = 600;
	GLdouble g[16];
	glGetDoublev(GL_PROJECTION, g);
	for(int k=0;k<16;k+=4){
		for(int i=0;i<4;i++)
			cout<<g[k+i]<<"\t";
		cout<<"\n";
	}
	cout<<"\n";
	*/
	glViewport(0, 0, width, height);
	//glOrtho(-width/2, width/2, -height/2, height/2, 1, 100);
}

void idle(){
	glutPostRedisplay();
}

void updatePale(unsigned char key, int x, int y) {
	switch (key) {
	case 27:  // ESC
		exit(0);
	case 'x':
		board->updatePaleDirection(kLeftPale, kPaleUpDir);
		break;
	case 'n':
		board->updatePaleDirection(kRightPale, kPaleUpDir);
		break;
	}
}


Renderer::Renderer(int* argc, char** argv, Board *brd){
	#if MACVERSION==1
	// nothing to do...
	#else
	#if LINUXVERSION==1
	// nothing to do...
	#else
	LARGE_INTEGER tps_long;
	QueryPerformanceFrequency(&tps_long);
	mspt = 1e6/(double)tps_long.QuadPart;
	#endif
	#endif

	board = brd;

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-400, glutGet(GLUT_SCREEN_HEIGHT)/2-300);

	glutCreateWindow("PBS Project");

	glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
	//glutKeyboardFunc(updatePale);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	next_update = getTime();
	glEnable(GL_LINE_SMOOTH);
    glutMainLoop();
}

Renderer::~Renderer(){
}