#pragma once

#include <glm/gtc/random.hpp>

#include "material.h"
#include "Hittable.h"

class lambertian : public material
{
public:
	lambertian(const glm::vec3 a) : albedo(a) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, glm::vec3& attenuation, Ray& scattered) const override
	{
		auto scatter_direction = rec.normal + normalize(glm::sphericalRand(1.0f));

		const auto s = 1e-8;
		if (scatter_direction.x < s && scatter_direction.y < s && scatter_direction.z < s)
			scatter_direction = rec.normal;

		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

public:
	glm::vec3 albedo;
};