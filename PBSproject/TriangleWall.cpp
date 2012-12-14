#include "TriangleWall.h"
#include "Constants.h"

TriangleWall::TriangleWall(float p1x, float p1y,
						float p2x, float p2y,
						float p3x, float p3y,
						float elasticity) {

							xPos = (p1x+p2x+p3x)/3.0f;
							yPos = (p1y+p2y+p3y)/3.0f;

							xVel = 0.0f; yVel = 0.0f; angularVel = 0.0f;
							mass = inf; friction = 0.0f; gravityScale = 0.0f;
							e = elasticity;
							momentOfInertia = inf;
							oneOverMass = 0.0f; oneOverI = 0.0f;

							nVertices = 3;
							vertices.push_back(p1x); vertices.push_back(p1y);
							vertices.push_back(p2x); vertices.push_back(p2y);
							vertices.push_back(p3x); vertices.push_back(p3y);

							color[0] = 0.8;
							color[1] = 0.0;
							color[2] = 0.1;

							float d1, d2, d3;
							d1 = (p1x-p2x)*(p1x-p2x)+(p1y-p2y)*(p1y-p2y);
							d2 = (p1x-p3x)*(p1x-p3x)+(p1y-p3y)*(p1y-p3y);
							d3 = (p3x-p2x)*(p3x-p2x)+(p3y-p2y)*(p3y-p2y);
							criticalRadius = sqrt(max(d1,max(d2,d3)));
}

TriangleWall* TriangleWall::clone() {
	return new TriangleWall(vertices.at(0),vertices.at(1), vertices.at(2), vertices.at(3),vertices.at(4), vertices.at(5), e);
}

bool TriangleWall::containsShape(Shape *sh, vector<int> &resp, vector<int >&resq) {
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