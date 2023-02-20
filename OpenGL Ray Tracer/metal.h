#pragma once

#include "material.h"
#include "Hittable.h"

class metal : public material
{
public:
	metal(const glm::vec3& a) : albedo(a) {}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, glm::vec3& attenuation, Ray& scattered) const override
	{
		auto v = normalize(r_in.direction());
		auto n = rec.normal;
		glm::vec3 reflected = v - 2 * dot(v, n) * n;
		scattered = Ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}


public:
	glm::vec3 albedo;
};