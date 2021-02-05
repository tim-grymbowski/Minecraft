#include "./Vertex.h"


Vertex::Vertex()
{
	this->x = +0.0f;
	this->y = +0.0f;
	this->z = +0.0f;
	this->u = +0.0f;
	this->v = +0.0f;
	this->t = -1.0f;
}

Vertex::Vertex(float x, float y, float z, float u, float v, float t)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->u = u;
	this->v = v;
	this->t = t;
}
