#ifndef BOARD_H
#define BOARD_H

#include "Shape.h"

using namespace std;

class Board
{
public:
	Board(void);
	~Board(void);

	void addShape(Shape *s);

	void update();

	vector<Shape *> *shapes;
	vector<Shape *> *newShapes;

protected:

	vector<Shape *> *aux;

	vector<Shape *> shapeVec1;
	vector<Shape *> shapeVec2;
};

#endif