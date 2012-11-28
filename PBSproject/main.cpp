#include "Renderer.h"
#include "RectangleRB.h"
#include "CircleRB.h"
#include "Constants.h"
#include "Board.h"
#include "Walls.h"

int main(int argc, char** argv)
{
	Board *board = new Board();
	RungeKuttaODESolver *solver = new RungeKuttaODESolver(timeStep,(int)intermediateSteps);
	RigidBody *rec1 = new RectangleRB(
				0.0f, 0.5f,
				2.0f, -2.0f,
				0.5f, 1.0f,
				M_PI/3.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	RigidBody *rec2 = new RectangleRB(
				0.0f, 0.0f,
				0.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f, 1.0f,
				1.0f,
				solver);
	RigidBody *cir1 = new CircleRB(
				-0.7f, 0.8f,
				0.0f, 0.0f,
				0.1f,
				0.0f, 10.0f,
				1.0f, 0.0f, 1.0f,
				1.0f,
				solver);
	RigidBody *cir2 = new CircleRB(
				0.0f, 0.0f,
				0.0f, 0.0f,
				0.1f,
				0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				1.0f,
				solver);
	Walls *walls = new Walls(-1.0f,1.0f,-1.0f,1.0f);

	board->addRigidBody(rec1);
	//board->addRigidBody(rec2);
	//board->addRigidBody(cir1);
	//board->addRigidBody(cir2);
	board->addWalls(walls);

	Renderer *r = new Renderer(&argc, argv, board);
	return 0;
}