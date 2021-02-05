#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#define COLOR GL_COLOR_BUFFER_BIT 
#define DEPTH GL_DEPTH_BUFFER_BIT 

#include "./Shader.h"
#include "./Mesh.h"
#include "./Texture.h"


class Renderer
{
private:
public:
	static void Init();
	static void Submit(Shader& shader, Mesh& mesh);
	static void Submit(Shader& shader, Mesh& mesh, Texture& texture);
	static void SetClearColor(float r, float g, float b, float a);
	static void Clear(unsigned int flags);
};
