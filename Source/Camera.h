#pragma once


#include "./vendor/glm/glm.hpp"
#include "./vendor/glm/gtc/matrix_transform.hpp"
#include "./vendor/glm/gtc/type_ptr.hpp"

class Camera
{
private:
	glm::mat4 matrix;
public:
	Camera() { matrix = glm::identity<glm::mat4>(); }
	~Camera() {}
	inline void Update(const glm::mat4& matrix) { this->matrix *= matrix; }
	inline glm::mat4 GetMatrix() { return matrix; }
};
