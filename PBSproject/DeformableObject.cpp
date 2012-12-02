#include <cmath>
#include "DeformableObject.h"
#include "Constants.h"

Vector2f ComputeDerivatives(Vector2f x0,Vector2f x1,Vector2f x2){
	Vector2f grad;
	grad[0]=(x2[1]-x1[1])/((x1[0]-x0[0])*(x2[1]-x0[1])-(x1[1]-x0[1])*(x2[0]-x0[0]));
	grad[1]=(x1[0]-x2[0])/((x1[0]-x0[0])*(x2[1]-x0[1])-(x1[1]-x0[1])*(x2[0]-x0[0]));
	return grad;
}

DeformableObject::DeformableObject(vector<Vector2f> &_vlist,vector<Vector3i> &_flist, vector<int> &_contour, float _E,float _rho, float _nu, float _alpha, float _beta){
	int N=vlist.size();
	int n = _contour.size();
	vlist = _vlist;
	flist = _flist;
	force.resize(N);
	u.resize(N);
	previous_u.resize(N);
	velocity.resize(N);
	E = _E;
	rho = _rho;
	nu = _nu;
	nVertices = n;
	alpha = _alpha;
	beta = _beta;
	contour=_contour;
	for(int i=0; i<n; i++){
		vertices.push_back(vlist[_contour[i]][0]);
		vertices.push_back(vlist[_contour[i]][1]);
	}
	K.ClearResize(2*N);
	ComputeStiffnessMatrixandMass();
	 color[0] = 0.8;
	 color[1] = 0.6;
	 color[2] = 0.1;
}

void DeformableObject::ComputeStiffnessMatrixandMass(){
	int numf=flist.size();
	int i;
	for(i=0;i<numf;i++){
		int ind0=flist[i][0];
		int ind1=flist[i][1];
		int ind2=flist[i][2];
		Vector2f x0=vlist[ind0];
		Vector2f x1=vlist[ind1];
		Vector2f x2=vlist[ind2];
		Vector2f dN0=ComputeDerivatives(x0,x1,x2);
		Vector2f dN1=ComputeDerivatives(x1,x2,x0);
		Vector2f dN2=ComputeDerivatives(x2,x0,x1);
		float area=abs(((x0[0]-x1[0])*(x0[1]-x2[1])-(x0[0]-x2[0])*(x0[1]-x1[1])))/2;
		mass[ind0]+=rho*area/3.0f;
		mass[ind1]+=rho*area/3.0f;
		mass[ind2]+=rho*area/3.0f;
		//add K00;
		K(2*ind0,2*ind0)+=E*area*((1-nu)*dN0[0]*dN0[0]+(1-2*nu)*dN0[1]*dN0[1])/((1+nu)*(1-2*nu));
		K(2*ind0+1,2*ind0+1)+=E*area*((1-nu)*dN0[1]*dN0[1]+(1-2*nu)*dN0[0]*dN0[0])/((1+nu)*(1-2*nu));
		K(2*ind0+1,2*ind0)+=E*area*dN0[0]*dN0[1]*(1-nu)/((1+nu)*(1-2*nu));
		//add K11;
		K(2*ind1,2*ind1)+=E*area*((1-nu)*dN1[0]*dN1[0]+(1-2*nu)*dN1[1]*dN1[1])/((1+nu)*(1-2*nu));
		K(2*ind1+1,2*ind1+1)+=E*area*((1-nu)*dN1[1]*dN1[1]+(1-2*nu)*dN1[0]*dN1[0])/((1+nu)*(1-2*nu));
		K(2*ind1+1,2*ind1)+=E*area*dN1[0]*dN1[1]*(1-nu)/((1+nu)*(1-2*nu));
		//add K22;
		K(2*ind2,2*ind2)+=E*area*((1-nu)*dN2[0]*dN2[0]+(1-2*nu)*dN2[1]*dN2[1])/((1+nu)*(1-2*nu));
		K(2*ind2+1,2*ind2+1)+=E*area*((1-nu)*dN2[1]*dN2[1]+(1-2*nu)*dN2[0]*dN2[0])/((1+nu)*(1-2*nu));
		K(2*ind2+1,2*ind2)+=E*area*dN2[0]*dN2[1]*(1-nu)/((1+nu)*(1-2*nu));
		//add K01 or K10;
		if(ind0>ind1){
			K(2*ind0,2*ind1)+=E*area*((1-nu)*dN0[0]*dN1[0]+(1-2*nu)*dN0[1]*dN1[1])/((1+nu)*(1-2*nu));
			K(2*ind0+1,2*ind1+1)+=E*area*((1-nu)*dN0[1]*dN1[1]+(1-2*nu)*dN0[0]*dN1[0])/((1+nu)*(1-2*nu));
			K(2*ind0+1,2*ind1)+=E*area*(nu*dN0[1]*dN1[0]+(1-2*nu)*dN0[0]*dN1[1])/((1+nu)*(1-2*nu));
			K(2*ind0,2*ind1+1)+=E*area*(nu*dN0[0]*dN1[1]+(1-2*nu)*dN0[1]*dN1[0])/((1+nu)*(1-2*nu));
		}else{
			K(2*ind1,2*ind0)+=E*area*((1-nu)*dN0[0]*dN1[0]+(1-2*nu)*dN0[1]*dN1[1])/((1+nu)*(1-2*nu));
			K(2*ind1+1,2*ind0+1)+=E*area*((1-nu)*dN0[1]*dN1[1]+(1-2*nu)*dN0[0]*dN1[0])/((1+nu)*(1-2*nu));
			K(2*ind1+1,2*ind0)+=E*area*(nu*dN0[0]*dN1[1]+(1-2*nu)*dN0[1]*dN1[0])/((1+nu)*(1-2*nu));
			K(2*ind1,2*ind0+1)+=E*area*(nu*dN0[1]*dN1[0]+(1-2*nu)*dN0[0]*dN1[1])/((1+nu)*(1-2*nu));
		}
		//add K02 or K20;
		if(ind0>ind2){
			K(2*ind0,2*ind2)+=E*area*((1-nu)*dN0[0]*dN2[0]+(1-2*nu)*dN0[1]*dN2[1])/((1+nu)*(1-2*nu));
			K(2*ind0+1,2*ind2+1)+=E*area*((1-nu)*dN0[1]*dN2[1]+(1-2*nu)*dN0[0]*dN2[0])/((1+nu)*(1-2*nu));
			K(2*ind0+1,2*ind2)+=E*area*(nu*dN0[1]*dN2[0]+(1-2*nu)*dN0[0]*dN2[1])/((1+nu)*(1-2*nu));
			K(2*ind0,2*ind2+1)+=E*area*(nu*dN0[0]*dN2[1]+(1-2*nu)*dN0[1]*dN2[0])/((1+nu)*(1-2*nu));
		}else{
			K(2*ind2,2*ind0)+=E*area*((1-nu)*dN0[0]*dN2[0]+(1-2*nu)*dN0[1]*dN2[1])/((1+nu)*(1-2*nu));
			K(2*ind2+1,2*ind0+1)+=E*area*((1-nu)*dN0[1]*dN2[1]+(1-2*nu)*dN0[0]*dN2[0])/((1+nu)*(1-2*nu));
			K(2*ind2+1,2*ind0)+=E*area*(nu*dN0[0]*dN2[1]+(1-2*nu)*dN0[1]*dN2[0])/((1+nu)*(1-2*nu));
			K(2*ind2,2*ind0+1)+=E*area*(nu*dN0[1]*dN2[0]+(1-2*nu)*dN0[0]*dN2[1])/((1+nu)*(1-2*nu));
		}
		//add K12 or K21;
		if(ind1>ind2){
			K(2*ind1,2*ind2)+=E*area*((1-nu)*dN1[0]*dN2[0]+(1-2*nu)*dN1[1]*dN2[1])/((1+nu)*(1-2*nu));
			K(2*ind1+1,2*ind2+1)+=E*area*((1-nu)*dN1[1]*dN2[1]+(1-2*nu)*dN1[0]*dN2[0])/((1+nu)*(1-2*nu));
			K(2*ind1+1,2*ind2)+=E*area*(nu*dN1[1]*dN2[0]+(1-2*nu)*dN1[0]*dN2[1])/((1+nu)*(1-2*nu));
			K(2*ind1,2*ind2+1)+=E*area*(nu*dN1[0]*dN2[1]+(1-2*nu)*dN1[1]*dN2[0])/((1+nu)*(1-2*nu));
		}else{
			K(2*ind2,2*ind1)+=E*area*((1-nu)*dN1[0]*dN2[0]+(1-2*nu)*dN1[1]*dN2[1])/((1+nu)*(1-2*nu));
			K(2*ind2+1,2*ind1+1)+=E*area*((1-nu)*dN1[1]*dN2[1]+(1-2*nu)*dN1[0]*dN2[0])/((1+nu)*(1-2*nu));
			K(2*ind2+1,2*ind1)+=E*area*(nu*dN1[0]*dN2[1]+(1-2*nu)*dN1[1]*dN2[0])/((1+nu)*(1-2*nu));
			K(2*ind2,2*ind1+1)+=E*area*(nu*dN1[1]*dN2[0]+(1-2*nu)*dN1[0]*dN2[1])/((1+nu)*(1-2*nu));
		}
	}
}

void DeformableObject::update(Shape* newSh){
	int n=u.size();
	float dt=timeStep;
	vector<Vector2f> accel (n);
	vector<Vector2f> temp (n);
	K.Mult(u,beta,velocity,temp);
	int i;
	Vector2f val;
	for(i=0;i<n;i++){
		accel[i][0]=(force[i][0]-temp[i][0])/mass[i]-alpha*velocity[i][0];
		accel[i][1]=(force[i][1]-temp[i][1])/mass[i]-alpha*velocity[i][1];
		val=u[i]; //u(t)
		u[i]=u[i]*2-previous_u[i]+accel[i]*(dt*dt); //position is now u(t+h)
		previous_u[i]=val; //previous_position is now u(t)
		velocity[i]=(u[i]-previous_u[i])/dt; // u(t+h)-u(t)
	}
	for(i=0;i<nVertices;i++){
		vertices[2*i]=vlist[contour[i]][0]+u[contour[i]][0];
		vertices[2*i+1]=vlist[contour[i]][1]+u[contour[i]][1];
	}

}
