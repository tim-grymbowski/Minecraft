#pragma once

#include "./Vertex.h"
#include "./TriangleVertex.h"

#include <vector>


class Mesh
{
private:
	unsigned int RendererID;
	unsigned int VertexBufferID;
	unsigned int IndexBufferID;
	int VertexBufferLength;
	int IndexBufferLength;
public:
	Mesh(int length);
	Mesh(const std::vector<Vertex>& buffer);
	Mesh(const std::vector<TriangleVertex>& buffer);
	~Mesh();

	void Data(const std::vector<Vertex>& buffer);
	void Data(const std::vector<TriangleVertex>& buffer);
	void AddAttribute(int index, int components, size_t offset);

	inline unsigned int GetRendererID() { return RendererID; };
	inline int GetVerticesLength() { return VertexBufferLength; };
	inline int GetIndicesLength() { return IndexBufferLength; };
};
