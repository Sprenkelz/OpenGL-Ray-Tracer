#pragma once

#include "Ray.h"

struct hit_record;

class material
{
public:
	virtual bool scatter(const Ray& r_in, const hit_record& rec, glm::vec3& attenuation, Ray& scattere) const = 0;

};