#include <iostream>

#include <GLFW/glfw3.h>

#include "./Display.h"


Display::Display(int width, int height, const char* title)
{
	if (!glfwInit())
		std::cerr << "Error: Failed to initialize GLFW" << std::endl;
	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		std::cerr << "Error: Failed to create window" << std::endl;
	}
	glfwMakeContextCurrent(window);
}

Display::~Display()
{
	glfwTerminate();
}

bool Display::IsClosed()
{
	return glfwWindowShouldClose(window);
}

void Display::Update()
{
	glfwSwapBuffers(window);
}

void Display::Poll()
{
	glfwPollEvents();
}
