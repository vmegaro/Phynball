#ifndef DEFORMABLEOBJECT_H_
#define DEFORMABLEOBJECT_H_
#include <vector>
#include "Eigen/Dense"
#include "Shape.h"
using namespace std;

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> MatrixXf;
typedef Eigen::Matrix<float, Eigen::Dynamic, 1> VectorXf;

/*
Subclass of shape designed to model deformable objects using Cauchy Strain and Implicit Euler as a time integration scheme
*/
class DeformableObject : public Shape {
public :
	DeformableObject(vector<float> _vlist,vector<int> _flist, vector<int> _contour, float _E,float _rho, float _nu, float _alpha, float _beta, float _e);
	// update all parameters of the objects and put the new values in 'newSh'
	void update(Shape *newSh);
	// create a 'collision' object regarding a collision occuring with vertex 'pointIndex' of 'collidingSh' on edge 'edgeIndex' of 'this'	
	void setCollisionResponse(Shape *collidingSh, const int &pointIndex,const int &edgeIndex, Collision *collision);
	// update the state of 'this' after a collision occurs on vertices in 'cv' with an impulse coefficient of 'impulseCoeff'
	// along the vector given by 'nx' and 'ny'. 'rx' and 'ry' are distances used to sompute the influence on the rotation of 'this'	
	void handleResponseImpulse(const float &nx, const float &ny,
const float &rx, const float &ry, const vector<int> &cv,const float &impulseCoeff);
	void ComputeStiffnessMatrixandMass();
	int nature(){return 2;};
	DeformableObject * clone();
	//vector of forces to be applied on every vertex
	VectorXf force;
	//vector of deformations of every vertex
	VectorXf u;
	//velocity of every vertex
	VectorXf velocity;
	//vector storing the indexes in 'vlist' of the vertices of the contour
	vector<int> contour;
	// elasticity coefficient used to control the resulting impulse in case of collision
	float e;
	float oneOverMass;

	static vector<int> FaceList_Rectangle();
	static vector<float> VertexList_Rectangle(float x,float y,float width,float height);
	static vector<int> Contour_Rectangle();
	static vector<int> FaceList_Circle();
	static vector<float> VertexList_Circle(float x,float y,float radius);
	static vector<int> Contour_Circle();
	static vector<int> FaceList_V();
	static vector<float> VertexList_V(float x,float y,float width,float height);
	static vector<int> Contour_V();

protected :
	//stiffness matrix
	MatrixXf K;
	//diagonal matrix where M(2i,2i) and M(2i+1,2i+1) are 1/mass[i]
	MatrixXf revMass;
	vector<float> mass;
	//original coordinates of all vertices at the beginning of the simulation
	vector<float> vlist;
	//face list index of the triangle mesh
	vector<int> flist;
	// solver used to compute new velocities during each update
	Eigen::ColPivHouseholderQR<MatrixXf> solver;
	//Young's modulus, Poisson's ratio, density, coefficients of Rayleigh damping
	float E, nu, rho, alpha, beta;
};

#endif /* DEFORMABLEOBJECT_H_ */
