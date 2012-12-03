#include "Board.h"
#include <iostream>
#include "Constants.h"
#include <windows.h>
#include <fstream>

bool PolygonIntersectionTest(const vector<float> &p,const vector<float> &q, vector<int> &resp, vector<int> &resq){
	int m=p.size()/2;
	int n=q.size()/2;
	int i,j,k,l;
	float x,y,det1,det2;
	bool odd = false;
	for(i=0;i<m;i++){
		x=p[2*i];
		y=p[2*i+1];
		k=n-1;
		for(j=0;j<n;j++){
			if ((((q[2*j+1]<y)&&(q[2*k+1]>=y))||((q[2*k+1]<y)&&(q[2*j+1]>=y)))&&((q[2*j]<=x)||(q[2*k]<=x))) {
			      if (q[2*j]+(y-q[2*j+1])/(q[2*k+1]-q[2*j+1])*(q[2*k]-q[2*j])<x) odd=!odd;
			}
			k=j;
		}
		if(odd){
			resp.push_back(i);
			l=(i+1)%m;
			k=n-1;
			for(j=0;j<n;j++){
				det1=((q[2*j+1]-p[2*l+1])*(p[2*i]-p[2*l])-(q[2*j]-p[2*l])*(p[2*i+1]-p[2*l+1]))*((q[2*k+1]-p[2*l+1])*(p[2*i]-p[2*l])-(q[2*k]-p[2*l])*(p[2*i+1]-p[2*l+1]));
				det2=((p[2*i+1]-q[2*k+1])*(q[2*j]-q[2*k])-(p[2*i]-q[2*k])*(q[2*j+1]-q[2*k+1]))*((p[2*l+1]-q[2*k+1])*(q[2*j]-q[2*k])-(p[2*l]-q[2*k])*(q[2*j+1]-q[2*k+1]));
				if((det1<=0)&&(det2<=0)){
					resq.push_back(k);
					resq.push_back(j);
					return true;
				}
				k=j;
			}
			l=(m+i-1)%m;
			k=n-1;
			for(j=0;j<n;j++){
				det1=((q[2*j+1]-p[2*l+1])*(p[2*i]-p[2*l])-(q[2*j]-p[2*l])*(p[2*i+1]-p[2*l+1]))*((q[2*k+1]-p[2*l+1])*(p[2*i]-p[2*l])-(q[2*k]-p[2*l])*(p[2*i+1]-p[2*l+1]));
				det2=((p[2*i+1]-q[2*k+1])*(q[2*j]-q[2*k])-(p[2*i]-q[2*k])*(q[2*j+1]-q[2*k+1]))*((p[2*l+1]-q[2*k+1])*(q[2*j]-q[2*k])-(p[2*l]-q[2*k])*(q[2*j+1]-q[2*k+1]));
				if((det1<=0)&&(det2<=0)){
					resq.push_back(k);
					resq.push_back(j);
					return true;
				}
				k=j;
			}			
			resq.push_back(k-1);
			resq.push_back(j-1);
			return true;
		}
	}
	for(i=0;i<n;i++){
		x=q[2*i];
		y=q[2*i+1];
		k=m-1;
		for(j=0;j<m;j++){
			if ((((p[2*j+1]<y)&&(p[2*k+1]>=y))||((p[2*k+1]<y)&&(p[2*j+1]>=y)))&&((p[2*j]<=x)||(p[2*k]<=x))) {
			      if (p[2*j]+(y-p[2*j+1])/(p[2*k+1]-p[2*j+1])*(p[2*k]-p[2*j])<x) odd=!odd;
			}
			k=j;
		}
		if(odd){
			resq.push_back(i);
			l=(i+1)%n;
			k=m-1;
			for(j=0;j<m;j++){
				det1=((p[2*j+1]-q[2*l+1])*(q[2*i]-q[2*l])-(p[2*j]-q[2*l])*(q[2*i+1]-q[2*l+1]))*((p[2*k+1]-q[2*l+1])*(q[2*i]-q[2*l])-(p[2*k]-q[2*l])*(q[2*i+1]-q[2*l+1]));
				det2=((q[2*i+1]-p[2*k+1])*(p[2*j]-p[2*k])-(q[2*i]-p[2*k])*(p[2*j+1]-p[2*k+1]))*((q[2*l+1]-p[2*k+1])*(p[2*j]-p[2*k])-(q[2*l]-p[2*k])*(p[2*j+1]-p[2*k+1]));
				if((det1<=0)&&(det2<=0)){
					resp.push_back(k);
					resp.push_back(j);
					return true;
				}
				k=j;
			}
			l=(n+i-1)%n;
			k=m-1;
			for(j=0;j<m;j++){
				det1=((p[2*j+1]-q[2*l+1])*(q[2*i]-q[2*l])-(p[2*j]-q[2*l])*(q[2*i+1]-q[2*l+1]))*((p[2*k+1]-q[2*l+1])*(q[2*i]-q[2*l])-(p[2*k]-q[2*l])*(q[2*i+1]-q[2*l+1]));
				det2=((q[2*i+1]-p[2*k+1])*(p[2*j]-p[2*k])-(q[2*i]-p[2*k])*(p[2*j+1]-p[2*k+1]))*((q[2*l+1]-p[2*k+1])*(p[2*j]-p[2*k])-(q[2*l]-p[2*k])*(p[2*j+1]-p[2*k+1]));
				if((det1<=0)&&(det2<=0)){
					resp.push_back(k);
					resp.push_back(j);
					return true;
				}
				k=j;
			}			
			resp.push_back(k-1);
			resp.push_back(j-1);
			return true;
		}
	}
	return false;
}

Board::Board(){
	shapes = &shapeVec1;
	newShapes = &shapeVec2;
}

Board::~Board(){
}

void Board::addShape(Shape *s) {
	shapeVec1.push_back(s);
	shapeVec2.push_back(s->clone());
}

void Board::addLeftPale(Shape *p) {
	shapeVec1.push_back(p);
	shapeVec2.push_back(p);
	Pale *lp = (Pale *)p;
	leftPale = lp;
}

void Board::addRightPale(Shape *p) {
	shapeVec1.push_back(p);
	shapeVec2.push_back(p);
	Pale *rp = (Pale *)p;
	rightPale = rp;
}

void Board::updatePaleDirection(int paleType, int paleDir) {
	if(kPaleDownDir == paleDir) {
		if(paleType == kLeftPale) leftPale->setGoDown();
		else rightPale->setGoDown();
	}else {
		if(paleType == kLeftPale) leftPale->setGoUp();
		else rightPale->setGoUp();
	}
}

int collisionInd;
float cdvx, cdvy, cdva, cimp;
void Board::update() {

	// Iteration
	for(int t = 0; t < intermediateSteps; t++) {
		// Update position and velocities
		vector<Shape *>::iterator it1 = shapes->begin(),
									  it2 = newShapes->begin();
		for(;it1 != shapes->end();++it1,++it2){
			(*it1)->update(*it2); // timestep integration
		}

		collisions.clear();

		vector<Shape *>::iterator sit1, sit2, nsit1, nsit2;
		vector<int> resp, resq;
		for(sit1 = shapes->begin() ,nsit1 = newShapes->begin(), collisionInd = 0;nsit1 != newShapes->end();++sit1, ++nsit1, collisionInd++) {
			for(sit2 = sit1+1, nsit2 = nsit1+1; nsit2 != newShapes->end();++sit2, ++nsit2) {
				if(PolygonIntersectionTest((*nsit1)->vertices,(*nsit2)->vertices,resp,resq)) {
					Collision *collision = new Collision();
					if(resp.size() == 2) {
						(*nsit1)->setCollisionResponse(
													*nsit2,
													(*nsit2)->vertices.at(resq.at(0)*2),
													(*nsit2)->vertices.at(resq.at(0)*2+1),
													resp.at(0),
													collision);
					}else {
						(*nsit2)->setCollisionResponse(
													*nsit1,
													(*nsit1)->vertices.at(resp.at(0)*2),
													(*nsit1)->vertices.at(resp.at(0)*2+1),
													resq.at(0),
													collision);
					}
					collisions.push_back(collision);
					resp.clear();resq.clear();
				}
			}
		}

		// Update using impulses
		vector<Collision *>::iterator colIt = collisions.begin();
		for(;colIt != collisions.end();++colIt) {
			(*colIt)->resolve();
		}

		// Swap buffers
		aux = shapes;
		shapes = newShapes;
		newShapes = aux;
	}
	if(GetAsyncKeyState(VkKeyScan('x')) <= keyPress) leftPale->setGoUp();
	else leftPale->setGoDown();
	if(GetAsyncKeyState(VkKeyScan('n')) <= keyPress) rightPale->setGoUp();
	else rightPale->setGoDown();
}