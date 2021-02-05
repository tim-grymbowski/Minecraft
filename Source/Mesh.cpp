#include "./Mesh.h"
#include "./Vertex.h"
#include "./TriangleVertex.h"

#include <vector>
#include <cstdint>
#define GLEW_STATIC
#include <GL/glew.h>


Mesh::Mesh(int length) {
	VertexBufferLength = length;
	IndexBufferLength = (VertexBufferLength * 3) >> 1;
	RendererID = 0;  
	glGenVertexArrays(1, &RendererID);
	VertexBufferID = 0; 
	glGenBuffers(1, &VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, VertexBufferLength * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	IndexBufferID = 0; 
	glGenBuffers(1, &IndexBufferID);
	glBindVertexArray(RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(const std::vector<Vertex>& buffer) {
	VertexBufferLength = buffer.size();
	IndexBufferLength = (VertexBufferLength * 3) >> 1;
	RendererID = 0;  
	glGenVertexArrays(1, &RendererID);
	VertexBufferID = 0; 
	glGenBuffers(1, &VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, VertexBufferLength * sizeof(Vertex), &buffer[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	IndexBufferID = 0; 
	glGenBuffers(1, &IndexBufferID);
	glBindVertexArray(RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);

	std::vector<uint32_t> indices = { };
	indices.reserve(IndexBufferLength);
	int iterations = IndexBufferLength / 6;
	for (int i = 0; i < iterations; ++i) {
		int offset = (i << 2);
		indices.push_back(offset);
		indices.push_back(3 + offset);
		indices.push_back(2 + offset);
		indices.push_back(offset);
		indices.push_back(2 + offset);
		indices.push_back(1 + offset);
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBufferLength * sizeof(uint32_t), &indices[0], GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(const std::vector<TriangleVertex>& buffer) {
	VertexBufferLength = buffer.size();
	IndexBufferLength = (VertexBufferLength * 3) >> 1;
	RendererID = 0;  
	glGenVertexArrays(1, &RendererID);
	VertexBufferID = 0; 
	glGenBuffers(1, &VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, VertexBufferLength * sizeof(TriangleVertex), &buffer[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	IndexBufferID = 0; 
	glGenBuffers(1, &IndexBufferID);
	glBindVertexArray(RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);

	std::vector<uint32_t> indices = { };
	indices.reserve(IndexBufferLength);
	int iterations = IndexBufferLength / 6;
	for (int i = 0; i < iterations; ++i) {
		int offset = (i << 2);
		indices.push_back(offset);
		indices.push_back(3 + offset);
		indices.push_back(2 + offset);
		indices.push_back(offset);
		indices.push_back(2 + offset);
		indices.push_back(1 + offset);
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBufferLength * sizeof(uint32_t), &indices[0], GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {

}

void Mesh::Data(const std::vector<Vertex>& buffer) {
	VertexBufferLength = buffer.size();
	IndexBufferLength = (VertexBufferLength * 3) >> 1;
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, VertexBufferLength * sizeof(Vertex), &buffer[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);

	std::vector<uint32_t> indices = { };
	indices.reserve(IndexBufferLength);
	int iterations = IndexBufferLength / 6;
	for (int i = 0; i < iterations; ++i) {
		int offset = (i << 2);
		indices.push_back(offset);
		indices.push_back(3 + offset);
		indices.push_back(2 + offset);
		indices.push_back(offset);
		indices.push_back(2 + offset);
		indices.push_back(1 + offset);
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBufferLength * sizeof(uint32_t), &indices[0], GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Data(const std::vector<TriangleVertex>& buffer) {
	VertexBufferLength = buffer.size();
	IndexBufferLength = (VertexBufferLength * 3) >> 1;
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, VertexBufferLength * sizeof(TriangleVertex), &buffer[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);

	std::vector<uint32_t> indices = { };
	indices.reserve(IndexBufferLength);
	int iterations = IndexBufferLength / 6;
	for (int i = 0; i < iterations; ++i) {
		int offset = (i << 2);
		indices.push_back(offset);
		indices.push_back(3 + offset);
		indices.push_back(2 + offset);
		indices.push_back(offset);
		indices.push_back(2 + offset);
		indices.push_back(1 + offset);
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexBufferLength * sizeof(uint32_t), &indices[0], GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::AddAttribute(int index, int components, size_t offset) {
	glBindVertexArray(RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, components, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offset);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
