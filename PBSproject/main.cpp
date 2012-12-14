#include "Renderer.h"
#include "DeformableObject.h"
#include "RectangleRB.h"
#include "CircleRB.h"
#include "Constants.h"
#include "Board.h"
#include "Wall.h"
#include "RectangleWall.h"
#include "Pale.h"

vector<int> FaceList_Rectangle(){
	vector<int> face (48);
	face[0]=0;face[1]=1;face[2]=5;
	face[3]=1;face[4]=2;face[5]=6;
	face[6]=2;face[7]=3;face[8]=7;
	face[9]=3;face[10]=4;face[11]=8;
	face[12]=1;face[13]=6;face[14]=5;
	face[15]=2;face[16]=7;face[17]=6;
	face[18]=3;face[19]=8;face[20]=7;
	face[21]=5;face[22]=6;face[23]=10;
	face[24]=6;face[25]=7;face[26]=11;
	face[27]=7;face[28]=8;face[29]=12;
	face[30]=5;face[31]=10;face[32]=9;
	face[33]=6;face[34]=11;face[35]=10;
	face[36]=7;face[37]=12;face[38]=11;
	face[39]=8;face[40]=13;face[41]=12;
	face[42]=0;face[43]=5;face[44]=9;
	face[45]=4;face[46]=13;face[47]=8;
	return face;
}

vector<float> VertexList_Rectangle(float x,float y,float width,float height){
	vector<float> pos (28);
	float w=width/4.0f;
	float h=height/2.0f;
	pos[0]=x;pos[1]=y;
	pos[2]=x+w;pos[3]=y;
	pos[4]=x+2*w;pos[5]=y;
	pos[6]=x+3*w;pos[7]=y;
	pos[8]=x+4*w;pos[9]=y;
	pos[10]=x+0.5f*w;pos[11]=y+h;
	pos[12]=x+1.5f*w;pos[13]=y+h;
	pos[14]=x+2.5f*w;pos[15]=y+h;
	pos[16]=x+3.5f*w;pos[17]=y+h;
	pos[18]=x;pos[19]=y+2*h;
	pos[20]=x+w;pos[21]=y+2*h;
	pos[22]=x+2*w;pos[23]=y+2*h;
	pos[24]=x+3*w;pos[25]=y+2*h;
	pos[26]=x+4*w;pos[27]=y+2*h;
	return pos;
}

vector<int> Contour_Rectangle(){
	vector<int> contour (10);
	contour[0]=0;
	contour[1]=1;
	contour[2]=2;
	contour[3]=3;
	contour[4]=4;
	contour[5]=13;
	contour[6]=12;
	contour[7]=11;
	contour[8]=10;
	contour[9]=9;
	return contour;
}

vector<int> FaceList_Circle(){
	vector<int> face (24);
	face[0]=0;face[1]=1;face[2]=2;
	face[3]=0;face[4]=2;face[5]=3;
	face[6]=0;face[7]=3;face[8]=4;
	face[9]=0;face[10]=4;face[11]=5;
	face[12]=0;face[13]=5;face[14]=6;
	face[15]=0;face[16]=6;face[17]=7;
	face[18]=0;face[19]=7;face[20]=8;
	face[21]=0;face[22]=8;face[23]=1;
	return face;
}

vector<float> VertexList_Circle(float x,float y,float radius){
	vector<float> pos (18);
	pos[0]=x; pos[1]=y;
	pos[2]=x; pos[3]=y+radius;
	pos[4]=x+0.66f*radius; pos[5]=y+0.66f*radius;
	pos[6]=x+radius; pos[7]=y;
	pos[8]=x+0.66f*radius; pos[9]=y-0.66f*radius;
	pos[10]=x; pos[11]=y-radius;
	pos[12]=x-0.66f*radius; pos[13]=y-0.66f*radius;
	pos[14]=x-radius; pos[15]=y;
	pos[16]=x-0.66f*radius; pos[17]=y+0.66f*radius;
	return pos;
}

vector<int> Contour_Circle(){
	vector<int> contour (8);
	contour[0]=1;
	contour[1]=2;
	contour[2]=3;
	contour[3]=4;
	contour[4]=5;
	contour[5]=6;
	contour[6]=7;
	contour[7]=8;
	return contour;
}

vector<int> FaceList_V(){
	vector<int> face (33);
	face[0]=0;face[1]=1;face[2]=2;
	face[3]=0;face[4]=1;face[5]=3;
	face[6]=0;face[7]=2;face[8]=4;
	face[9]=0;face[10]=3;face[11]=7;
	face[12]=0;face[13]=4;face[14]=8;
	face[15]=3;face[16]=5;face[17]=7;
	face[18]=4;face[19]=6;face[20]=8;
	face[21]=5;face[22]=7;face[23]=11;
	face[24]=6;face[25]=8;face[26]=12;
	face[27]=5;face[28]=9;face[29]=11;
	face[30]=6;face[31]=10;face[32]=12;
	return face;
}

vector<float> VertexList_V(float x,float y,float width,float height){
	vector<float> pos (26);
	float w = width/8.0f;
	float h = height/5.0f;
	pos[0]=x; pos[1]=y;
	pos[2]=x-w; pos[3]=y-h;
	pos[4]=x+w; pos[5]=y-h;
	pos[6]=x-2.0f*w; pos[7]=y;
	pos[8]=x+2.0f*w; pos[9]=y;
	pos[10]=x-3.0f*w; pos[11]=y+2.0f*h;
	pos[12]=x+3.0f*w; pos[13]=y+2.0f*h;
	pos[14]=x-2.0f*w; pos[15]=y+2.0f*h;
	pos[16]=x+2.0f*w; pos[17]=y+2.0f*h;
	pos[18]=x-4.0f*w; pos[19]=y+4.0f*h;
	pos[20]=x+4.0f*w; pos[21]=y+4.0f*h;
	pos[22]=x-3.0f*w; pos[23]=y+4.0f*h;
	pos[24]=x+3.0f*w; pos[25]=y+4.0f*h;
	return pos;
}

vector<int> Contour_V(){
	vector<int> contour (13);
	contour[0]=1;
	contour[1]=2;
	contour[2]=4;
	contour[3]=6;
	contour[4]=10;
	contour[5]=12;
	contour[6]=8;
	contour[7]=0;
	contour[8]=7;
	contour[9]=11;
	contour[10]=9;
	contour[11]=5;
	contour[12]=3;
	return contour;
}

int main(int argc, char** argv)
{
	Board *board = new Board();
	RungeKuttaODESolver *solver = new RungeKuttaODESolver(timeStep);
	Shape *rec1 = new RectangleRB(
				0.0f, 0.0f,
				0.0f, 0.0f,
				1.5f, 0.2f,
				0.0f, 0.0f,
				0.001f, 0.0f, 1.0f,
				1.0f,
				solver);
	Shape *rec2 = new RectangleRB(
				-0.3f, -0.4f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec3 = new RectangleRB(
				0.3f, -0.4f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec4 = new RectangleRB(
				-0.3f, 0.5f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec5 = new RectangleRB(
				0.3f, 0.5f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec6 = new RectangleRB(
				-0.3f, 0.2f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec7 = new RectangleRB(
				0.3f, 0.2f,
				0.0f, -0.5f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec8 = new RectangleRB(
				-0.3f, -0.1f,
				0.0f, -0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec9 = new RectangleRB(
				0.3f, -0.1f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *cir1 = new CircleRB(
				0.5f, 0.3f,
				0.0f, 0.0f,
				0.1f,
				0.0f, 0.0f,
				0.001f, 0.0f, 1.0f,
				1.0f,
				solver);
	Shape *cir2 = new CircleRB(
				0.0f, 0.6f,
				0.0f, 0.0f,
				0.08f,
				0.0f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *cir3 = new CircleRB(
				0.0f, -0.5f,
				0.0f, 0.0f,
				0.08f,
				0.0f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *cir4 = new CircleRB(
				0.0f, 0.4f,
				0.0f, -0.05f,
				0.08f,
				0.0f, 0.0f,
				0.001f, 0.0f, 0.0f,
				1.0f,
				solver);
	DeformableObject *do1 = new DeformableObject(VertexList_Rectangle(-0.15,0.0,0.3,0.1),FaceList_Rectangle(),
						Contour_Rectangle(),0.01f,0.3f,0.1f,0.1f,0.1f,0.3f);
	DeformableObject *do2 = new DeformableObject(VertexList_Rectangle(-0.15,-0.7,0.3,0.1),FaceList_Rectangle(),
						Contour_Rectangle(),0.03f,0.3f,0.2f,0.2f,0.2f,0.3f);
	DeformableObject *do3 = new DeformableObject(VertexList_Circle(0.0f,0.0f,0.15),FaceList_Circle(),
						Contour_Circle(),0.03f,0.3f,0.2f,0.2f,0.2f,0.3f);
	DeformableObject *dov = new DeformableObject(VertexList_V(0.0f,0.0f,0.3f,0.3f),FaceList_V(),
						Contour_V(),0.03f,0.3f,0.2f,0.2f,0.2f,0.3f);			
	Shape *w = new Wall(kStandardWall);
	Shape *recW1 = new RectangleWall(
				0.0f, -0.9f,
				2.0f, 0.2f,
				0.0f,
				0.5f);
	Shape *recW2 = new RectangleWall(
				0.0f, 0.9f,
				2.0f, 0.2f,
				0.0f,
				0.5f);
	Shape *recW3 = new RectangleWall(
				-0.9f, 0.0f,
				0.2f, 1.5f,
				0.0f,
				0.5f);
	Shape *recW4 = new RectangleWall(
				0.9f, 0.0f,
				0.2f, 1.5f,
				0.0f,
				0.5f);
	Shape *paleL = new Pale(kLeftPale,solver);
	Shape *paleR = new Pale(kRightPale,solver);

	//board->addShape(rec1);
	board->addShape(rec2);
	board->addShape(rec3);
	board->addShape(rec4);
	board->addShape(rec5);
	board->addShape(rec6);
	board->addShape(rec7);
	board->addShape(rec8);
	board->addShape(rec9);
	//board->addShape(cir1);
	board->addShape(cir2);
	board->addShape(cir3);
	board->addShape(cir4);
	//board ->addShape(w);
	board->addShape(do1);
	//board->addShape(do2);	
	board->addWall(recW1);
	board->addWall(recW2);
	board->addWall(recW3);
	board->addWall(recW4);
	board->addLeftPale(paleL);
	board->addRightPale(paleR);

	Renderer *r = new Renderer(&argc, argv, board);
	return 0;
}
