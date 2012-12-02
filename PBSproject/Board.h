#ifndef BOARD_H
#define BOARD_H

#include "Shape.h"
#include "Pale.h"

using namespace std;

class Board
{
public:
	Board(void);
	~Board(void);

	void addShape(Shape *s);
	void addLeftPale(Shape *p);
	void addRightPale(Shape *p);

	void update();

	void updatePaleDirection(int paleType, int paleDir);

	vector<Shape *> *shapes;
	vector<Shape *> *newShapes;

protected:

	vector<Shape *> *aux;

	vector<Shape *> shapeVec1;
	vector<Shape *> shapeVec2;

	Pale *leftPale;
	Pale *rightPale;

	vector<Collision *> collisions;
};

#endif