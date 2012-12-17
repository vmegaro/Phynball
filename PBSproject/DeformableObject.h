#ifndef DEFORMABLEOBJECT_H_
#define DEFORMABLEOBJECT_H_
#include <vector>
#include "Eigen/Dense"
#include "Shape.h"
using namespace std;

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXf;
typedef Eigen::Matrix<float, Eigen::Dynamic, 1> VectorXf;

class DeformableObject : public Shape {
public :
	DeformableObject(vector<float> _vlist,vector<int> _flist, vector<int> _contour, float _E,float _rho, float _nu, float _alpha, float _beta, float _e);
	void update(Shape *newSh);
	void setCollisionResponse(Shape *collidingSh, const int &pointIndex,const int &edgeIndex, Collision *collision);
	void handleResponseImpulse(const float &nx, const float &ny,
const float &rx, const float &ry, const vector<int> &cv,const float &impulseCoeff);
	void ComputeStiffnessMatrixandMass();
	int nature(){return 2;};
	DeformableObject * clone();

	VectorXf force;
	VectorXf u;
	VectorXf velocity;
	vector<int> contour;
	float length;
	float e;
	float oneOverMass;
protected :
	MatrixXf K;
	MatrixXf revMass;
	vector<float> mass;
	vector<float> vlist;
	vector<int> flist;
	Eigen::ColPivHouseholderQR<MatrixXf> solver;
	float E, nu, rho, alpha, beta;

};

#endif /* DEFORMABLEOBJECT_H_ */
