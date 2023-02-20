#include "Application.h"

Application::Application()
{
	m_ray_tracer = std::make_shared<RayTracer>();
	m_window = std::make_unique<WindowContext>(1600, 900, "Among us");
	m_glWindow = m_window->get_native_window();
	if (!m_glWindow)
	{
		return;
	}

	m_UI = std::make_unique<UIContext>(m_glWindow, m_ray_tracer);
}

void Application::loop()
{
	bool isRunning = true;

	GLuint texture;
	int image_width = 640;
	int image_height = 480;
	m_ray_tracer->render(image_width, image_height);
	auto image_data = m_ray_tracer->get_image_data(&image_width, &image_height);
	m_create_texture(&texture, image_data, image_width, image_height);

	while (isRunning)
	{
		m_window->pre_render();

		if (m_ray_tracer->new_image_created)
		{
			image_data = m_ray_tracer->get_image_data(&image_width, &image_height);
			m_create_texture(&texture, image_data, image_width, image_height);
		}

		m_UI->pre_render(texture, image_width, image_height);

		m_UI->post_render();

		m_window->post_render();
	}
}

void Application::m_create_texture(GLuint* out_texture, int* image_data, int image_width, int image_height)
{

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	*out_texture = image_texture;
}