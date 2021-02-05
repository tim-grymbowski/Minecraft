#include "./Shader.h"

#include <unordered_map>
#include <iostream>
#define GLEW_STATIC
#include <gl/glew.h>

#define NULL 0


Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	RendererID = glCreateProgram();
	glAttachShader(RendererID, vertexShader);
	glAttachShader(RendererID, fragmentShader);
	glLinkProgram(RendererID);
}

Shader::~Shader()
{
}

void Shader::Bind()
{
	glUseProgram(RendererID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetMatrix(const char* matrix, const float* data)
{
	unsigned int location = glGetUniformLocation(RendererID, matrix);
	if (location == -1) 
	{ 
		std::cerr << "Error: Invalid uniform '" << matrix << "'" << std::endl;
		return; 
	}
	glProgramUniformMatrix4fv(RendererID, location, 1, GL_FALSE, data);
}

void Shader::SetSampler(const char* sampler, int slot)
{
	unsigned int location = glGetUniformLocation(RendererID, sampler);
	if (location == -1) 
	{ 
		std::cerr << "Error: Invalid uniform '" << sampler << "'" << std::endl;
		return; 
	}
	glProgramUniform1i(RendererID, location, slot);
}
