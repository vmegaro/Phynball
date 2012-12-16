#include <cmath>
#include "DeformableObject.h"
#include <cmath>
#include "DeformableObject.h"
#include "RigidBody.h"
#include "Constants.h"

void ComputeDerivatives(float* x0,float* x1,float* x2,float* grad){
	grad[0]=(x2[1]-x1[1])/((x1[0]-x0[0])*(x2[1]-x0[1])-(x1[1]-x0[1])*(x2[0]-x0[0]));
	grad[1]=(x1[0]-x2[0])/((x1[0]-x0[0])*(x2[1]-x0[1])-(x1[1]-x0[1])*(x2[0]-x0[0]));
}

DeformableObject::DeformableObject(vector<float> _vlist,vector<int> _flist, vector<int> _contour, float _E,float _rho, float _nu, float _alpha, float _beta,float _e){
	int N=_vlist.size()/2;
	int n = _contour.size();
	float dt=timeStep;
	vlist = _vlist;
	flist = _flist;
	force.resize(2*N);
	force.setZero();
	u.resize(2*N);
	u.setZero();
	velocity.resize(2*N);
	velocity.setZero();
	mass.resize(N);
	E = _E;
	rho = _rho;
	nu = _nu;
	nVertices = n;
	alpha = _alpha;
	beta = _beta;
	e=_e;
	contour=_contour;
	for(int i=0; i<n; i++){
		vertices.push_back(vlist[2*_contour[i]]);
		vertices.push_back(vlist[2*_contour[i]+1]);
	}
	K.resize(2*N,2*N);
	K.setZero();
	ComputeStiffnessMatrixandMass();
	color[0] = 0.8;
	color[1] = 0.6;
	color[2] = 0.1;
	MatrixXf I;
	I.resize(2*N,2*N);
	I.setIdentity();
	revMass.resize(2*N,2*N);
	revMass.setZero();
	for(int i=0;i<N;i++){
		revMass(2*i,2*i)=1/mass[i];
		revMass(2*i+1,2*i+1)=revMass(2*i,2*i);
	}
	Eigen::ColPivHouseholderQR<MatrixXf> _solver((1+alpha*dt)*I+dt*(beta+dt)*revMass*K);
	solver=_solver;
	criticalRadius=(vlist[2*contour[0]]-xPos)*(vlist[2*contour[0]]-xPos)+(vlist[2*contour[0]+1]-yPos)*(vlist[2*contour[0]+1]-yPos);
	for(int i=1;i<n;i++){
		float radius=(vlist[2*contour[i]]-xPos)*(vlist[2*contour[i]]-xPos)+(vlist[2*contour[i]+1]-yPos)*(vlist[2*contour[i]+1]-yPos);
		if(radius>criticalRadius) criticalRadius=radius;
	}
	criticalRadius=sqrt(criticalRadius);
}

void DeformableObject::ComputeStiffnessMatrixandMass(){
	int numf=flist.size()/3;
	int i;
	float totmass=0.0f;
	for(i=0;i<numf;i++){
		int ind0=flist[3*i];
		int ind1=flist[3*i+1];
		int ind2=flist[3*i+2];
		float x0 [2]= {vlist[2*ind0],vlist[2*ind0+1]};
		float x1 [2]= {vlist[2*ind1],vlist[2*ind1+1]};
		float x2 [2]= {vlist[2*ind2],vlist[2*ind2+1]};
		float dN0 [2];
		ComputeDerivatives(x0,x1,x2,dN0);
		float dN1 [2];
		ComputeDerivatives(x1,x2,x0,dN1);
		float dN2 [2];
		ComputeDerivatives(x2,x0,x1,dN2);
		float area=abs(((x0[0]-x1[0])*(x0[1]-x2[1])-(x0[0]-x2[0])*(x0[1]-x1[1])))/2;
		mass[ind0]+=rho*area/3.0f;
		mass[ind1]+=rho*area/3.0f;
		mass[ind2]+=rho*area/3.0f;
		xPos+=x0[0]*mass[ind0]+x1[0]*mass[ind1]+x2[0]*mass[ind2];
		yPos+=x0[1]*mass[ind0]+x1[1]*mass[ind1]+x2[1]*mass[ind2];
		totmass+=rho*area;
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
	oneOverMass = 1.0f/totmass;
	xPos*=oneOverMass;
	yPos*=oneOverMass;
}

void DeformableObject::update(Shape* newSh){
	DeformableObject *newDO = (DeformableObject*) newSh;
	float dt=timeStep;
	newDO->velocity = solver.solve(velocity+dt*revMass*(force-K*u));
	for(int i=0;i<mass.size();i++){
		if(newDO->velocity(2*i)>clamp) newDO->velocity(2*i)=clamp;
		if(newDO->velocity(2*i)<-clamp) newDO->velocity(2*i)=-clamp;
		if(newDO->velocity(2*i+1)>clamp) newDO->velocity(2*i+1)=clamp;
		if(newDO->velocity(2*i+1)<-clamp) newDO->velocity(2*i+1)=-clamp;
	}
	newDO->u=u+dt*newDO->velocity;
	for(int i=0;i<mass.size();i++){
		newDO->xPos+=(newDO->u(2*i)-u(2*i))*mass[i]*oneOverMass;
		newDO->yPos+=(newDO->u(2*i+1)-u(2*i+1))*mass[i]*oneOverMass;
	}
	force.setZero();
	for(int i=0;i<nVertices;i++){
		newDO->vertices[2*i]=vlist[2*contour[i]]+newDO->u(contour[i]*2);
		newDO->vertices[2*i+1]=vlist[2*contour[i]+1]+newDO->u(contour[i]*2+1);
		if((newDO->vertices[2*i+1]-yPos)*(newDO->vertices[2*i+1]-yPos)+(newDO->vertices[2*i]-xPos)*(newDO->vertices[2*i]-xPos)>criticalRadius*criticalRadius){
			criticalRadius=sqrt((newDO->vertices[2*i+1]-yPos)*(newDO->vertices[2*i+1]-yPos)+(newDO->vertices[2*i]-xPos)*(newDO->vertices[2*i]-xPos));
		}		
	}
}

void DeformableObject::setCollisionResponse(Shape *collidingSh, const int &pointIndex,const int &edgeIndex, Collision *collision){
	float nx,ny,r;
	float vabx, vaby;
	float rxa,rya,rxb,ryb;
	float xCollision,yCollision;
	float impulseCoeff;
	if(collidingSh->nature() == kShapeNatureDO){
		DeformableObject *collidingDo = (DeformableObject*) collidingSh;
		xCollision=collidingDo->vertices.at(pointIndex*2);
		yCollision=collidingDo->vertices.at(pointIndex*2+1);
		// compute unit normal: nx = dy, ny = -dx
		nx = vertices.at((edgeIndex+1)%nVertices*2+1)-vertices.at((edgeIndex)*2+1);
		ny = -(vertices.at((edgeIndex+1)%nVertices*2)-vertices.at((edgeIndex)*2));
		r = sqrt(nx*nx+ny*ny);
		nx /= r;
		ny /= r;
		if(nx*(xCollision-vertices.at(edgeIndex*2))+ny*(yCollision-vertices.at(edgeIndex*2+1))>0){
			nx=-nx;
			ny=-ny;
		}
		// set respective velocity
		vabx=collidingDo->velocity(collidingDo->contour.at(pointIndex)*2)-(velocity(contour.at(edgeIndex)*2)+velocity(contour.at((edgeIndex+1)%nVertices)*2))/2.0f;
		vaby=collidingDo->velocity(collidingDo->contour.at(pointIndex)*2+1)-(velocity(contour.at(edgeIndex)*2+1)+velocity(contour.at((edgeIndex+1)%nVertices)*2+1))/2.0f;
		if(vabx*nx+vaby*ny > 0.0f) return;
		impulseCoeff = -((1.0f+(e+collidingDo->e)/2.0f)*(vabx*nx+vaby*ny))/(oneOverMass+collidingDo->oneOverMass);
		// Set up collision object
		collision->shapeB = this;
		collision->shapeA = collidingDo;
		collision->nx = nx;
		collision->ny = ny;
		collision->rxa = 0;
		collision->rya = 0;
		collision->cva.push_back(contour.at(edgeIndex));
		collision->cva.push_back(contour.at((edgeIndex+1)%nVertices));
		collision->rxb = 0;
		collision->ryb = 0;
		collision->cvb.push_back(collidingDo->contour.at(pointIndex));
		collision->j = impulseCoeff;
		collision->resolved = 0;
	}else{
		RigidBody *collidingRb = (RigidBody *)collidingSh;
		xCollision=collidingRb->vertices.at(pointIndex*2);
		yCollision=collidingRb->vertices.at(pointIndex*2+1);
		// compute unit normal: nx = dy, ny = -dx
		nx = vertices.at((edgeIndex+1)%nVertices*2+1)-vertices.at((edgeIndex)*2+1);
		ny = -(vertices.at((edgeIndex+1)%nVertices*2)-vertices.at((edgeIndex)*2));
		r = sqrt(nx*nx+ny*ny);
		nx /= r;
		ny /= r;
		if(nx*(xCollision-vertices.at(edgeIndex*2))+ny*(yCollision-vertices.at(edgeIndex*2+1))>0){
			nx=-nx;
			ny=-ny;
		}
		rxa = xCollision - collidingRb->xPos;
		rya = yCollision - collidingRb->yPos;
		rxb = xCollision - xPos;
		ryb = yCollision - yPos;
		// set respective velocity
		vabx=collidingRb->xVel-(velocity(contour.at(edgeIndex)*2)+velocity(contour.at((edgeIndex+1)%nVertices)*2))/2.0f;
		vaby=collidingRb->yVel-(velocity(contour.at(edgeIndex)*2+1)+velocity(contour.at((edgeIndex+1)%nVertices)*2+1))/2.0f;
		if(vabx*nx+vaby*ny > 0.0f) return;
		impulseCoeff = -((1.0f+(e+collidingRb->e)/2.0f)*(vabx*nx+vaby*ny))/(oneOverMass+collidingRb->oneOverMass);
		// Set up collision object
		collision->shapeB = this;
		collision->shapeA = collidingRb;
		collision->nx = nx;
		collision->ny = ny;
		collision->rxa = rxa;
		collision->rya = rya;
		collision->rxb = rxb;
		collision->ryb = ryb;
		collision->cvb.push_back(contour.at(edgeIndex));
		collision->cvb.push_back(contour.at((edgeIndex+1)%nVertices));
		collision->j = impulseCoeff;
		collision->resolved = 0;
	}
}

void DeformableObject::handleResponseImpulse(const float &nx, const float &ny,
const float &rx, const float &ry, const vector<int> &cv, const float &impulseCoeff){
	int n = cv.size();
	float dt=timeStep;
	for(int i=0;i<n;i++){
		force(cv[i]*2)=(nx*impulseCoeff-velocity(cv[i]*2)*mass[cv[i]])/(n*dt);
		force(cv[i]*2+1)=(ny*impulseCoeff-velocity(cv[i]*2+1)*mass[cv[i]])/(n*dt);
	}
}

DeformableObject * DeformableObject::clone(){
	return new DeformableObject(vlist,flist,contour,E,rho,nu,alpha,beta,e);
}
