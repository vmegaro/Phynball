#include "Board.h"
#include <iostream>
#include "Constants.h"
#include "CharacterRB.h"
#include <windows.h>
#include <fstream>

/*
Intersection test between two polygons (not necessarily convex) 'sh1' and 'sh2'. First we check if the bounding circles 
collide or not, then if it is the case we perform a point-in-polygon test for every vertex of each polygon,
and finally we look for intersecting edges in the neighborhood of the collision point.
The vectors 'resp' and 'resq' store the indexes of the vertices engaged in the collision : the "piercing" vertex 
or the two vertices of a "pierced" edge. So if a collision occurs one of them will contain 1 vertex and the other 2.
'resp' corresponds to 'sh1' and resq to 'sh2'.
We tried to implement more shape-specific intersection tests with rigid bodies but could not make it in time.
*/
bool Board::polygonIntersectionTest(Shape *sh1, Shape *sh2, vector<int> &resp, vector<int >&resq){

	// Broad-phase: discard objects with no bounding areas averlap
	float dist2 = (sh1->xPos-sh2->xPos)*(sh1->xPos-sh2->xPos)+(sh1->yPos-sh2->yPos)*(sh1->yPos-sh2->yPos);
	float criticalDist2 = (sh1->criticalRadius+sh2->criticalRadius)*(sh1->criticalRadius+sh2->criticalRadius);
	if(dist2 > criticalDist2) return false;

	// Rigidbody collision detection speed up
	//int check = 0;
	//if(sh1->nature() == kShapeNatureRB) {
	//	check++;
	//	RigidBody *rb1 = (RigidBody *)sh1;
	//	// Try to detect collision smartly: use properties of the shape of the specific objects.
	//	if(rb1->containsShape(sh2, resp, resq)) return true;
	//}
	//if(sh2->nature() == kShapeNatureRB) {
	//	check++;
	//	RigidBody *rb2 = (RigidBody *)sh2;
	//	if(rb2->containsShape(sh1, resq, resp)) return true;
	//}
	//if(check == 2) return false;

	// We are not lucky: perform a complete non convex polygon intersection test
	vector<float> p,q;
	p = sh1->vertices;
	q = sh2->vertices;
	int m=p.size()/2;
	int n=q.size()/2;
	int i,j,k,l;
	float x,y,det1,det2;
	bool odd = false;
	// loop over 'sh1' vertices
	for(i=0;i<m;i++){
		x=p[2*i];
		y=p[2*i+1];
		k=n-1;
		// loop over 'sh2' edges
		for(j=0;j<n;j++){
			// point-in-polygon test
			if ((((q[2*j+1]<y)&&(q[2*k+1]>=y))||((q[2*k+1]<y)&&(q[2*j+1]>=y)))&&((q[2*j]<=x)||(q[2*k]<=x))) {
			      if (q[2*j]+(y-q[2*j+1])/(q[2*k+1]-q[2*j+1])*(q[2*k]-q[2*j])<x) odd=!odd;
			}
			k=j;
		}
		// collision found
		if(odd){
			resp.push_back(i);
			l=(i+1)%m;
			k=n-1;
			//we look for intersecting edges with the two edges adjacent to the collision point
			// with the first edge
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
			//with the second edge
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
	// same thing but this time we loop over 'sh2' vertices
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

	RungeKuttaODESolver *solver = new RungeKuttaODESolver(timeStep);
	goalCharacters.push_back(new CharacterRB('g',solver));
	goalCharacters.push_back(new CharacterRB('o',solver));
	goalCharacters.push_back(new CharacterRB('a',solver));
	goalCharacters.push_back(new CharacterRB('l',solver));
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
// the following method checks if the condition of a goal are met and prevents one goal from turning into several ones
// because of the too small time step.
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
bool collisionFound = false;
float positionNoise;
vector<int> resp, resq;
// move the ball back after a goal. It tries to put the ball back in its original position and if it's not
// possible because a collsion would occur it adds some noise to the position and tries again.
void Board::restoreBallPosition() {
	//cout << "rest0" << nl;
	playBall->xPos = 70.0f;
	playBall->yPos = 60.0f;
	playBall->xVel = 0.0f;
	playBall->yVel = 0.0f;
	playBall->angularPos = 0.0f;
	playBall->angularVel = 0.0f;
	vector<Shape *>::iterator it1;
	while(true) {
		collisionFound = false;
		positionNoise = (float)rand()*5.0f/(float)RAND_MAX -2.5f;
		playBall->xPos += positionNoise;
		positionNoise = (float)rand()*5.0f/(float)RAND_MAX -2.5f;
		playBall->yPos += positionNoise;
		it1 = shapes->begin();
		for(;it1 != shapes->end();++it1){
			if(playBall == *it1) continue;
			if(polygonIntersectionTest(*it1,playBall,resp,resq)) {
				collisionFound = true;
				break;
			}
		}
		if(!collisionFound) break;
	}
	//cout << "rest1" << nl;
}

void Board::moveLeftPale(bool b){
	if(b)
		leftPale->setGoUp();
	else
		leftPale->setGoDown();
}

void Board::moveRightPale(bool b){
	if(b)
		rightPale->setGoUp();
	else
		rightPale->setGoDown();
}

int collisionInd;
int animationFrames = 0;
bool shouldDisplyAnimation = false;
// start the animation after each goal
void Board::startGoalAnimation() {
	// make the four letters 'g', 'o', 'a' and 'l' move and collide like normal dynamic shapes
	for(int i = 0; i < intermediateSteps; i++) {
		vector<Shape *>::iterator it1 = goalCharacters.begin();
		for(;it1 != goalCharacters.end();++it1){
			(*it1)->update(*it1); // timestep integration
		}

		vector<Shape *>::iterator sit1, sit2, nsit1, nsit2;
		for(sit1 = goalCharacters.begin() ,nsit1 = goalCharacters.begin(), collisionInd = 0;nsit1 != goalCharacters.end();++sit1, ++nsit1, collisionInd++) {
			for(sit2 = sit1+1, nsit2 = nsit1+1; nsit2 != goalCharacters.end();++sit2, ++nsit2) {
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

		//if(otherTeamScore == 2) cout << "solve collisions" << nl;
		// Update using impulses
		vector<Collision *>::iterator colIt = collisions.begin();
		for(;colIt != collisions.end();++colIt) {
			(*colIt)->resolve();
		}
	}
	
}
//function used to exert gravity on the four letters, to make them fall after they collide
void Board::setGravityToGoalChars(float gravity) {
	CharacterRB *ch;
	ch = (CharacterRB *)goalCharacters.at(0);
	ch->gravityScale = gravity;
	ch = (CharacterRB *)goalCharacters.at(1);
	ch->gravityScale = gravity;
	ch = (CharacterRB *)goalCharacters.at(2);
	ch->gravityScale = gravity;
	ch = (CharacterRB *)goalCharacters.at(3);
	ch->gravityScale = gravity;
}

// reinitialize the position of the four letters after the animation
void Board::reinitCharPositions() {
	setGravityToGoalChars(0.0f);
	CharacterRB *ch;
	for(int i = 0; i < 4; i++) {
		ch = (CharacterRB *)goalCharacters.at(i);
		ch->reinit();
	}
}

float cdvx, cdvy, cdva, cimp;
// main method to update the state of every shape after every time step
void Board::update() {
	//cout << "Updating" << nl;
	if(shouldDisplyAnimation) {
		animationFrames ++;
		if(animationFrames >= 20) {
			startGoalAnimation();
			animationFrames ++;
			if(animationFrames == 150) {
				setGravityToGoalChars(3.0f);
			}
			if(animationFrames > 350) {
				shouldDisplyAnimation = false;
				animationFrames = 0;
				reinitCharPositions();
				restoreBallPosition();
			}
			return;
		}
	}

	// Iteration
	for(int t = 0; t < intermediateSteps; t++) {
		//if(otherTeamScore == 2) cout << "update shapes" << nl;
		// Update position and velocities
		vector<Shape *>::iterator it1 = shapes->begin(),
									  it2 = newShapes->begin();
		for(;it1 != shapes->end();++it1,++it2){
			(*it1)->update(*it2); // timestep integration
		}

		//if(otherTeamScore == 2) cout << "update pales" << nl;
		leftPale->update(leftPale);
		rightPale->update(rightPale);

		collisions.clear();

		// Collisions
		//+++++++++++

		vector<Shape *>::iterator sit1, sit2, nsit1, nsit2;
		vector<Wall *>::iterator wIt;
		
		//if(otherTeamScore == 2) cout << "pales collisions" << nl;
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

		//if(otherTeamScore == 2) cout << "walls collision" << nl;
		//Wall collisions
		int w = 0;
		for(wIt = walls->begin(); wIt != walls->end();++wIt,w++) {
			int s = 0;
			for(nsit1 = newShapes->begin(); nsit1 != newShapes->end();++nsit1,s++) {
				//if(otherTeamScore == 2) cout << w << " <-> " << s << nl;
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
		//if(otherTeamScore == 2) cout << "shapes collision" << nl;
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

		//if(otherTeamScore == 2) cout << "solve collisions" << nl;
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
	/*
	if(GetAsyncKeyState(VkKeyScan('x')) <= keyPress) leftPale->setGoUp();
	else leftPale->setGoDown();
	if(GetAsyncKeyState(VkKeyScan('n')) <= keyPress) rightPale->setGoUp();
	else rightPale->setGoDown();
	*/

	//Check and set if someone scored
	//if(otherTeamScore == 2) cout << "setscore0" << nl;
	setScore();
	//if(otherTeamScore == 2) cout << "setscore1" << nl;
	if(isPlayerGoal) {
		playerScore++;
		shouldDisplyAnimation = true;
	}
	if(isOtherTeamGoal) {
		otherTeamScore++;
		shouldDisplyAnimation = true;
	}
	//if(otherTeamScore == 2) cout << "end" << nl;
}
