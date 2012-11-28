#ifndef C_Const
#define C_Const
#include <limits.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define totTimeStep 0.004f
#define intermediateSteps 2.0f

const float timeStep = totTimeStep/intermediateSteps;
const float inf = std::numeric_limits<float>::max();


#define g 9.81f

#endif