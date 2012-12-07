#ifndef DEFORMABLEOBJECT_H_
#define DEFORMABLEOBJECT_H_
#include <vector>
#include "utilities.h"
#include "Shape.h"

class DeformableObject : public Shape {
public :
	DeformableObject(vector<Vector2f> _vlist,vector<Vector3i> _flist, vector<int> _contour, float _E,float _rho, float _nu, float _alpha, float _beta, float _e);
	void update(Shape *newSh);
	void setCollisionResponse(Shape *collidingSh, const int &pointIndex,const int &edgeIndex, Collision *collision);
	void handleResponseImpulse(const float &nx, const float &ny,
const float &rx, const float &ry, const vector<int> &cv,const float &impulseCoeff);
	void ComputeStiffnessMatrixandMass();
	int nature(){return 2;};
	DeformableObject * clone();

	vector<Vector2f> force;
	vector<Vector2f> u;
	vector<Vector2f> previous_u;
	vector<Vector2f> velocity;
	vector<int> contour;
	Vector2f G;
	float length;
	float e;
	float oneOverMass;
protected :
	SMatrixf K;
	vector<Vector2f> vlist;
	vector<Vector3i> flist;
	vector<float> mass;
	float E, nu, rho, alpha, beta;

};

#endif /* DEFORMABLEOBJECT_H_ */