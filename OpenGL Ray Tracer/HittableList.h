#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

class HittableList : public hittable
{
public:
	HittableList() {};
	HittableList(std::shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const override;

public:
	std::vector<std::shared_ptr<hittable>> objects;
};