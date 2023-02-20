#pragma once
#include <iostream>
#include <memory>

#include "WindowContext.h"
#include "UIContext.h"
#include "RayTracer.h"


class Application
{

public:
	Application();

	void loop();

private:
	void m_create_texture(GLuint* out_texture, int* image_data, int image_width, int image_height);

	GLFWwindow* m_glWindow;

	std::shared_ptr<RayTracer> m_ray_tracer;
	std::unique_ptr<WindowContext> m_window;
	std::unique_ptr<UIContext> m_UI;
};