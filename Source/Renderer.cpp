#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include "./Renderer.h"
#include "./Shader.h"
#include "./Mesh.h"
#include "./Texture.h"


void Renderer::Init()
{
	if (glewInit() != GLEW_OK)
		std::cerr << "Error: Invalid rendering context" << std::endl;

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_ADD);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::Submit(Shader& shader, Mesh& mesh)
{
	shader.Bind();
	glBindVertexArray(mesh.GetRendererID());
	glDrawElements(GL_TRIANGLES, mesh.GetIndicesLength(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	shader.Unbind();
}

void Renderer::Submit(Shader& shader, Mesh& mesh, Texture& texture)
{
	texture.Bind(texture.GetSlot());
	shader.Bind();
	glBindVertexArray(mesh.GetRendererID());
	glDrawElements(GL_TRIANGLES, mesh.GetIndicesLength(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	shader.Unbind();
	texture.Unbind();
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::Clear(unsigned int flags)
{
	glClear(flags);
}
