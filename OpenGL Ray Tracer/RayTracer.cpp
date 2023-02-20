#include "RayTracer.h"

RayTracer::RayTracer()
{
	new_image_created = false;

	auto material_ground = std::make_shared<lambertian>(glm::vec3(0.8f, 0.8f, 0.0f));
	auto material_center = std::make_shared<lambertian>(glm::vec3(0.7f, 0.3f, 0.3f));
	auto material_left = std::make_shared<metal>(glm::vec3(0.8f, 0.8f, 0.8f));
	auto material_right = std::make_shared<metal>(glm::vec3(0.8f, 0.6f, 0.2f));

	m_world.add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f, material_ground));
	m_world.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, material_center));
	m_world.add(std::make_shared<Sphere>(glm::vec3(-1.0f, 0.0f, -1.0f), 0.5f, material_left));
	m_world.add(std::make_shared<Sphere>(glm::vec3(1.0f, 0.0f, -1.0f), 0.5f, material_right));
}

bool RayTracer::render(int width, int height)
{
	m_image_width = width;
	m_image_height = height;
	Camera cam((float)width / height);
	m_image_data = new int[width * height];

	const int samples_per_pixel = 10;
	const int max_depth = 5;

	for (int j = height-1, k = 0; j >= 0; j--)
	{
		for (int i = 0; i < width; i++, k++)
		{
			glm::vec3 pixel_color(0.0f);
			for (int s = 0; s < samples_per_pixel; s++)
			{
				auto u = (i + glm::linearRand(0.0f, 1.0f)) / (width - 1);
				auto v = (j + glm::linearRand(0.0f, 1.0f)) / (height - 1);
				Ray r = cam.get_ray(u, v);
				pixel_color += m_ray_color(r, m_world, max_depth);
			}
			pixel_color = sqrt(pixel_color * (1.0f / samples_per_pixel));
			m_image_data[k] = m_color_data(pixel_color);
		}
	}

	new_image_created = true;
	return true;
}

glm::vec3 RayTracer::m_ray_color(const Ray& r, const hittable& world, int depth)
{
	hit_record rec;

	if (depth <= 0)
		return glm::vec3(0.0f);

	if (world.hit(r, 0.001f, INFINITY, rec))
	{
		Ray scattered;
		glm::vec3 attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * m_ray_color(scattered, world, depth - 1);

		return glm::vec3(0.0f);
	}

	auto unit_direction = glm::normalize(r.direction());
	auto t = 0.5f * (unit_direction.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

int RayTracer::m_color_data(glm::vec3 color)
{
	int color_data = 0;
	color_data |= 0xff000000;
	color_data |= static_cast<int>(color.z * 255) << 8 * 2;
	color_data |= static_cast<int>(color.y * 255) << 8 * 1;
	color_data |= static_cast<int>(color.x * 255) << 8 * 0;

	return color_data;
}