#if LINUXVERSION==1
#include "GL/glut.h"
#else
#include "GLUT/glut.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>
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
#include "../libs/Simple OpenGL Image Library/src/SOIL.h"

#define MICROSECS_PER_FRAME  totTimeStep*100.0f
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

GLuint bgTex;

void prepareTexture() {

	// Texture for background
	const char* fname = "../images/field.png";
	bgTex = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
	(
		fname,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
	if (!bgTex)
    {
        printf("failed to load texture: %s\n",fname);
        //exit(0);
	}else {
		printf("loaded texture: %s\n", fname);
	}

	glBindTexture (GL_TEXTURE_2D, bgTex);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	// dynamic objects
	for(vector<Shape *>::iterator it = board->shapes->begin();it != board->shapes->end();it++){
		(*it)->setupTexture();
	}

	// walls
	for(vector<Wall *>::iterator it = board->walls->begin();it != board->walls->end();it++){
		(*it)->setupTexture();
	}

	//  pales
	board->leftPale->setupTexture();
	board->rightPale->setupTexture();

	// characters
	for(vector<Shape *>::iterator it = board->goalCharacters.begin();it != board->goalCharacters.end();it++){
		(*it)->setupTexture();
	}
}

void drawObjects() {
	//draw dynamic objects
	for(vector<Shape *>::iterator it = board->shapes->begin();it != board->shapes->end();it++){
		(*it)->draw();
	}

	//draw walls
	for(vector<Wall *>::iterator it = board->walls->begin();it != board->walls->end();it++){
		(*it)->draw();
	}

	// draw pales
	board->leftPale->draw();
	board->rightPale->draw();
	// end draw pales

	//draw characters
	for(vector<Shape *>::iterator it = board->goalCharacters.begin();it != board->goalCharacters.end();it++){
		(*it)->draw();
	}
}

void drawBackground() {
	// draw background
	glEnable(GL_TEXTURE_2D);	

	glBindTexture (GL_TEXTURE_2D, bgTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(-1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0); glVertex2f(1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0); glVertex2f(1.0f, 1.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(-1.0f, 1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

char score[25];
void drawString (void * font, char *s, float x, float y){
     unsigned int i;
     glRasterPos2f(x, y);

     for (i = 0; i < strlen (s); i++)
          glutBitmapCharacter (font, s[i]);
}

void display(){
	if (getTime() - next_update > MICROSECS_PER_FRAME) {
		next_update += MICROSECS_PER_FRAME;
		glClearColor(0.2,0.2,0.2,1);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_CULL_FACE);

		//update
		board->update();

		// Draw background with texture
		drawBackground();

		// draw shapes, pales and walls
		drawObjects();

		// draw score
		sprintf(score,"Player: %d",board->playerScore);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, score, -0.8f, 0.88f);
		sprintf(score,"SuperTeam: %d",board->otherTeamScore);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, score, -0.8f, 0.83f);
		
		//glFlush();
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
	glViewport(0, 0, windowWidth, windowHeight);
	//glOrtho(-width/2, width/2, -height/2, height/2, 1, 100);
}

void idle(){
	glutPostRedisplay();
}

void keypress(unsigned char key, int x, int y){
	if(key=='x')
		board->moveLeftPale(true);
	if(key=='n')
		board->moveRightPale(true);
	cout<<key<<" pressed " ;
}

void keyreleased(unsigned char key, int x, int y){
	if(key=='x')
		board->moveLeftPale(false);
	if(key=='n')
		board->moveRightPale(false);
	cout<<key<<" released ";
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
    glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-windowWidth)/2, (glutGet(GLUT_SCREEN_HEIGHT)-windowHeight)/2);

	glutCreateWindow("PBS Project");

	glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

	glutKeyboardFunc(keypress);
	glutKeyboardUpFunc(keyreleased);
	glutIgnoreKeyRepeat(true);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	next_update = getTime();
	glEnable(GL_LINE_SMOOTH);
	//glDisable(GL_DEPTH_TEST);

	prepareTexture();

    glutMainLoop();
}

Renderer::~Renderer(){
}