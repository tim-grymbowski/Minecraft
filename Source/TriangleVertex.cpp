#include "./TriangleVertex.h"


TriangleVertex::TriangleVertex() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
}

TriangleVertex::TriangleVertex(float x, float y, float z, float r, float g, float b) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->r = r;
	this->g = g;
	this->b = b;
}
