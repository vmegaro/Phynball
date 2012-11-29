#include "Board.h"

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

void Board::addWalls(Walls *w) {
	walls = w;
}

void Board::update() {
	// Update position and velocities
	vector<Shape *>::iterator it1 = shapes->begin(),
								  it2 = newShapes->begin();
	for(;it1 != shapes->end();++it1,++it2){
		(*it1)->update(*it2);
	}

	// Find walls collisions
	float vx,vy;
	it2 = newShapes->begin();
	for(;it2 != newShapes->end();++it2){
		for(int vInd = 0; vInd < (*it2)->nVertices; vInd++) {
			vx = (*it2)->vertices.at(vInd*2);
			vy = (*it2)->vertices.at(vInd*+1);
			// Check left and right walls
			if(vx <= walls->x1Pos) {
				//(*it2)->xVel = abs((*it2)->xVel);
			}else if(vx >= walls->x2Pos) {
				//(*it2)->xVel = -abs((*it2)->xVel);
			}

			// Check lower and upper walls
			if(vy <= walls->y1Pos) {
				//(*it2)->yVel = abs((*it2)->yVel);
			}else if(vy >= walls->y2Pos) {
				//(*it2)->yVel = -abs((*it2)->yVel);
			}
		}
	}

	// Apply potential forces
	/*float c1x,c1y,c2x,c2y;
	float r2;
	it1 = newShapes->begin();
	for(;it1 != newShapes->end();++it1){
		c1x = (*it1)->xPos;
		c1y = (*it1)->yPos;
		for(it2 = it1+1;it2 != newShapes->end();++it2){
			c2x = (*it2)->xPos;
			c2y = (*it2)->xPos;

			(*it1)->Rx = c2x-c1x;
			(*it1)->Ry = c2y-c1y;
			r2 = (*it1)->Rx*(*it1)->Rx+(*it1)->Ry*(*it1)->Ry;
			(*it1)->Tx = 4.0f*(*it1)->Rx/r2;
			(*it1)->Ty = 4.0f*(*it1)->Ry/r2;
		}
	}*/

	// Swap buffers
	aux = shapes;
	shapes = newShapes;
	newShapes = aux;
}