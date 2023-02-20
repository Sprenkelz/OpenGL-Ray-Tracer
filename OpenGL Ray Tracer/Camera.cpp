#include "Camera.h"

Camera::Camera(float aspect_ratio)
{
	auto viewport_height = 2.0f;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0f;

	origin = glm::vec3(0.0f);
	horizontal = glm::vec3(viewport_width, 0.0f, 0.0f);
	vertical = glm::vec3(0.0f, viewport_height, 0.0f);
	lower_left_corner = origin - horizontal * 0.5f - vertical * 0.5f - glm::vec3(0.0f, 0.0f, focal_length);
}

Ray Camera::get_ray(float u, float v) const
{
	return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}
