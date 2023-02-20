#include "Sphere.h"

bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
{
	glm::vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b_half = dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	
	auto discriminant = b_half * b_half - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	auto root = (-b_half - sqrt(discriminant)) / a;

	if (root < t_min || t_max < root)
	{
		root = (-b_half + sqrt(discriminant)) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(root);
	auto outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;

    return true;
}
