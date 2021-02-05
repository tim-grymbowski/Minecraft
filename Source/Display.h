#pragma once


class Display
{
private:
	GLFWwindow* window;
public:
public:
	Display(int width, int height, const char* title);
	~Display();

	bool IsClosed();
	void Update();
	void Poll();

	inline void SetWidth(int width) {};
	inline void SetHeight(int height) {};
	inline void SetTitle(const char* title) {};

	inline GLFWwindow* Get() { return window; };
};
