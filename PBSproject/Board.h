#ifndef BOARD_H
#define BOARD_H

#include "Shape.h"
#include "Pale.h"
#include "Wall.h"
#include "PlayBall.h"

using namespace std;
/*
Main class containing all needed objects and methods to set up the game and 
update the position of objects and the score.
*/
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

	void moveLeftPale(bool b);
	void moveRightPale(bool b);

	void update();
	void updatePaleDirection(int paleType, int paleDir);
	// during each update, the new states of all dynamic shapes in 'shapes' are stored in 'newShapes' 
	// and the vectors 'shapes' and 'newShapes' are switched at the end of the update
	vector<Shape *> *shapes;
	vector<Shape *> *newShapes;
	vector<Wall *> *walls;

	void startGoalAnimation();
	void setGravityToGoalChars(float gravity);
	void reinitCharPositions();
	vector<Shape *> goalCharacters;

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
