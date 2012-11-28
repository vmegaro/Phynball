#include "Board.h"

bool PolygonIntersectionTest(vector<float> &p,vector<float> &q,pair<vector<int>, vector<int> > res){
	int m=p.size()/2;
	int n=q.size()/2;
	int i,j,k;
	float x,y;
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
			res.first.push_back(i);
			res.second.push_back(j);
			res.second.push_back(k);
			return true;
		}
	}
	for(i=0;i<n;i++){
		x=q[2*i];
		y=q[2*i+1];
		k=n-1;
		for(j=0;j<m;j++){
			if ((((p[2*j+1]<y)&&(p[2*k+1]>=y))||((p[2*k+1]<y)&&(p[2*j+1]>=y)))&&((p[2*j]<=x)||(p[2*k]<=x))) {
			      if (p[2*j]+(y-p[2*j+1])/(p[2*k+1]-p[2*j+1])*(p[2*k]-p[2*j])<x) odd=!odd;
			}
			k=j;
		}
		if(odd){
			res.first.push_back(j);
			res.first.push_back(k);
			res.second.push_back(i);
			return true;
		}
	}
	return false;
}

Board::Board(){
	rigidBodies = &rigidBodyVec1;
	newRigidBodies = &rigidBodyVec2;
}

Board::~Board(){
}

void Board::addRigidBody(RigidBody *rb) {
	rigidBodyVec1.push_back(rb);
	rigidBodyVec2.push_back(rb->clone());
}

void Board::addWalls(Walls *w) {
	walls = w;
}

void Board::update() {
	// Update position and velocities
	vector<RigidBody *>::iterator it1 = rigidBodies->begin(),
								  it2 = newRigidBodies->begin();
	for(;it1 != rigidBodies->end();++it1,++it2){
		(*it1)->update(*it2);
	}

	// Find walls collisions
	float vx,vy;
	it2 = newRigidBodies->begin();
	for(;it2 != newRigidBodies->end();++it2){
		for(int vInd = 0; vInd < (*it2)->nVertices; vInd++) {
			vx = (*it2)->vertices.at(vInd*2);
			vy = (*it2)->vertices.at(vInd*+1);
			// Check left and right walls
			if(vx <= walls->x1Pos) {
				(*it2)->xVel = abs((*it2)->xVel);
			}else if(vx >= walls->x2Pos) {
				(*it2)->xVel = -abs((*it2)->xVel);
			}

			// Check lower and upper walls
			if(vy <= walls->y1Pos) {
				(*it2)->yVel = abs((*it2)->yVel);
			}else if(vy >= walls->y2Pos) {
				(*it2)->yVel = -abs((*it2)->yVel);
			}
		}
	}

	// Apply potential forces
	float c1x,c1y,c2x,c2y;
	float r2;
	it1 = newRigidBodies->begin();
	for(;it1 != newRigidBodies->end();++it1){
		c1x = (*it1)->xPos;
		c1y = (*it1)->yPos;
		for(it2 = it1+1;it2 != newRigidBodies->end();++it2){
			c2x = (*it2)->xPos;
			c2y = (*it2)->xPos;

			(*it1)->Rx = c2x-c1x;
			(*it1)->Ry = c2y-c1y;
			r2 = (*it1)->Rx*(*it1)->Rx+(*it1)->Ry*(*it1)->Ry;
			(*it1)->Tx = 4.0f*(*it1)->Rx/r2;
			(*it1)->Ty = 4.0f*(*it1)->Ry/r2;
		}
	}

	// Swap buffers
	aux = rigidBodies;
	rigidBodies = newRigidBodies;
	newRigidBodies = aux;
}