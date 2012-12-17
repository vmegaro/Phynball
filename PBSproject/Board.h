#ifndef BOARD_H
#define BOARD_H

#include "Shape.h"
#include "Pale.h"
#include "Wall.h"
#include "PlayBall.h"

using namespace std;

class Board
{
public:
	Board();
	~Board(void);

	void addShape(Shape *s);
	void addWall(Shape *w);
	void addLeftPale(Shape *p);
	void addRightPale(Shape *p);
	void addPlayBall(Shape *_playBall);

	void update();

	void updatePaleDirection(int paleType, int paleDir);

	vector<Shape *> *shapes;
	vector<Shape *> *newShapes;
	vector<Wall *> *walls;

	Pale *leftPale;
	Pale *rightPale;

	int playerScore;
	int otherTeamScore;
	void setScore();
	void restoreBallPosition();

	PlayBall *playBall;


protected:

	bool polygonIntersectionTest(Shape *sh1, Shape *sh2, vector<int> &resp, vector<int >&resq);

	vector<Shape *> *aux;

	vector<Shape *> shapeVec1;
	vector<Shape *> shapeVec2;

	vector<Collision *> collisions;
	vector<Wall *> wallsVec;
};

#endif