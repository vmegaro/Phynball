#include "Renderer.h"
#include "DeformableObject.h"
#include "RectangleRB.h"
#include "CircleRB.h"
#include "Constants.h"
#include "Board.h"
#include "Wall.h"
#include "RectangleWall.h"
#include "TriangleWall.h"
#include "UpWall.h"
#include "DownWall.h"
#include "LeftWall.h"
#include "RightWall.h"
#include "LeftTriangleWall.h"
#include "RightTriangleWall.h"
#include "Pale.h"
#include "PlayBall.h"
#include "GoalKeeper.h"
#include "Referee.h"
#include "RectangleMSO.h"
#include "Player.h"
#include "Net.h"
#include "NakedMan.h"

//create all objects needed to launch the game and start it
void setupAndRun(int argc, char** argv) {
	Board *board = new Board();
	RungeKuttaODESolver *solver = new RungeKuttaODESolver(timeStep);

	for(int i = 30; i < 80; i+=10) {
		for(int j = 30; j < 80; j+=20) {
			Shape *player = new Player(i,j);
			board->addShape(player);
		}
	}

	Shape *recWLeft = new LeftWall();
	Shape *recWRight = new RightWall();
	Shape *recWUp = new UpWall();
	Shape *recWDown = new DownWall();
	Shape *triWLeft = new LeftTriangleWall();
	Shape *triWRight = new RightTriangleWall();
	Shape *trWallR = new TriangleWall(95.0f, 90.0f,
									  85.0f, 90.0f,
									  95.0f, 80.0f,
									  0.5f);
	Shape *trWallL = new TriangleWall(5.0f, 90.0f,
									  15.0f, 90.0f,
									  5.0f, 80.0f,
									  0.5f);

	Shape *cir1 = new PlayBall(solver);
	Shape *goalKeeper = new GoalKeeper(cir1);

	Shape *referee = new Referee();

	//Shape *do1 = new DeformableObject(DeformableObject::VertexList_Rectangle(leftGoalPole,bottomGoal,goalWidth,goalHeight),DeformableObject::FaceList_Rectangle(),
						//DeformableObject::Contour_Rectangle(),0.03f,1.0f,0.3f,0.3f,0.3f,0.3f); do1->xPos = 50; do1->yPos = middleGoal;
	Shape *net = new Net();
	Shape *nakedMan = new NakedMan();

	Shape *paleL = new Pale(kLeftPale,solver);
	Shape *paleR = new Pale(kRightPale,solver);

	board->addWall(recWUp);
	board->addWall(recWLeft);
	board->addWall(recWRight);
	board->addWall(recWDown);
	board->addWall(triWLeft);
	board->addWall(triWRight);
	board->addWall(trWallR);
	board->addWall(trWallL);
	board->addShape(goalKeeper);
	board->addPlayBall(cir1);
	board->addShape(referee);
	board->addLeftPale(paleL);
	board->addRightPale(paleR);
	board->addShape(net);
	board->addShape(nakedMan);

	Renderer *r = new Renderer(&argc, argv, board);
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
				60.0f, 60.0f,
				0.0f, -50.0f,
				4.0f,
				0.0f, 0.0f,
				0.1f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *cir3 = new CircleRB(
				0.0f, -0.5f,
				0.0f, 0.0f,
				8.0f,
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
	Shape *do1 = new DeformableObject(DeformableObject::VertexList_Rectangle(50,30,20,10),DeformableObject::FaceList_Rectangle(),
						DeformableObject::Contour_Rectangle(),0.5f,0.3f,0.1f,0.1f,0.1f,0.3f); do1->xPos = 50; do1->yPos = 30;
	Shape *do2 = new DeformableObject(DeformableObject::VertexList_Rectangle(-0.15,-0.7,0.3,0.1),DeformableObject::FaceList_Rectangle(),
						DeformableObject::Contour_Rectangle(),0.03f,0.3f,0.2f,0.2f,0.2f,0.3f);
	Shape *do3 = new DeformableObject(DeformableObject::VertexList_Circle(0.0f,0.0f,0.15),DeformableObject::FaceList_Circle(),
						DeformableObject::Contour_Circle(),0.03f,0.3f,0.2f,0.2f,0.2f,0.3f);
	Shape *dov = new DeformableObject(DeformableObject::VertexList_V(0.0f,0.0f,0.3f,0.3f),DeformableObject::FaceList_V(),
						DeformableObject::Contour_V(),0.03f,0.3f,0.2f,0.2f,0.2f,0.3f);			
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
	/*board->addShape(rec2);
	board->addShape(rec3);
	board->addShape(rec4);
	board->addShape(rec5);
	board->addShape(rec6);
	board->addShape(rec7);
	board->addShape(rec8);
	board->addShape(rec9);*/
	//board->addShape(cir1);
	board->addShape(cir2);
	/*board->addShape(cir3);
	board->addShape(cir4);*/
	//board ->addShape(w);
	board->addShape(do1);
	/*board->addShape(do2);	
	board->addWall(recW1);
	board->addWall(recW2);
	board->addWall(recW3);
	board->addWall(recW4);*/
	board->addLeftPale(paleL);
	board->addRightPale(paleR);

	//Renderer *r = new Renderer(&argc, argv, board);
	setupAndRun(argc,argv);
	return 0;
}
