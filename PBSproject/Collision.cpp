#include "Collision.h"
#include "Shape.h"

Collision::Collision() {
					shapeA = NULL;
					shapeB = NULL;
					nx = 0.0f; ny = 0.0f;
					rxa = 0.0f; rya = 0.0f;
					rxb = 0.0f; ryb = 0.0f;
					j = 0.0f;
					resolved = 1;
}

Collision::Collision(Shape *_shapeA) {
					shapeA = _shapeA;
					shapeB = NULL;
					nx = 0.0f; ny = 0.0f;
					rxa = 0.0f; rya = 0.0f;
					rxb = 0.0f; ryb = 0.0f;
					j = 0.0f;
					resolved = 1;
}

Collision::Collision(Shape *_shapeA, Shape *_shapeB,
					float _nx, float _ny,
					float _rxa, float _rya,
					float _rxb, float _ryb,
					float _j) {
						shapeA = _shapeA;
						shapeB = _shapeB;
						nx = _nx; ny = _ny;
						rxa = _rxa; rya = _rya;
						rxb = _rxb; ryb = _ryb;
						j = _j;
						resolved = 1;
}

void Collision::resolve() {
	if(!resolved) {
		shapeA->handleResponseImpulse(nx,ny,rxa,rya,j);
		shapeB->handleResponseImpulse(nx,ny,rxb,ryb,-j);
		resolved = 1;
	}
}