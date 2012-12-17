#include "Pale.h"
#include "Constants.h"

#define xPosL 32.0f
#define xPosR 67.5f
#define yPosLR 12.5f
#define minAngL -M_PI/4.0f
#define maxAngL M_PI/8.0f
#define minAngR M_PI/8.0f*7.0f
#define maxAngR M_PI/4.0f*5.0f
#define standardAngVel 6.0f
#define longWidth 15.0f
#define shortWidth 2.0f
#define height 3.0f

enum PaleVerticesPositions
{
	innerx = 0,
	innery,
	outterUpx,
	outterUpy,
	outterBottomx,
	outterBottomy,
	NUM_Vertices
};

Pale::Pale(int position, RungeKuttaODESolver *odeSolver) {
	vertices = vector<float>(NUM_Vertices,0.0f);
	switch (position)
	{
	case kLeftPale:
		{
			xPos = xPosL;
			angularPos = minAngL;
			maxAngle = maxAngL;
			minAngle = minAngL;
			upAngularVel = standardAngVel;
			break;
		}
	case kRightPale:
		{
			xPos = xPosR;
			angularPos = maxAngR;
			maxAngle = maxAngR;
			minAngle = minAngR;
			upAngularVel = -standardAngVel;
			break;
		}
	default:
		break;
	}

	yPos = yPosLR;

	vertices.at(innerx) = (xPos+longWidth);vertices.at(innery) = (yPos);
	vertices.at(outterUpx) = (xPos-shortWidth);vertices.at(outterUpy) = (yPos+height);
	vertices.at(outterBottomx) = (xPos-shortWidth);vertices.at(outterBottomy) = (yPos-height);

	nVertices = NUM_Vertices/2;

	xVel = 0.0f; yVel = 0.0f;
	angularVel = 0.0f;

	updateVertices();

	mass = inf; friction = 0.0f; gravityScale = 0.0f;
	e = 0.4f;
	momentOfInertia = mass*(longWidth*longWidth+height*height)/20.0f;
	oneOverMass = 0.0f; oneOverI = 1.0f/momentOfInertia;
	Tx = 0.0f; Ty = 0.0f; Rx = 0.0f; Ry = 0.0f;
	solver = odeSolver;

	color[0] = 0.5;
	color[1] = 0.5;
	color[2] = 0.5;

	criticalRadius = longWidth;
}

Pale * Pale::clone() {
	if(upAngularVel == standardAngVel) {
		return new Pale(kLeftPale, solver);
	}else {
		return new Pale(kRightPale, solver);
	}
}

void Pale::update(Shape *newSh) {
	if(angularPos < minAngle) {
		angularPos = minAngle;
		angularVel = 0.0f;
	}else if(angularPos > maxAngle) {
		angularPos = maxAngle;
		angularVel = 0.0f;
	}else {
		solver->updateRigidBodyPositionAngleAndVelocities(this, this);
		updateVertices();
	}
}

void Pale::setGoUp() {
	angularVel = upAngularVel;
	update(this);
}

void Pale::setGoDown() {
	angularVel = -upAngularVel;
	update(this);
}

void Pale::updateVertices() {
	longVecX = cos(angularPos)*longWidth; // deltaX
	longVecY = sin(angularPos)*longWidth; // deltaY
	shortVecX = -cos(angularPos)*shortWidth;
	shortVecY = -sin(angularPos)*shortWidth;

	relength = height/sqrt(shortVecX*shortVecX+shortVecY*shortVecY);

	heightVecX = -shortVecY*relength;
	heightVecY = shortVecX*relength;

	vertices.at(innerx) = xPos + longVecX;
	vertices.at(innery) = yPos + longVecY;
	vertices.at(outterUpx) = xPos + shortVecX + heightVecX;
	vertices.at(outterUpy) = yPos + shortVecY + heightVecY;
	vertices.at(outterBottomx) = xPos + shortVecX - heightVecX;
	vertices.at(outterBottomy) = yPos + shortVecY - heightVecY;
}

bool Pale::containsShape(Shape *sh, vector<int> &resp, vector<int >&resq) {

	for(int i = 0; i < sh->nVertices; i++) {
		float Ax = sh->vertices.at(2*i);
		float Ay = sh->vertices.at(2*i+1);

		// Compute vectors        
		float v0x = vertices.at(2) - vertices.at(0);
		float v1x = vertices.at(4) - vertices.at(0);
		float v2x = Ax - vertices.at(0);

		float v0y = vertices.at(3) - vertices.at(1);
		float v1y = vertices.at(5) - vertices.at(1);
		float v2y = Ay - vertices.at(1);

		// Compute dot products
		float dot00 = v0x*v0x+v0y*v0y;
		float dot01 = v0x*v1x+v0y*v1y;
		float dot02 = v0x*v2x+v0y*v2y;
		float dot11 = v1x*v1x+v1y*v1y;
		float dot12 = v1x*v2x+v1y*v2y;

		// Compute barycentric coordinates
		float invDenom = 1/(dot00 * dot11 - dot01 * dot01);
		float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
		float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

		// Check if point is in triangle
		if((u >= 0) && (v >= 0) && (u + v < 1)) {
			// Point index inside triangle
			resq.push_back(i);

			// Anchor edge 
			for(int k = 0; k < sh->nVertices && resp.empty(); k++) {
				float Ax = sh->vertices.at((2*(i+k))%(2*sh->nVertices));
				float Ay = sh->vertices.at((2*(i+k)+1)%(2*sh->nVertices));
				float Bx = sh->vertices.at((2*(i+k+1))%(2*sh->nVertices));
				float By = sh->vertices.at((2*(i+k+1)+1)%(2*sh->nVertices));

				// Edge detection for normal computation
				for(int j = 0; j < nVertices; j++) {
					float Cx = vertices.at(2*j);
					float Cy = vertices.at(2*j+1);
					float Dx = vertices.at((2*j+2)%(nVertices*2));
					float Dy = vertices.at((2*j+3)%(nVertices*2));

					float x00 = Ax, y00 = Ay,
						  x01 = Bx-Ax, y01 = By-Ay,
						  x10 = Cx, y10 = Cy,
						  x11 = Dx-Cx, y11 = Dy-Cy;

					float d = (x11*y01 - x01*y11);
					if (d == 0) continue;
					float oneOverd = 1.0f/d;

					float s = oneOverd*((x00-x10)*y01 - (y00-y10)*x01);
					float t = -oneOverd*(-(x00-x10)*y11 + (y00-y10)*x11);

					if(t >= 0.0f && t <= 1.0f &&
						s >= 0.0f && s <= 1.0f) {
						resp.push_back(j);resp.push_back(j+1);
						break;
					}
				}
			}

			return resp.size();
		}
		
	}

	return false;
}