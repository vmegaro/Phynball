#include "Renderer.h"
#include "RectangleRB.h"
#include "CircleRB.h"
#include "Constants.h"
#include "Board.h"
#include "Wall.h"
#include "RectangleWall.h"
#include "Pale.h"

int main(int argc, char** argv)
{
	Board *board = new Board();
	RungeKuttaODESolver *solver = new RungeKuttaODESolver(timeStep);
	Shape *rec1 = new RectangleRB(
				0.0f, 0.0f,
				0.0f, 0.0f,
				1.5f, 0.2f,
				0.0f, 0.0f,
				1.0, 0.0f, 1.0f,
				1.0f,
				solver);
	Shape *rec2 = new RectangleRB(
				-0.3f, -0.4f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec3 = new RectangleRB(
				0.3f, -0.4f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec4 = new RectangleRB(
				-0.3f, 0.5f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec5 = new RectangleRB(
				0.3f, 0.5f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec6 = new RectangleRB(
				-0.3f, 0.2f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec7 = new RectangleRB(
				0.3f, 0.2f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec8 = new RectangleRB(
				-0.3f, -0.1f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *rec9 = new RectangleRB(
				0.3f, -0.1f,
				0.0f, 0.0f,
				0.1f, 0.1f,
				0.5f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *cir1 = new CircleRB(
				0.5f, 0.3f,
				0.0f, 0.0f,
				0.1f,
				0.0f, 0.0f,
				1.0f, 0.0f, 1.0f,
				1.0f,
				solver);
	Shape *cir2 = new CircleRB(
				0.0f, 0.6f,
				0.0f, 0.0f,
				0.08f,
				0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *cir3 = new CircleRB(
				0.0f, 0.4f,
				0.0f, 0.0f,
				0.08f,
				0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *cir4 = new CircleRB(
				0.0f, 0.2f,
				0.0f, 0.0f,
				0.08f,
				0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Shape *w = new Wall(kStandardWall);
	Shape *recW1 = new RectangleWall(
				0.0f, -0.9f,
				2.0f, 0.2f,
				0.0f,
				0.8f);
	Shape *recW2 = new RectangleWall(
				0.0f, 0.9f,
				2.0f, 0.2f,
				0.0f,
				0.8f);
	Shape *recW3 = new RectangleWall(
				-0.9f, 0.0f,
				0.2f, 1.5f,
				0.0f,
				0.8f);
	Shape *recW4 = new RectangleWall(
				0.9f, 0.0f,
				0.2f, 1.5f,
				0.0f,
				0.8f);
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
	board->addShape(recW1);
	board->addShape(recW2);
	board->addShape(recW3);
	board->addShape(recW4);
	board->addLeftPale(paleL);
	board->addRightPale(paleR);

	Renderer *r = new Renderer(&argc, argv, board);
	return 0;
}