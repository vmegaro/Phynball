#ifndef C_Const
#define C_Const
#include <limits.h>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#define keyPress -32767
#define keyX 0x59
#define keyN 0x4F

#define totTimeStep 0.005f
#define intermediateSteps 5.0f

const float timeStep = totTimeStep/intermediateSteps;
const float inf = std::numeric_limits<float>::max();
const float eps = 0.00000001f;

enum wallTypes {
	kStandardWall = 0
};

enum paleTypes {
	kLeftPale = 0,
	kRightPale,
};

#define kPaleDownDir 0
#define kPaleUpDir 1

#define kg 9.81f

#endif