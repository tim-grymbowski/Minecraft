#pragma once

#include <unordered_map>

class Shader
{
private:
	unsigned int RendererID;
	std::unordered_map<std::string, unsigned int> uniforms;
public:
	Shader(const char* vertexSource, const char* fragmentSource);
	~Shader();

	void Bind();
	void Unbind();

	void SetMatrix(const char* matrix, const float* data);
	void SetSampler(const char* sampler, int slot);

	inline unsigned int GetID() { return RendererID; }
};
