#ifndef C_CharacterRB
#define C_CharacterRB
#include "RectangleRB.h"
#include <vector>

using namespace std;

class CharacterRB: public RectangleRB{
public:
	CharacterRB(char character,
				RungeKuttaODESolver *odeSolver);
	void reinit();
	virtual void draw();

protected:
	char character;
};

#endif