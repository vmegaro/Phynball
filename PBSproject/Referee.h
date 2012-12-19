#ifndef C_Referee
#define C_Referee
#include "DeformableObject.h"

/*
A subclass of Deformable Object. The only difference here with the parent class is the texturing.
*/
class Referee: public DeformableObject{
public:
	Referee();

	virtual void update(Shape *newSh);

	virtual Referee * clone();

	virtual void draw();

protected:
};

#endif
