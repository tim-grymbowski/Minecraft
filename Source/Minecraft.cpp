#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cstdint>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "./vendor/stb_image/stb_image.h"

#include "./vendor/glm/glm.hpp"
#include "./vendor/glm/gtc/matrix_transform.hpp"
#include "./vendor/glm/gtc/type_ptr.hpp"

#include "./Camera.h"
#include "./Vertex.h"
#include "./Player.h"
#include "./Block.h"
#include "./Renderer.h"
#include "./Level.h"
#include "./Chunk.h"
#include "./Material.h"
#include "./Mesh.h"
#include "./TaskManager.h"
#include "./Display.h"
#include "./Shader.h"
#include "./Texture.h"
#include "./TriangleVertex.h"


static Block blocks[64 * 64 * 64];
static Player player(0.0f, 0.0f, 0.0f);
static Camera camera;
static bool esc = false;
static double cursor_x0 = 0;
static double cursor_y0 = 0;

class ContentPointer {
private:
	Shader* shader;
	Player* player;
	Camera* camera;

	Mesh* mesh;
public:
	ContentPointer() { 
		shader = nullptr; 
		player = nullptr; 
		camera = nullptr;
		mesh = nullptr;
	}
	
	inline Shader* GetShader() { return shader; }
	inline void SetShader(Shader* shader) { this->shader = shader; }

	inline Player* GetPlayer() { return player; }
	inline void SetPlayer(Player* player) { this->player = player; }

	inline Camera* GetCamera() { return camera; }
	inline void SetCamera(Camera* camera) { this->camera = camera; }

	inline Mesh* GetMesh() { return mesh; }
	inline void SetMesh(Mesh* mesh) { this->mesh = mesh; }
};

inline void TranslatePlayer(Player* player, Camera* camera, Shader* shader, const glm::vec3& translation) {
	glm::mat4 playerMatrix = glm::identity<glm::mat4>();
	glm::mat4 upload = glm::identity<glm::mat4>();
	playerMatrix = glm::translate(playerMatrix, translation);
	player->Update(playerMatrix);
	upload = camera->GetMatrix() * player->GetMatrix();
	shader->SetMatrix("view", &upload[0][0]);
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	ContentPointer* content = (ContentPointer*)glfwGetWindowUserPointer(window);
	Shader* shader = content->GetShader();
	Player* player = content->GetPlayer();
	Camera* camera = content->GetCamera();

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		int cursor = esc ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
		glfwSetInputMode(window, GLFW_CURSOR, cursor);
		esc = !esc;
	}

	if (action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_W:
			TranslatePlayer(player, camera, shader, glm::vec3(+0.0f, +0.0f, -1.0f));
			break;
		case GLFW_KEY_A:
			TranslatePlayer(player, camera, shader, glm::vec3(-1.0f, +0.0f, +0.0f));
			break;
		case GLFW_KEY_S:
			TranslatePlayer(player, camera, shader, glm::vec3(+0.0f, +0.0f, +1.0f));
			break;
		case GLFW_KEY_D:
			TranslatePlayer(player, camera, shader, glm::vec3(+1.0f, +0.0f, +0.0f));
			break;
		case GLFW_KEY_Z:
			TranslatePlayer(player, camera, shader, glm::vec3(+0.0f, +1.0f, +0.0f));
			break;
		case GLFW_KEY_X:
			TranslatePlayer(player, camera, shader, glm::vec3(+0.0f, -1.0f, +0.0f));
			break;
		}
	}
}

void OnCursorPosEvent(GLFWwindow* window, double x, double y) {
	ContentPointer* content = (ContentPointer*)glfwGetWindowUserPointer(window);
	Shader* shader = content->GetShader();
	Player* player = content->GetPlayer();
	Camera* camera = content->GetCamera();

	double x_offset = x - cursor_x0;
	double y_offset = y - cursor_y0;
	
	if (!esc)
	{
		float yaw = x_offset / 4;
		float pitch = y_offset / 4;

		glm::mat4 playerMatrix = glm::identity<glm::mat4>();
		playerMatrix = glm::rotate(playerMatrix, glm::radians(yaw), glm::vec3(+0.0f, +1.0f, +0.0f));
		player->Update(playerMatrix);

		glm::mat4 cameraMatrix = glm::identity<glm::mat4>();
		cameraMatrix = glm::rotate(cameraMatrix, glm::radians(pitch), glm::vec3(+1.0f, +0.0f, +0.0f));
		camera->Update(cameraMatrix);

		glm::mat4 upload = camera->GetMatrix() * player->GetMatrix();
		shader->SetMatrix("view", &upload[0][0]);
	}

	cursor_x0 = x;
	cursor_y0 = y;
}

static int heightmap[64 * 64];

void TestChunkGeneration(ContentPointer* content) {
	static Player* player;
	static Camera* camera;
	static Shader* shader;

	static Mesh* mesh;

	player = content->GetPlayer();
	camera = content->GetCamera();
	shader = content->GetShader();

	mesh = content->GetMesh();

	glm::vec4 position = player->GetPosition();

	float fx = position.x;
	float fy = position.y;
	float fz = position.z;

	int ix = (int)fx;
	int iy = (int)fy;
	int iz = (int)fz;

	for (int x = 0; x < 64; ++x) {
		for (int z = 0; z < 64; ++z) {
			int index = x + (z << 6);
			int ox = ix + x - 31;
			int oz = iz + z - 31;
			int seed = ox + oz; // used to be ox & oz
			srand(seed);
			heightmap[index] = 5 + (rand() % (48 - 5));
		}
	}

	for (int y = 0; y < 64; ++y) {
		for (int z = 0; z < 64; ++z) {
			for (int x = 0; x < 64; ++x) {
				int t = 0;
				int c = 0;
				int height = heightmap[x + (z << 6)];

				if (height >= 64 - y) {
					t = 1; // stone
					c = 1; // opaque
				}
				else if ((64 - y > 5) && (64 - y <= 11)) {
					t = 2; // water
					c = 0; // translucent
				}
				else {
					t = 0; // air
					c = -1; // not visible
				}

				int index = x + (z << 6) + (y << 12);
				blocks[index].SetType(t);
				blocks[index].SetCode(c); 
			}
		}
	}

	std::vector<Vertex> solidMesh;

	for (int y = 0; y < 64; ++y) {
		for (int z = 0; z < 64; ++z) {
			for (int x = 0; x < 64; ++x) {
				int index = x + (z << 6) + (y << 12);
				int code = blocks[index].GetCode();

				if (code != -1) {
					float ox = fx + x - 31;
					float oz = fz + z - 31;

					if (x - 1 >= 0) {
						if (code != blocks[index - 1].GetCode()) {
							if (code == 1) {
								solidMesh.push_back(Vertex(-0.5f + ox, -0.5f - y, -2.0f + oz, +0.25f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, -0.5f - y, -1.0f + oz, +0.75f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, +0.5f - y, -1.0f + oz, +0.75f, +0.75f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, +0.5f - y, -2.0f + oz, +0.25f, +0.75f, +1.0f));
							}
						}
					}
					if (x + 1 <= 63) {
						if (code != blocks[index + 1].GetCode()) {
							if (code == 1) {
								solidMesh.push_back(Vertex(+0.5f + ox, -0.5f - y, -1.0f + oz, +0.25f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(+0.5f + ox, -0.5f - y, -2.0f + oz, +0.75f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(+0.5f + ox, +0.5f - y, -2.0f + oz, +0.75f, +0.75f, +1.0f));
								solidMesh.push_back(Vertex(+0.5f + ox, +0.5f - y, -1.0f + oz, +0.25f, +0.75f, +1.0f));
							}
						}
					}
					if (z - 1 >= 0) {
						if (code != blocks[index - 64].GetCode()) {
							if (code == 1) {
								solidMesh.push_back(Vertex(+0.5f + ox, -0.5f - y, -2.0f + oz, +0.25f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, -0.5f - y, -2.0f + oz, +0.75f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, +0.5f - y, -2.0f + oz, +0.75f, +0.75f, +1.0f));
								solidMesh.push_back(Vertex(+0.5f + ox, +0.5f - y, -2.0f + oz, +0.25f, +0.75f, +1.0f));
							}
						}
					}
					if (z + 1 <= 63) {
						if (code != blocks[index + 64].GetCode()) {
							if (code == 1) {
								solidMesh.push_back(Vertex(-0.5f + ox, -0.5f - y, -1.0f + oz, +0.25f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(+0.5f + ox, -0.5f - y, -1.0f + oz, +0.75f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(+0.5f + ox, +0.5f - y, -1.0f + oz, +0.75f, +0.75f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, +0.5f - y, -1.0f + oz, +0.25f, +0.75f, +1.0f));
							}
						}
					}
					if (y - 1 >= 0) {
						if (code != blocks[index - 4096].GetCode()) {

							// or is y perhaps flipped?
							if (code == 1) {
								solidMesh.push_back(Vertex(+0.5f + ox, -0.5f - y, -1.0f + oz, +0.25f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, -0.5f - y, -1.0f + oz, +0.75f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, -0.5f - y, -2.0f + oz, +0.75f, +0.75f, +1.0f));
								solidMesh.push_back(Vertex(+0.5f + ox, -0.5f - y, -2.0f + oz, +0.25f, +0.75f, +1.0f));
							}
						}
					}
					if (y + 1 <= 63) {
						if (code != blocks[index + 4096].GetCode()) {
							if (code == 1) {
								solidMesh.push_back(Vertex(+0.5f + ox, +0.5f - y, -2.0f + oz, +0.25f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, +0.5f - y, -2.0f + oz, +0.75f, +0.25f, +1.0f));
								solidMesh.push_back(Vertex(-0.5f + ox, +0.5f - y, -1.0f + oz, +0.75f, +0.75f, +1.0f));
								solidMesh.push_back(Vertex(+0.5f + ox, +0.5f - y, -1.0f + oz, +0.25f, +0.75f, +1.0f));
							}
						}
					}
				}
			}
		}
	}

	mesh->Data(solidMesh);
	content->SetMesh(mesh);

	glm::mat4 upload = camera->GetMatrix() * player->GetMatrix();
	shader->SetMatrix("view", &upload[0][0]);
}

int main(void) {
	Display display(1600, 900, "Minecraft");	

	glfwGetCursorPos(display.Get(), &cursor_x0, &cursor_y0);
	glfwSetInputMode(display.Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Renderer::Init();

	const char* vertexSource0 = "#version 450\n"
		"layout (location = 0) in vec3 vertexPosition;\n"
		"layout (location = 1) in vec2 vertexTexCoord;\n"
		"layout (location = 2) in vec2 vertexTexCode;\n"
		"out vec2 fragmentTexCoord;\n"
		"out vec2 fragmentTexCode;\n"
		"uniform mat4 proj;\n"
		"uniform mat4 view;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = proj * view * vec4(vertexPosition, 1.0);\n"
		"	fragmentTexCoord = vertexTexCoord;\n"
		"	fragmentTexCode = vertexTexCode;\n"
		"}\n";

	const char* fragmentSource0 = "#version 450\n"
		"in vec2 fragmentTexCoord;\n"
		"in vec2 fragmentTexCode;\n"
		"out vec4 outputColor;\n"
		"uniform sampler2D sampler;\n"
		"void main()\n"
		"{\n"
		"	if (fragmentTexCode.x == 1) {\n"
		"		outputColor = texture(sampler, fragmentTexCoord);\n"
		"	}\n"
		"}\n";

	Shader shader0(vertexSource0, fragmentSource0);

	glm::mat4 proj = glm::perspective(glm::radians(70.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
	shader0.SetMatrix("proj", &proj[0][0]);

	glm::mat4 view = player.GetMatrix();
	shader0.SetMatrix("view", &view[0][0]);

	ContentPointer content = ContentPointer();
	content.SetShader(&shader0);
	content.SetPlayer(&player);
	content.SetCamera(&camera);
	content.SetMesh(nullptr);

	glfwSetWindowUserPointer(display.Get(), &content);
	glfwSetKeyCallback(display.Get(), OnKeyEvent);
	glfwSetCursorPosCallback(display.Get(), OnCursorPosEvent);

	Texture texture0("../Resources/images/room.png", 1400, 700, 24, 0);
	shader0.SetSampler("sampler", texture0.GetSlot());

	Renderer::SetClearColor(0.0, 0.5, 1.0, 1.0);

	Mesh mesh0(std::vector<Vertex> {});
	mesh0.AddAttribute(0, 3, offsetof(Vertex, x));
	mesh0.AddAttribute(1, 2, offsetof(Vertex, u));
	mesh0.AddAttribute(2, 1, offsetof(Vertex, t));
	
	content.SetMesh(&mesh0);

	TestChunkGeneration(&content);

	while (!display.IsClosed()) {
		TestChunkGeneration(&content);
		Renderer::Clear(COLOR | DEPTH);
		Renderer::Submit(shader0, mesh0, texture0);
		display.Update();
		display.Poll();
	} 

	return 0;
}
