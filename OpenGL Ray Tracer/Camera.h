#pragma once

#include <glm/vec3.hpp>
#include "Ray.h"

class Camera
{
public:
	Camera(float aspect_ratio);

	Ray get_ray(float u, float v) const;

private:
	glm::vec3 origin;
	glm::vec3 lower_left_corner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
};