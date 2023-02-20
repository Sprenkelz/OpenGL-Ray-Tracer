#pragma once

#include <memory>

#include "Ray.h"

class material;

struct hit_record
{
	glm::vec3 p;
	glm::vec3 normal;
	std::shared_ptr<material> mat_ptr;
	float t;
	bool front_face;

	inline void set_face_normal(const Ray& r, const glm::vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable
{
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};