#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class WindowContext
{
public:
	WindowContext(int width, int height, const char* title);


	~WindowContext();

	static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void on_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	static void on_window_size_callback(GLFWwindow* window, int width, int height);

	static void on_window_close_callback(GLFWwindow* window);

	void pre_render();

	void post_render();

	GLFWwindow* get_native_window() { return m_glwindow; };
private:
	GLFWwindow* m_glwindow;
};