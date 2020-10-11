#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <vector>

// #include <WinUser.h>

float gravity = 0; // -0.05f;
/* Might be a bad idea to set as const */
const int num_vertex_data = 648;

/* This (and some variable values) need to be adjusted, 
to be of the form vertex, normal, vertex, normal, ..., 
and not of the form vertex, vertex, vertex, normal, ... */
float vertices[num_vertex_data] = {
		-0.5f, -0.5f, +1.0f, +0.0f, +0.0f, -1.0f,   -0.5f, +0.5f, +1.0f, +0.0f, +0.0f, -1.0f,   +0.5f, +0.5f, +1.0f, +0.0f, +0.0f, -1.0f,
		-0.5f, -0.5f, +1.0f, +0.0f, +0.0f, -1.0f,   +0.5f, +0.5f, +1.0f, +0.0f, +0.0f, -1.0f,   +0.5f, -0.5f, +1.0f, +0.0f, +0.0f, -1.0f,
															    
		+0.5f, -0.5f, +1.0f, +1.0f, +0.0f, +0.0f,   +0.5f, +0.5f, +1.0f, +1.0f, +0.0f, +0.0f,   +0.5f, +0.5f, +2.0f, +1.0f, +0.0f, +0.0f,
		+0.5f, -0.5f, +1.0f, +1.0f, +0.0f, +0.0f,   +0.5f, +0.5f, +2.0f, +1.0f, +0.0f, +0.0f,   +0.5f, -0.5f, +2.0f, +1.0f, +0.0f, +0.0f,
							 
		+0.5f, -0.5f, +2.0f, +0.0f, +0.0f, +1.0f,   +0.5f, +0.5f, +2.0f, +0.0f, +0.0f, +1.0f,   -0.5f, +0.5f, +2.0f, +0.0f, +0.0f, +1.0f,
		+0.5f, -0.5f, +2.0f, +0.0f, +0.0f, +1.0f,   -0.5f, +0.5f, +2.0f, +0.0f, +0.0f, +1.0f,   -0.5f, -0.5f, +2.0f, +0.0f, +0.0f, +1.0f,
							 
		-0.5f, -0.5f, +2.0f, -1.0f, +0.0f, +0.0f,   -0.5f, +0.5f, +2.0f, -1.0f, +0.0f, +0.0f,   -0.5f, +0.5f, +1.0f, -1.0f, +0.0f, +0.0f,
		-0.5f, -0.5f, +2.0f, -1.0f, +0.0f, +0.0f,   -0.5f, +0.5f, +1.0f, -1.0f, +0.0f, +0.0f,   -0.5f, -0.5f, +1.0f, -1.0f, +0.0f, +0.0f,
							 
		-0.5f, +0.5f, +1.0f, +0.0f, +1.0f, +0.0f,   -0.5f, +0.5f, +2.0f, +0.0f, +1.0f, +0.0f,   +0.5f, +0.5f, +2.0f, +0.0f, +1.0f, +0.0f,
		-0.5f, +0.5f, +1.0f, +0.0f, +1.0f, +0.0f,   +0.5f, +0.5f, +2.0f, +0.0f, +1.0f, +0.0f,   +0.5f, +0.5f, +1.0f, +0.0f, +1.0f, +0.0f,
							 
		-0.5f, -0.5f, +2.0f, +0.0f, -1.0f, +0.0f,   -0.5f, -0.5f, +1.0f, +0.0f, -1.0f, +0.0f,   +0.5f, -0.5f, +1.0f, +0.0f, -1.0f, +0.0f,
		-0.5f, -0.5f, +2.0f, +0.0f, -1.0f, +0.0f,   +0.5f, -0.5f, +1.0f, +0.0f, -1.0f, +0.0f,   +0.5f, -0.5f, +2.0f, +0.0f, -1.0f, +0.0f,

		// increased z by +1 and x by -1
		
		-1.5f, -0.5f, +2.0f, +0.0f, +0.0f, -1.0f,   -1.5f, +0.5f, +2.0f, +0.0f, +0.0f, -1.0f,   -0.5f, +0.5f, +2.0f, +0.0f, +0.0f, -1.0f,
		-1.5f, -0.5f, +2.0f, +0.0f, +0.0f, -1.0f,   -0.5f, +0.5f, +2.0f, +0.0f, +0.0f, -1.0f,   -0.5f, -0.5f, +2.0f, +0.0f, +0.0f, -1.0f,

		-0.5f, -0.5f, +2.0f, +1.0f, +0.0f, +0.0f,   -0.5f, +0.5f, +2.0f, +1.0f, +0.0f, +0.0f,   -0.5f, +0.5f, +3.0f, +1.0f, +0.0f, +0.0f,
		-0.5f, -0.5f, +2.0f, +1.0f, +0.0f, +0.0f,   -0.5f, +0.5f, +3.0f, +1.0f, +0.0f, +0.0f,   -0.5f, -0.5f, +3.0f, +1.0f, +0.0f, +0.0f,

		-0.5f, -0.5f, +3.0f, +0.0f, +0.0f, +1.0f,   -0.5f, +0.5f, +3.0f, +0.0f, +0.0f, +1.0f,   -1.5f, +0.5f, +3.0f, +0.0f, +0.0f, +1.0f,
		-0.5f, -0.5f, +3.0f, +0.0f, +0.0f, +1.0f,   -1.5f, +0.5f, +3.0f, +0.0f, +0.0f, +1.0f,   -1.5f, -0.5f, +3.0f, +0.0f, +0.0f, +1.0f,

		-1.5f, -0.5f, +3.0f, -1.0f, +0.0f, +0.0f,   -1.5f, +0.5f, +3.0f, -1.0f, +0.0f, +0.0f,   -1.5f, +0.5f, +2.0f, -1.0f, +0.0f, +0.0f,
		-1.5f, -0.5f, +3.0f, -1.0f, +0.0f, +0.0f,   -1.5f, +0.5f, +2.0f, -1.0f, +0.0f, +0.0f,   -1.5f, -0.5f, +2.0f, -1.0f, +0.0f, +0.0f,

		-1.5f, +0.5f, +2.0f, +0.0f, +1.0f, +0.0f,   -1.5f, +0.5f, +3.0f, +0.0f, +1.0f, +0.0f,   -0.5f, +0.5f, +3.0f, +0.0f, +1.0f, +0.0f,
		-1.5f, +0.5f, +2.0f, +0.0f, +1.0f, +0.0f,   -0.5f, +0.5f, +3.0f, +0.0f, +1.0f, +0.0f,   -0.5f, +0.5f, +2.0f, +0.0f, +1.0f, +0.0f,

		-1.5f, -0.5f, +3.0f, +0.0f, -1.0f, +0.0f,   -1.5f, -0.5f, +2.0f, +0.0f, -1.0f, +0.0f,   -0.5f, -0.5f, +2.0f, +0.0f, -1.0f, +0.0f,
		-1.5f, -0.5f, +3.0f, +0.0f, -1.0f, +0.0f,   -0.5f, -0.5f, +2.0f, +0.0f, -1.0f, +0.0f,   -0.5f, -0.5f, +3.0f, +0.0f, -1.0f, +0.0f,

		//increased z by +1, x by -1, and y by +1
		
		-1.5f, +0.5f, +2.0f, +0.0f, +0.0f, -1.0f,   -1.5f, +1.5f, +2.0f, +0.0f, +0.0f, -1.0f,   -0.5f, +1.5f, +2.0f, +0.0f, +0.0f, -1.0f,
		-1.5f, +0.5f, +2.0f, +0.0f, +0.0f, -1.0f,   -0.5f, +1.5f, +2.0f, +0.0f, +0.0f, -1.0f,   -0.5f, +0.5f, +2.0f, +0.0f, +0.0f, -1.0f,

		-0.5f, +0.5f, +2.0f, +1.0f, +0.0f, +0.0f,   -0.5f, +1.5f, +2.0f, +1.0f, +0.0f, +0.0f,   -0.5f, +1.5f, +3.0f, +1.0f, +0.0f, +0.0f,
		-0.5f, +0.5f, +2.0f, +1.0f, +0.0f, +0.0f,   -0.5f, +1.5f, +3.0f, +1.0f, +0.0f, +0.0f,   -0.5f, +0.5f, +3.0f, +1.0f, +0.0f, +0.0f,

		-0.5f, +0.5f, +3.0f, +0.0f, +0.0f, +1.0f,   -0.5f, +1.5f, +3.0f, +0.0f, +0.0f, +1.0f,   -1.5f, +1.5f, +3.0f, +0.0f, +0.0f, +1.0f,
		-0.5f, +0.5f, +3.0f, +0.0f, +0.0f, +1.0f,   -1.5f, +1.5f, +3.0f, +0.0f, +0.0f, +1.0f,   -1.5f, +0.5f, +3.0f, +0.0f, +0.0f, +1.0f,

		-1.5f, +0.5f, +3.0f, -1.0f, +0.0f, +0.0f,   -1.5f, +1.5f, +3.0f, -1.0f, +0.0f, +0.0f,   -1.5f, +1.5f, +2.0f, -1.0f, +0.0f, +0.0f,
		-1.5f, +0.5f, +3.0f, -1.0f, +0.0f, +0.0f,   -1.5f, +1.5f, +2.0f, -1.0f, +0.0f, +0.0f,   -1.5f, +0.5f, +2.0f, -1.0f, +0.0f, +0.0f,

		-1.5f, +1.5f, +2.0f, +0.0f, +1.0f, +0.0f,   -1.5f, +1.5f, +3.0f, +0.0f, +1.0f, +0.0f,   -0.5f, +1.5f, +3.0f, +0.0f, +1.0f, +0.0f,
		-1.5f, +1.5f, +2.0f, +0.0f, +1.0f, +0.0f,   -0.5f, +1.5f, +3.0f, +0.0f, +1.0f, +0.0f,   -0.5f, +1.5f, +2.0f, +0.0f, +1.0f, +0.0f,

		-1.5f, +0.5f, +3.0f, +0.0f, -1.0f, +0.0f,   -1.5f, +0.5f, +2.0f, +0.0f, -1.0f, +0.0f,   -0.5f, +0.5f, +2.0f, +0.0f, -1.0f, +0.0f,
		-1.5f, +0.5f, +3.0f, +0.0f, -1.0f, +0.0f,   -0.5f, +0.5f, +2.0f, +0.0f, -1.0f, +0.0f,   -0.5f, +0.5f, +3.0f, +0.0f, -1.0f, +0.0f,
};

void cb(GLFWwindow* window, int key, int scancode, int action, int mods) {

	/* Figure out rotation by dragging the cursor! */
	/* What if a cube contains the camera ??? */
	if (key == GLFW_KEY_W && action == GLFW_PRESS | !GLFW_RELEASE) {
		if (!gravity) {
			for (int i = 0; i < num_vertex_data; i++) {
				/*if (((i % 3) == 1) && !((-1.0f + 0.05f <= vertices[i]) && (vertices[i] <= 1.0f + 0.05f)))*/
				if ((i % 6) == 1) vertices[i] -= 0.05f;
			}
		}
	} else if (key == GLFW_KEY_A && action == GLFW_PRESS | !GLFW_RELEASE) {
		for (int i = 0; i < num_vertex_data; i++) {
			/*if (((i % 3) == 0) && !((-0.5f - 0.05f <= vertices[i]) && (vertices[i] <= 0.5f - 0.05f)))*/ 
			if ((i % 6) == 0) vertices[i] += 0.05f;
		}
	} else if (key == GLFW_KEY_D && action == GLFW_PRESS | !GLFW_RELEASE) {
		for (int i = 0; i < num_vertex_data; i++) {
			/*if (((i % 3) == 0) && !((-0.5f + 0.05f <= vertices[i]) && (vertices[i] <= 0.5f + 0.05f)))*/
			if ((i % 6) == 0) vertices[i] -= 0.05f;
		}
	} else if (key == GLFW_KEY_S && action == GLFW_PRESS | !GLFW_RELEASE) {
		if (!gravity) {
			for (int i = 0; i < num_vertex_data; i++) {
				/*if (((i % 3) == 1) && !((-1.0f - 0.05f <= vertices[i]) && (vertices[i] <= 1.0f - 0.05f)))*/
				if ((i % 6) == 1) vertices[i] += 0.05f;
			}
		}
	} else if (key == GLFW_KEY_Z && action == GLFW_PRESS | !GLFW_RELEASE) {
		for (int i = 0; i < num_vertex_data; i++) {
			/*if (((i % 3) == 2) && !((-0.5f - 0.05f <= vertices[i]) && (vertices[i] <= 0.5f - 0.05f)))*/
			if ((i % 6) == 2) vertices[i] += 0.05f;
		} /* USING i += 3 rather than i % 3 should be much more efficient! */
	} else if (key == GLFW_KEY_X && action == GLFW_PRESS | !GLFW_RELEASE) {
		for (int i = 0; i < num_vertex_data; i++) {
			/*if (((i % 3) == 2) && !((-0.5f + 0.05f <= vertices[i]) && (vertices[i] <= 0.5f + 0.05f)))*/
			if ((i % 6) == 2) vertices[i] -= 0.05f;
		} 
	} else if (key == GLFW_KEY_F && action == GLFW_PRESS | !GLFW_RELEASE) {
		// CLOCKWISE
		for (int i = 0; i < num_vertex_data; i += 6) {
			float x = vertices[i] * cosf(-0.005f) - vertices[i + 2] * sinf(-0.005f);
			float z = vertices[i] * sinf(-0.005f) + vertices[i + 2] * cosf(-0.005f);
			vertices[i] = x;
			vertices[i + 2] = z;
		} 
	} else if (key == GLFW_KEY_G && action == GLFW_PRESS | !GLFW_RELEASE) {
		// COUNTER-CLOCKWISE
		for (int i = 0; i < num_vertex_data; i += 6) {
			float x = vertices[i] * cosf(+0.005f) - vertices[i + 2] * sinf(+0.005f);
			float z = vertices[i] * sinf(+0.005f) + vertices[i + 2] * cosf(+0.005f);
			vertices[i] = x;
			vertices[i + 2] = z;
		}
	} else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		static int i = 0;
		//off : on if on by default, else on : off
		//find alternative to ++ so there is no limit
		//to how many times you can toggle
		gravity = !(i++ % 2) ? 0.0f : -0.05f;
		if (gravity == 0.0f) { 
			std::cout << "Gravity turned off!\n"; 
		}
		else { 
			std::cout << "Gravity turned on!\n"; 
		}
	} else if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		/* Let x stay x, and exchange y and z (or -y and z, or x and -x) */
		std::vector<float> vec_y;
		std::vector<float> vec_z;
		for (int i = 0; i < num_vertex_data; i++) {
			if ((i % 6) == 1) {
				vec_y.push_back(vertices[i]);
			} else if ((i % 6) == 2) {
				vec_z.push_back(vertices[i]);
			}
		}
		for (int i = 0; i < num_vertex_data; i++) {
			if ((i % 6) == 1) {
				vertices[i] = vec_z[(i - 1) / 6];
			} else if ((i % 6) == 2) {
				vertices[i] = vec_y[(i - 2) / 6];
			}
		}
	}
	glBufferData(GL_ARRAY_BUFFER, num_vertex_data * sizeof(float), vertices, GL_STATIC_DRAW);
}

/*INPUT ip;
ip.type = INPUT_KEYBOARD;
ip.ki.wScan = 0;
ip.ki.time = 0;
ip.ki.dwExtraInfo = 0;
ip.ki.wVk = 0x26;
ip.ki.dwFlags = 0;*/

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1680, 1050, "Minecraft", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	unsigned int vertex_buffer = 0;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, (num_vertex_data / 4) * sizeof(float), vertices, GL_STATIC_DRAW);

	unsigned int vertex_array = 0;
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	/* experiment with first index */
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

	glfwSetKeyCallback(window, cb);

	const char* vertex_shader =
		"#version 150\n"
		"in vec3 pos;\n"
		"out vec3 pos_c;\n"
		"mat4 mat_proj = mat4(\n"
		"	1050.0/1680.0 * 1.0/tan(0.5), 0.0,		    0.0,           0.0,\n"
		"	0.0,						  1.0/tan(0.5), 0.0,           0.0,\n"
		"	0.0,						  0.0,			1000.0/999.0,  0.0,\n"
		"	0.0,						  0.0,			-1000.0/999.0, 1.0\n"
		");\n"
		"void main() {\n"
		"	pos_c = pos;\n"
		"	gl_Position = mat_proj * vec4(pos, pos.z);"
		"}\n";
	
	const char* fragment_shader =
		"#version 150\n"
		"in vec3 pos_c;\n"
		"out vec4 new_color;\n"
		"/*uniform vec4 color;*/\n"
		"/*in vec4 color = vec4(0.0, 1.0, 0.0, 1.0);*/\n"
		"void main() {\n"
		"	new_color = vec4(0.8, 0.1, 0.0, 1.0); /*color;*/\n"
		"}\n";

	unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &fragment_shader, NULL);
	glCompileShader(fragment_shader_id);

	unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id, 1, &vertex_shader, NULL);
	glCompileShader(vertex_shader_id);

	unsigned int program = glCreateProgram();
	glAttachShader(program, fragment_shader_id);
	glAttachShader(program, vertex_shader_id);
	glLinkProgram(program);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	
	while (!glfwWindowShouldClose(window))
	{
		/*SendInput(1, &ip, sizeof(INPUT));*/

		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

		glBindVertexArray(vertex_array);

		glDrawArrays(GL_TRIANGLES, 0, (num_vertex_data / 3));

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (gravity) {
			/* A better alternative is to regularly check the time */
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			for (int i = 0; i < num_vertex_data; i++) {
				if ((i % 3) == 1) vertices[i] += gravity;
			}
			glBufferData(GL_ARRAY_BUFFER, num_vertex_data * sizeof(float), vertices, GL_STATIC_DRAW); 
		}
	}
	glfwTerminate();
}


