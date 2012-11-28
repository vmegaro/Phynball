#ifndef BOARD_H
#define BOARD_H

#include "RigidBody.h"
#include "Walls.h"

using namespace std;

class Board
{
public:
	Board(void);
	~Board(void);

	void addRigidBody(RigidBody *rb);
	void addWalls(Walls *w);

	void update();

	vector<RigidBody *> *rigidBodies;
	vector<RigidBody *> *newRigidBodies;

	Walls* walls;

protected:

	vector<RigidBody *> *aux;

	vector<RigidBody *> rigidBodyVec1;
	vector<RigidBody *> rigidBodyVec2;
};

#endif