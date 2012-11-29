#ifndef BOARD_H
#define BOARD_H

#include "Shape.h"
#include "Walls.h"

using namespace std;

class Board
{
public:
	Board(void);
	~Board(void);

	void addShape(Shape *s);
	void addWalls(Walls *w);

	void update();

	vector<Shape *> *shapes;
	vector<Shape *> *newShapes;

	Walls* walls;

protected:

	vector<Shape *> *aux;

	vector<Shape *> shapeVec1;
	vector<Shape *> shapeVec2;
};

#endif