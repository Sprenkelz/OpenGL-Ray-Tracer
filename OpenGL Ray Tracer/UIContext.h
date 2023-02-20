#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "RayTracer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class UIContext
{
public:
	UIContext(GLFWwindow* window, std::shared_ptr<RayTracer> ray_tracer_context);

	~UIContext();

	void pre_render(GLuint texture, int texture_width, int texture_height);

	void post_render();
private:
	std::shared_ptr<RayTracer> m_ray_tracer;

	int m_viewport_x;

	int m_viewport_y;
};

