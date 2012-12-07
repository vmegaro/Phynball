#include "Renderer.h"
#include "DeformableObject.h"
#include "RectangleRB.h"
#include "CircleRB.h"
#include "Constants.h"
#include "Board.h"
#include "Wall.h"
#include "RectangleWall.h"
#include "Pale.h"

vector<Vector3i> FaceList_Rectangle(){
	vector<Vector3i> face (16);
	face[0][0]=0;face[0][1]=1;face[0][2]=5;
	face[1][0]=1;face[1][1]=2;face[1][2]=6;
	face[2][0]=2;face[2][1]=3;face[2][2]=7;
	face[3][0]=3;face[3][1]=4;face[3][2]=8;
	face[4][0]=1;face[4][1]=6;face[4][2]=5;
	face[5][0]=2;face[5][1]=7;face[5][2]=6;
	face[6][0]=3;face[6][1]=8;face[6][2]=7;
	face[7][0]=5;face[7][1]=6;face[7][2]=10;
	face[8][0]=6;face[8][1]=7;face[8][2]=11;
	face[9][0]=7;face[9][1]=8;face[9][2]=12;
	face[10][0]=5;face[10][1]=10;face[10][2]=9;
	face[11][0]=6;face[11][1]=11;face[11][2]=10;
	face[12][0]=7;face[12][1]=12;face[12][2]=11;
	face[13][0]=8;face[13][1]=13;face[13][2]=12;
	face[14][0]=0;face[14][1]=5;face[14][2]=9;
	face[15][0]=4;face[15][1]=13;face[15][2]=8;
	return face;
}

vector<Vector2f> VertexList_Rectangle(float x,float y,float width,float height){
	vector<Vector2f> pos (14);
	float w=width/4.0f;
	float h=height/2.0f;
	pos[0][0]=x;pos[0][1]=y;
	pos[1][0]=x+w;pos[1][1]=y;
	pos[2][0]=x+2*w;pos[2][1]=y;
	pos[3][0]=x+3*w;pos[3][1]=y;
	pos[4][0]=x+4*w;pos[4][1]=y;
	pos[5][0]=x+0.5f*w;pos[5][1]=y+h;
	pos[6][0]=x+1.5f*w;pos[6][1]=y+h;
	pos[7][0]=x+2.5f*w;pos[7][1]=y+h;
	pos[8][0]=x+3.5f*w;pos[8][1]=y+h;
	pos[9][0]=x;pos[9][1]=y+2*h;
	pos[10][0]=x+w;pos[10][1]=y+2*h;
	pos[11][0]=x+2*w;pos[11][1]=y+2*h;
	pos[12][0]=x+3*w;pos[12][1]=y+2*h;
	pos[13][0]=x+4*w;pos[13][1]=y+2*h;
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
						Contour_Rectangle(),0.03f,0.1f,0.2f,1.0f,1.0f,0.3f);
	DeformableObject *do2 = new DeformableObject(VertexList_Rectangle(-0.15,-0.7,0.3,0.1),FaceList_Rectangle(),
						Contour_Rectangle(),0.03f,0.1f,0.2f,1.0f,1.0f,0.3f);				
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