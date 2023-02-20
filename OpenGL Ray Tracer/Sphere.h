#pragma once

#include "hittable.h"

class Sphere : public hittable
{
public:
	Sphere(glm::vec3 cen, float r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {};

	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;


public:
	glm::vec3 center;
	float radius;
	std::shared_ptr<material> mat_ptr;
};