#include "WindowContext.h"

WindowContext::WindowContext(int width, int height, const char* title)
{
	if (!glfwInit())
	{
		std::cout << "Failed to initiate GLFW" << std::endl;
		m_glwindow = nullptr;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_glwindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (m_glwindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetKeyCallback(m_glwindow, on_key_callback);
	glfwSetScrollCallback(m_glwindow, on_scroll_callback);
	glfwSetWindowSizeCallback(m_glwindow, on_window_size_callback);
	glfwSetWindowCloseCallback(m_glwindow, on_window_close_callback);
	glfwMakeContextCurrent(m_glwindow);

	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize glad!" << std::endl;
		m_glwindow = nullptr;
		return;
	}

	glViewport(0, 0, width, height);
}



WindowContext::~WindowContext()
{
	// Delete window before ending the program
	glfwDestroyWindow(m_glwindow);
	// Terminate GLFW before ending the program
	glfwTerminate();
}

void WindowContext::on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "KEY CALLBACK" << std::endl;
}

void WindowContext::on_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	std::cout << "SCROLL CALLBACK" << std::endl;
}

void WindowContext::on_window_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "WINDOW SIZE CALLBACK" << std::endl;
}

void WindowContext::on_window_close_callback(GLFWwindow* window)
{
	std::cout << "WINDOW CLOSE CALLBACK" << std::endl;
}

void WindowContext::pre_render()
{
	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
}

void WindowContext::post_render()
{
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(m_glwindow);
	// Take care of all GLFW events
	glfwPollEvents();
}