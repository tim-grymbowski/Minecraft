#include <iostream>
#include <thread>
#include <string>
#include <fstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./vendor/stb_image/stb_image.h"

#include "./vendor/glm/glm.hpp"
#include "./vendor/glm/gtc/matrix_transform.hpp"


struct Vertex
{
	float x;
	float y;
	float z;

	float u;
	float v;

	float t;

	Vertex(float x, float y, float z, float u, float v, float t);
};

Vertex::Vertex(float x, float y, float z, float u, float v, float t)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->u = u;
	this->v = v;
	this->t = t;
}

Vertex mesh[] = {

	/* FRONT FACE */ 

	Vertex(-0.5f, -0.5f, -1.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -1.0f, +0.25f, +0.75f, +1.0f),
	Vertex(+0.5f, +0.5f, -1.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-0.5f, -0.5f, -1.0f, +0.25f, +0.25f, +1.0f),
	Vertex(+0.5f, +0.5f, -1.0f, +0.75f, +0.75f, +1.0f),
	Vertex(+0.5f, -0.5f, -1.0f, +0.75f, +0.25f, +1.0f),

	/* LEFT SIDE FACE */

	Vertex(-0.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -1.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-0.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -1.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, -0.5f, -1.0f, +0.75f, +0.25f, +1.0f),

	/* RIGHT SIDE FACE */

	Vertex(+0.5f, -0.5f, -1.0f, +0.25f, +0.25f, +1.0f),
	Vertex(+0.5f, +0.5f, -1.0f, +0.25f, +0.75f, +1.0f),
	Vertex(+0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),

	Vertex(+0.5f, -0.5f, -1.0f, +0.25f, +0.25f, +1.0f),
	Vertex(+0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),
	Vertex(+0.5f, -0.5f, -2.0f, +0.75f, +0.25f, +1.0f),

	/* TOP FACE */

	Vertex(-0.5f, +0.5f, -1.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.25f, +0.75f, +1.0f),
	Vertex(+0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-0.5f, +0.5f, -1.0f, +0.25f, +0.25f, +1.0f),
	Vertex(+0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),
	Vertex(+0.5f, +0.5f, -1.0f, +0.75f, +0.25f, +1.0f),

	/* BOTTOM FACE */

	Vertex(-0.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, -0.5f, -1.0f, +0.25f, +0.75f, +1.0f),
	Vertex(+0.5f, -0.5f, -1.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-0.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(+0.5f, -0.5f, -1.0f, +0.75f, +0.75f, +1.0f),
	Vertex(+0.5f, -0.5f, -2.0f, +0.75f, +0.25f, +1.0f),

	/* BACK FACE */
	
	Vertex(+0.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(+0.5f, +0.5f, -2.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),

	Vertex(+0.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, -0.5f, -2.0f, +0.75f, +0.25f, +1.0f),

	//-------------------------------------------------

	/* FRONT FACE */

	Vertex(-1.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +0.5f, -2.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-1.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, -0.5f, -2.0f, +0.75f, +0.25f, +1.0f),

	/* LEFT SIDE FACE */

	Vertex(-1.5f, -0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +0.5f, -3.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-1.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-1.5f, -0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-1.5f, -0.5f, -2.0f, +0.75f, +0.25f, +1.0f),

	/* RIGHT SIDE FACE */

	Vertex(-0.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -3.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-0.5f, -0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -3.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, -0.5f, -3.0f, +0.75f, +0.25f, +1.0f),

	/* TOP FACE */

	Vertex(-1.5f, +0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +0.5f, -3.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -3.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-1.5f, +0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -3.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.75f, +0.25f, +1.0f),

	/* BOTTOM FACE */

	Vertex(-1.5f, -0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, -0.5f, -2.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, -0.5f, -2.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-1.5f, -0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, -0.5f, -2.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, -0.5f, -3.0f, +0.75f, +0.25f, +1.0f),

	/* BACK FACE */

	Vertex(-0.5f, -0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -3.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-1.5f, +0.5f, -3.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-0.5f, -0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +0.5f, -3.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-1.5f, -0.5f, -3.0f, +0.75f, +0.25f, +1.0f),

	//-------------------------------------------------

	/* FRONT FACE */

	Vertex(-1.5f, +0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +1.5f, -2.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, +1.5f, -2.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-1.5f, +0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +1.5f, -2.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.75f, +0.25f, +1.0f),

	/* LEFT SIDE FACE */

	Vertex(-1.5f, +0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +1.5f, -3.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-1.5f, +1.5f, -2.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-1.5f, +0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +1.5f, -2.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-1.5f, +0.5f, -2.0f, +0.75f, +0.25f, +1.0f),

	/* RIGHT SIDE FACE */

	Vertex(-0.5f, +0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +1.5f, -2.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, +1.5f, -3.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-0.5f, +0.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +1.5f, -3.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -3.0f, +0.75f, +0.25f, +1.0f),

	/* TOP FACE */

	Vertex(-1.5f, +1.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +1.5f, -3.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, +1.5f, -3.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-1.5f, +1.5f, -2.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +1.5f, -3.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, +1.5f, -2.0f, +0.75f, +0.25f, +1.0f),

	/* BOTTOM FACE */

	Vertex(-1.5f, +0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +0.5f, -2.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-1.5f, +0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +0.5f, -2.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-0.5f, +0.5f, -3.0f, +0.75f, +0.25f, +1.0f),

	/* BACK FACE */

	Vertex(-0.5f, +0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-0.5f, +1.5f, -3.0f, +0.25f, +0.75f, +1.0f),
	Vertex(-1.5f, +1.5f, -3.0f, +0.75f, +0.75f, +1.0f),

	Vertex(-0.5f, +0.5f, -3.0f, +0.25f, +0.25f, +1.0f),
	Vertex(-1.5f, +1.5f, -3.0f, +0.75f, +0.75f, +1.0f),
	Vertex(-1.5f, +0.5f, -3.0f, +0.75f, +0.25f, +1.0f),
}; 

void arrow(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_REPEAT)
	{
		for (int i = 0; i < sizeof(mesh) / sizeof(Vertex); ++i)
			mesh[i].z += 0.01f;

		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh), mesh, GL_STATIC_DRAW);
	}
	else if (key == GLFW_KEY_A && action == GLFW_REPEAT)
	{
		for (int i = 0; i < sizeof(mesh) / sizeof(Vertex); ++i)
			mesh[i].x += 0.05f;

		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh), mesh, GL_STATIC_DRAW);
	}
	else if (key == GLFW_KEY_S && action == GLFW_REPEAT)
	{
		for (int i = 0; i < sizeof(mesh) / sizeof(Vertex); ++i)
			mesh[i].z -= 0.01f;

		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh), mesh, GL_STATIC_DRAW);
	}
	else if (key == GLFW_KEY_D && action == GLFW_REPEAT)
	{
		for (int i = 0; i < sizeof(mesh) / sizeof(Vertex); ++i)
			mesh[i].x -= 0.05f;

		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh), mesh, GL_STATIC_DRAW);
	}

	else if (key == GLFW_KEY_X && action == GLFW_REPEAT)
	{
		for (int i = 0; i < sizeof(mesh) / sizeof(Vertex); ++i)
			mesh[i].y += 0.05f;

		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh), mesh, GL_STATIC_DRAW);
	}
	else if (key == GLFW_KEY_Z && action == GLFW_REPEAT)
	{
		for (int i = 0; i < sizeof(mesh) / sizeof(Vertex); ++i)
			mesh[i].y -= 0.05f;

		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh), mesh, GL_STATIC_DRAW);
	}
}

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1600, 900, "Minecraft", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error: Invalid rendering context" << std::endl;
	}

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);	

	const char* vertex_shader_src = "#version 450\n"
		"layout (location = 0) in vec3 vertex_pos;\n"
		"layout (location = 1) in vec2 vertex_tex_coord;\n"
		"layout (location = 2) in vec2 vertex_tex_id;\n"
		"out vec2 fragment_tex_coord;\n"
		"out vec2 fragment_tex_id;\n"
		"uniform mat4 matrix;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = matrix * vec4(vertex_pos, 1.0);\n"
		"	fragment_tex_coord = vertex_tex_coord;\n"
		"	fragment_tex_id = vertex_tex_id;\n"
		"}\n"; 

	const char* fragment_shader_src = "#version 450\n"
		"in vec2 fragment_tex_coord;\n"
		"in vec2 fragment_tex_id;\n"
		"out vec4 frag_color;\n"
		"uniform sampler2D texture_sampler;\n"
		"void main()\n"
		"{\n"
		"	if (fragment_tex_id.x != -0) frag_color = texture(texture_sampler, fragment_tex_coord);\n"
		"	else frag_color = vec4(0.0, 0.0, 0.75, 0.75);\n"
		"}\n";

	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
	glCompileShader(vertex_shader);

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
	glCompileShader(fragment_shader);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	unsigned int buf;
	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh), mesh, GL_STATIC_DRAW);

	unsigned int arr_buf;
	glGenVertexArrays(1, &arr_buf);
	glBindVertexArray(arr_buf);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(0 * sizeof(float)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(5 * sizeof(float)));

	const std::string& filename = "../Resources/images/room.png";
	int width = 1400;
	int height = 700;
	int bits_per_pixel = 24;

	stbi_set_flip_vertically_on_load(1);
	unsigned char* image_data = stbi_load(filename.c_str(), &width, &height, &bits_per_pixel, 4);

	unsigned int tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	if (image_data != nullptr) stbi_image_free(image_data);

	glUseProgram(program);

	int location = glGetUniformLocation(program, "texture_sampler");
	glUniform1i(location, 0);

	glm::mat4 matrix = glm::perspective(glm::radians(70.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
	location = glGetUniformLocation(program, "matrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_ADD);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glfwSetKeyCallback(window, arrow);
	
	while (!glfwWindowShouldClose(window))
	{
		glBindVertexArray(arr_buf);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(mesh) / sizeof(Vertex));

		glfwSwapBuffers(window);
		glfwPollEvents();
	} 

	glfwTerminate();
	return 0;
}
