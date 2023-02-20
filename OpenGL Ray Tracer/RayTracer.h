#pragma once
#include <memory>
#include <glm/gtc/random.hpp>

#include "Ray.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"

class RayTracer
{
public:
	RayTracer();

	bool render(int width, int height);

	int* get_image_data(int* out_width, int* out_height) 
	{ 
		*out_width = m_image_width;
		*out_height = m_image_height;
		new_image_created = false;
		return m_image_data;
	};

private:
	glm::vec3 m_ray_color(const Ray& r, const hittable& world, int depth);

	int m_color_data(glm::vec3 color);

public:
	bool new_image_created;

private:
	HittableList m_world;
	int* m_image_data;
	int m_image_width;
	int m_image_height;
};