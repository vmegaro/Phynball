#include <cmath>
#include "DeformableObject.h"
#include <cmath>
#include "DeformableObject.h"
#include "RigidBody.h"
#include "Constants.h"

vector<int> DeformableObject::FaceList_Rectangle(){
	vector<int> face (48);
	face[0]=0;face[1]=1;face[2]=5;
	face[3]=1;face[4]=2;face[5]=6;
	face[6]=2;face[7]=3;face[8]=7;
	face[9]=3;face[10]=4;face[11]=8;
	face[12]=1;face[13]=6;face[14]=5;
	face[15]=2;face[16]=7;face[17]=6;
	face[18]=3;face[19]=8;face[20]=7;
	face[21]=5;face[22]=6;face[23]=10;
	face[24]=6;face[25]=7;face[26]=11;
	face[27]=7;face[28]=8;face[29]=12;
	face[30]=5;face[31]=10;face[32]=9;
	face[33]=6;face[34]=11;face[35]=10;
	face[36]=7;face[37]=12;face[38]=11;
	face[39]=8;face[40]=13;face[41]=12;
	face[42]=0;face[43]=5;face[44]=9;
	face[45]=4;face[46]=13;face[47]=8;
	return face;
}

vector<float> DeformableObject::VertexList_Rectangle(float x,float y,float width,float height){
	vector<float> pos (28);
	float w=width/4.0f;
	float h=height/2.0f;
	pos[0]=x;pos[1]=y;
	pos[2]=x+w;pos[3]=y;
	pos[4]=x+2*w;pos[5]=y;
	pos[6]=x+3*w;pos[7]=y;
	pos[8]=x+4*w;pos[9]=y;
	pos[10]=x+0.5f*w;pos[11]=y+h;
	pos[12]=x+1.5f*w;pos[13]=y+h;
	pos[14]=x+2.5f*w;pos[15]=y+h;
	pos[16]=x+3.5f*w;pos[17]=y+h;
	pos[18]=x;pos[19]=y+2*h;
	pos[20]=x+w;pos[21]=y+2*h;
	pos[22]=x+2*w;pos[23]=y+2*h;
	pos[24]=x+3*w;pos[25]=y+2*h;
	pos[26]=x+4*w;pos[27]=y+2*h;
	return pos;
}

vector<int> DeformableObject::Contour_Rectangle(){
	vector<int> contour (10);
	contour[0]=0;
	contour[1]=1;
	contour[2]=2;
	contour[3]=3;
	contour[4]=4;
	contour[5]=13;
	contour[6]=12;
	contour[7]=11;
	contour[8]=10;
	contour[9]=9;
	return contour;
}

vector<int> DeformableObject::FaceList_Circle(){
	vector<int> face (24);
	face[0]=0;face[1]=1;face[2]=2;
	face[3]=0;face[4]=2;face[5]=3;
	face[6]=0;face[7]=3;face[8]=4;
	face[9]=0;face[10]=4;face[11]=5;
	face[12]=0;face[13]=5;face[14]=6;
	face[15]=0;face[16]=6;face[17]=7;
	face[18]=0;face[19]=7;face[20]=8;
	face[21]=0;face[22]=8;face[23]=1;
	return face;
}

vector<float> DeformableObject::VertexList_Circle(float x,float y,float radius){
	vector<float> pos (18);
	pos[0]=x; pos[1]=y;
	pos[2]=x; pos[3]=y+radius;
	pos[4]=x+0.66f*radius; pos[5]=y+0.66f*radius;
	pos[6]=x+radius; pos[7]=y;
	pos[8]=x+0.66f*radius; pos[9]=y-0.66f*radius;
	pos[10]=x; pos[11]=y-radius;
	pos[12]=x-0.66f*radius; pos[13]=y-0.66f*radius;
	pos[14]=x-radius; pos[15]=y;
	pos[16]=x-0.66f*radius; pos[17]=y+0.66f*radius;
	return pos;
}

vector<int> DeformableObject::Contour_Circle(){
	vector<int> contour (8);
	contour[0]=1;
	contour[1]=2;
	contour[2]=3;
	contour[3]=4;
	contour[4]=5;
	contour[5]=6;
	contour[6]=7;
	contour[7]=8;
	return contour;
}

vector<int> DeformableObject::FaceList_V(){
	vector<int> face (33);
	face[0]=0;face[1]=1;face[2]=2;
	face[3]=0;face[4]=1;face[5]=3;
	face[6]=0;face[7]=2;face[8]=4;
	face[9]=0;face[10]=3;face[11]=7;
	face[12]=0;face[13]=4;face[14]=8;
	face[15]=3;face[16]=5;face[17]=7;
	face[18]=4;face[19]=6;face[20]=8;
	face[21]=5;face[22]=7;face[23]=11;
	face[24]=6;face[25]=8;face[26]=12;
	face[27]=5;face[28]=9;face[29]=11;
	face[30]=6;face[31]=10;face[32]=12;
	return face;
}

vector<float> DeformableObject::VertexList_V(float x,float y,float width,float height){
	vector<float> pos (26);
	float w = width/8.0f;
	float h = height/5.0f;
	pos[0]=x; pos[1]=y;
	pos[2]=x-w; pos[3]=y-h;
	pos[4]=x+w; pos[5]=y-h;
	pos[6]=x-2.0f*w; pos[7]=y;
	pos[8]=x+2.0f*w; pos[9]=y;
	pos[10]=x-3.0f*w; pos[11]=y+2.0f*h;
	pos[12]=x+3.0f*w; pos[13]=y+2.0f*h;
	pos[14]=x-2.0f*w; pos[15]=y+2.0f*h;
	pos[16]=x+2.0f*w; pos[17]=y+2.0f*h;
	pos[18]=x-4.0f*w; pos[19]=y+4.0f*h;
	pos[20]=x+4.0f*w; pos[21]=y+4.0f*h;
	pos[22]=x-3.0f*w; pos[23]=y+4.0f*h;
	pos[24]=x+3.0f*w; pos[25]=y+4.0f*h;
	return pos;
}

vector<int> DeformableObject::Contour_V(){
	vector<int> contour (13);
	contour[0]=1;
	contour[1]=2;
	contour[2]=4;
	contour[3]=6;
	contour[4]=10;
	contour[5]=12;
	contour[6]=8;
	contour[7]=0;
	contour[8]=7;
	contour[9]=11;
	contour[10]=9;
	contour[11]=5;
	contour[12]=3;
	return contour;
}

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
