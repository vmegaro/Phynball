#include "Board.h"
#include <iostream>
#include "Constants.h"
#include <windows.h>
#include <fstream>

bool Board::polygonIntersectionTest(Shape *sh1, Shape *sh2, vector<int> &resp, vector<int >&resq){

	// Broad-phase: discard objects with no bounding areas averlap
	float dist2 = (sh1->xPos-sh2->xPos)*(sh1->xPos-sh2->xPos)+(sh1->yPos-sh2->yPos)*(sh1->yPos-sh2->yPos);
	float criticalDist2 = (sh1->criticalRadius+sh2->criticalRadius)*(sh1->criticalRadius+sh2->criticalRadius);
	if(dist2 > criticalDist2) return false;

	// Rigidbody collision detection speed up
	int check = 0;
	if(sh1->nature() == kShapeNatureRB) {
		check++;
		RigidBody *rb1 = (RigidBody *)sh1;
		// Try to detect collision smartly: use properties of the shape of the specific objects.
		if(rb1->containsShape(sh2, resp, resq)) return true;
	}
	if(sh2->nature() == kShapeNatureRB) {
		check++;
		RigidBody *rb2 = (RigidBody *)sh2;
		if(rb2->containsShape(sh1, resq, resp)) return true;
	}
	if(check == 2) return false;

	// We are not lucky: perform a complete non convex polygon intersection test
	vector<float> p,q;
	p = sh1->vertices;
	q = sh2->vertices;
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
	walls = &wallsVec;
	playerScore = 0;
	otherTeamScore = 0;
}

Board::~Board(){
}

void Board::addShape(Shape *s) {
	shapeVec1.push_back(s);
	shapeVec2.push_back(s->clone());
}

void Board::addWall(Shape *w) {
	/*shapeVec1.push_back(w);
	shapeVec2.push_back(w);*/
	Wall *wall = (Wall *)w;
	wallsVec.push_back(wall);
}

void Board::addLeftPale(Shape *p) {
	Pale *lp = (Pale *)p;
	leftPale = lp;
}

void Board::addRightPale(Shape *p) {
	Pale *rp = (Pale *)p;
	rightPale = rp;
}

void Board::addPlayBall(Shape *_playBall) {
	shapeVec1.push_back(_playBall);
	shapeVec2.push_back(_playBall->clone());
	this->playBall = (PlayBall *)_playBall;
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

bool wasGoal = false;
bool isOtherTeamGoal = false, isPlayerGoal = false;
void Board::setScore() {
	isOtherTeamGoal = false; isPlayerGoal = false;
	if(playBall->yPos >= 80.0 && 
		playBall->xPos >= leftGoalPole && playBall->xPos <= rightGoalPole) {
			if(!wasGoal){
				isPlayerGoal = true;
				wasGoal = true;
			}
	}else if(playBall->yPos < 0) {
		if(!wasGoal){
			isOtherTeamGoal = true;
			wasGoal = true;
		}
	}else {
		wasGoal = false;
	}
}

float positionNoise;
vector<int> resp, resq;
void Board::restoreBallPosition() {
	playBall->xPos = 70.0f;
	playBall->yPos = 60.0f;
	playBall->xVel = 0.0f;
	playBall->yVel = 3.0f;
	playBall->angularPos = 0.0f;
	playBall->angularVel = 0.0f;
	vector<Shape *>::iterator it1;
	while(true) {
		positionNoise = (float)rand()*5.0f/(float)RAND_MAX -2.5f;
		playBall->xPos += positionNoise;
		positionNoise = (float)rand()*5.0f/(float)RAND_MAX -2.5f;
		playBall->yPos += positionNoise;
		it1 = shapes->begin();
		for(;it1 != shapes->end();++it1){
			if(polygonIntersectionTest(*it1,playBall,resp,resq)) continue;
		}
		break;
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


		leftPale->update(leftPale);
		rightPale->update(rightPale);

		collisions.clear();

		// Collisions
		//+++++++++++

		vector<Shape *>::iterator sit1, sit2, nsit1, nsit2;
		vector<Wall *>::iterator wIt;

		//Pales collisions
		for(nsit1 = newShapes->begin(); nsit1 != newShapes->end();++nsit1) {
			if(polygonIntersectionTest(*nsit1,leftPale,resp,resq)) {
				Collision *collision = new Collision();
				if(resp.size() == 2) {
					(*nsit1)->setCollisionResponse(
												leftPale,
												resq.at(0),
												resp.at(0),
												collision);
				}else {
					(leftPale)->setCollisionResponse(
												*nsit1,
												resp.at(0),
												resq.at(0),
												collision);
				}
				collisions.push_back(collision);
				resp.clear();resq.clear();
			}

			if(polygonIntersectionTest(*nsit1,rightPale,resp,resq)) {
				Collision *collision = new Collision();
				if(resp.size() == 2) {
					(*nsit1)->setCollisionResponse(
												rightPale,
												resq.at(0),
												resp.at(0),
												collision);
				}else {
					(rightPale)->setCollisionResponse(
												*nsit1,
												resp.at(0),
												resq.at(0),
												collision);
				}
				collisions.push_back(collision);
				resp.clear();resq.clear();
			}
		}

		//Wall collisions
		for(wIt = walls->begin(); wIt != walls->end();++wIt) {
			for(nsit1 = newShapes->begin(); nsit1 != newShapes->end();++nsit1) {
				if(polygonIntersectionTest(*nsit1,*wIt,resp,resq)) {
					Collision *collision = new Collision();
					if(resp.size() == 2) {
						(*nsit1)->setCollisionResponse(
													*wIt,
													resq.at(0),
													resp.at(0),
													collision);
					}else {
						(*wIt)->setCollisionResponse(
													*nsit1,
													resp.at(0),
													resq.at(0),
													collision);
					}
					collisions.push_back(collision);
					resp.clear();resq.clear();
				}
			}
		}

		// Dynamic objects collisions
		for(sit1 = shapes->begin() ,nsit1 = newShapes->begin(), collisionInd = 0;nsit1 != newShapes->end();++sit1, ++nsit1, collisionInd++) {
			for(sit2 = sit1+1, nsit2 = nsit1+1; nsit2 != newShapes->end();++sit2, ++nsit2) {
				if(polygonIntersectionTest(*nsit1,*nsit2,resp,resq)) {
					Collision *collision = new Collision();
					if(resp.size() == 2) {
						(*nsit1)->setCollisionResponse(
													*nsit2,
													resq.at(0),
													resp.at(0),
													collision);
					}else {
						(*nsit2)->setCollisionResponse(
													*nsit1,
													resp.at(0),
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

	//Check and set if someone scored
	setScore();
	if(isPlayerGoal) {
		playerScore++;
		restoreBallPosition();
	}
	if(isOtherTeamGoal) {
		otherTeamScore++;
		restoreBallPosition();
	}
}