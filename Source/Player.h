#pragma once

#include "./Camera.h"

#include "./vendor/glm/glm.hpp"
#include "./vendor/glm/gtc/matrix_transform.hpp"
#include "./vendor/glm/gtc/type_ptr.hpp"


class Player
{
private:
	glm::mat4 matrix;
public:
	Player() { matrix = glm::identity<glm::mat4>(); }
	Player(float x, float y, float z) { 
		glm::mat4 identity = glm::identity<glm::mat4>();
		matrix = glm::translate(identity, glm::vec3(x, y, z));
	}
	
	~Player() {}
	
	inline void Update(const glm::mat4& matrix) { this->matrix *= matrix; } 
	inline glm::mat4 GetMatrix() { return glm::inverse(matrix); }
	inline glm::vec4 GetPosition() { return matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); }
};
