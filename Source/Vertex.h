#pragma once

struct Vertex
{
	float x;
	float y;
	float z;

	float u;
	float v;

	float t;

	Vertex();
	Vertex(float x, float y, float z, float u, float v, float t);
};
