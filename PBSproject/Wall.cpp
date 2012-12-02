#include "Wall.h"
#include "Constants.h"

Wall::Wall(int type) {
	switch (type)
	{
	case kStandardWall:
		{buildStandardWall();
		break;}
	default:
		break;
	}
}

Wall::Wall(vector<float> &vert,float elasticity){
	xVel = 0.0f; yVel = 0.0f;
	mass = inf; friction = 0.0f; gravityScale = 0.0f;
	e = elasticity;
	momentOfInertia = inf;
	oneOverMass = 0.0f; oneOverI = 0.0f;

	nVertices = vert.size()/2;
	vertices = vert;

	color[0] = 0.8;
	color[1] = 0.0;
	color[2] = 0.1;
}

void Wall::buildStandardWall() {
	xVel = 0.0f; yVel = 0.0f;
	mass = inf; friction = 0.0f; gravityScale = 0.0f;
	e = 0.8f;
	momentOfInertia = inf;
	oneOverMass = 0.0f; oneOverI = 0.0f;

	vertices.push_back(1.0f);vertices.push_back(1.0f);
	vertices.push_back(-1.0f);vertices.push_back(1.0f);
	vertices.push_back(-1.0f);vertices.push_back(-1.0f);
	vertices.push_back(-0.1f);vertices.push_back(-1.0f);
	vertices.push_back(-0.1f);vertices.push_back(-0.8f);
	vertices.push_back(-0.8f);vertices.push_back(-0.8f);
	vertices.push_back(-0.8f);vertices.push_back(0.8f);
	vertices.push_back(0.8f);vertices.push_back(0.8f);
	vertices.push_back(0.8f);vertices.push_back(-0.8f);
	vertices.push_back(0.1f);vertices.push_back(-0.8f);
	vertices.push_back(0.1f);vertices.push_back(-1.0f);
	vertices.push_back(1.0f);vertices.push_back(-1.0f);
	//vertices.push_back(1.0f);vertices.push_back(1.0f);

	nVertices = vertices.size()/2;

	color[0] = 0.8;
	color[1] = 0.0;
	color[2] = 0.1;
}

void Wall::update(Shape *newSh) {

}

Wall * Wall::clone() {
	return new Wall(vertices,e);
}