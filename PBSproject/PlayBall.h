#ifndef C_PlayBall
#define C_PlayBall
#include "CircleRB.h"
#include <vector>

using namespace std;

class PlayBall: public CircleRB{
public:
	PlayBall(RungeKuttaODESolver *solver);

	virtual void draw();

	virtual PlayBall * clone();

	virtual void update(Shape *newSh);

protected:

};

#endif