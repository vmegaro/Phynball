#include <cmath>
#include "DeformableObject.h"
#include "RigidBody.h"
#include "Constants.h"

Vector2f ComputeDerivatives(Vector2f x0,Vector2f x1,Vector2f x2){
	Vector2f grad;
	grad[0]=(x2[1]-x1[1])/((x1[0]-x0[0])*(x2[1]-x0[1])-(x1[1]-x0[1])*(x2[0]-x0[0]));
	grad[1]=(x1[0]-x2[0])/((x1[0]-x0[0])*(x2[1]-x0[1])-(x1[1]-x0[1])*(x2[0]-x0[0]));
	return grad;
}

DeformableObject::DeformableObject(vector<Vector2f> _vlist,vector<Vector3i> _flist, vector<int> _contour, float _E,float _rho, float _nu, float _alpha, float _beta,float _e){
	int N=_vlist.size();
	int n = _contour.size();
	vlist = _vlist;
	flist = _flist;
	force.resize(N);
	u.resize(N);
	previous_u.resize(N);
	velocity.resize(N);
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
	float totmass=0.0f;
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
		G+=x0*mass[ind0];
		G+=x1*mass[ind1];
		G+=x2*mass[ind2];
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
	G*=oneOverMass;
	length=(vlist[0]-G).length();
}

void DeformableObject::update(Shape* newSh){
	DeformableObject *newDO = (DeformableObject*) newSh;
	int n=u.size();
	float dt=timeStep;
	vector<Vector2f> accel (n);
	vector<Vector2f> temp (n);
	K.Mult(u,beta,velocity,temp);
	int i;
	Vector2f val;
	newDO->G=G;
	for(i=0;i<n;i++){
		accel[i][0]=(force[i][0]-temp[i][0])/mass[i]-alpha*velocity[i][0];
		accel[i][1]=(force[i][1]-temp[i][1])/mass[i]-alpha*velocity[i][1];
		newDO->u[i]=u[i]*2-previous_u[i]+accel[i]*(dt*dt); //position is now u(t+h)
		newDO->previous_u[i]=u[i]; //previous_position is now u(t)
		newDO->velocity[i]=(newDO->u[i]-newDO->previous_u[i])/dt; // u(t+h)-u(t)
		newDO->G+=(newDO->u[i]-newDO->previous_u[i])*mass[i]*oneOverMass;
		if(newDO->velocity[i][0]>0.1) newDO->velocity[i][0]=0.1;
		if(newDO->velocity[i][0]<-0.1) newDO->velocity[i][0]=-0.1;
		if(newDO->velocity[i][1]>0.1) newDO->velocity[i][1]=0.1;
		if(newDO->velocity[i][1]<-0.1) newDO->velocity[i][1]=-0.1;
		force[i][0]=0.0f;
		force[i][1]=0.0f;
	}
	for(i=0;i<nVertices;i++){
		newDO->vertices[2*i]=vlist[contour[i]][0]+newDO->u[contour[i]][0];
		newDO->vertices[2*i+1]=vlist[contour[i]][1]+newDO->u[contour[i]][1];
	}
}

void DeformableObject::setCollisionResponse(Shape *collidingSh, const int &pointIndex,const int &edgeIndex, Collision *collision){
	float nx,ny,r;
	float vabx, vaby;
	float rxa,rya,rxb,ryb;
	float xCollision,yCollision;
	float impulseCoeff;
	if(collidingSh->nature()==2){
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
		vabx=collidingDo->velocity.at(collidingDo->contour.at(pointIndex))[0]-(velocity.at(contour.at(edgeIndex))[0]+velocity.at(contour.at((edgeIndex+1)%nVertices))[0])/2.0f;
		vaby=collidingDo->velocity.at(collidingDo->contour.at(pointIndex))[1]-(velocity.at(contour.at(edgeIndex))[1]+velocity.at(contour.at((edgeIndex+1)%nVertices))[1])/2.0f;
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
		rxb = xCollision - G[0];
		ryb = yCollision - G[1];
		// set respective velocity
		vabx=collidingRb->xVel-(velocity.at(contour.at(edgeIndex))[0]+velocity.at(contour.at((edgeIndex+1)%nVertices))[0])/2.0f;
		vaby=collidingRb->yVel-(velocity.at(contour.at(edgeIndex))[1]+velocity.at(contour.at((edgeIndex+1)%nVertices))[1])/2.0f;
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
		force[cv[i]][0]=(nx*impulseCoeff-mass[cv[i]]*velocity[cv[i]][0])/(n*dt);
		force[cv[i]][1]=(ny*impulseCoeff-mass[cv[i]]*velocity[cv[i]][1])/(n*dt);
	}
}

DeformableObject * DeformableObject::clone(){
	return new DeformableObject(vlist,flist,contour,E,rho,nu,alpha,beta,e);
}