#ifndef HITABLEH
#define HITABLEH

#include "Ray.h"
#include "Vector3.h"
#include <cmath>

struct HitRecord
{
    float t;
    Vector3 p;
    Vector3 normal;
};

class Hitable
{
public:
    virtual bool hit(const Ray& r, float min, float max, const HitRecord& record) const = 0;
};

class Sphere : Hitable
{
private:
    Vector3 center;
    float radius;
public:
    Sphere() {}
    Sphere(Vector3& center, float t) {
        this->center = center;
        this->radius = t;
    }
    bool hit(const Ray& r, float min, float max, HitRecord& record) const {
        Vector3 originToCenter = r.origin() - center;
        float a = Vector3::dot(r.direction(), r.direction());
        float b = Vector3::dot(originToCenter, r.direction());
        float c = Vector3::dot(originToCenter, originToCenter) - radius * radius;

        float discriminant = b * b - a * c;
        if (discriminant <= 0) {
            return false;
        }

        // -b - sqrt(b * b - a * c);
        float tmp = (-b - sqrt(discriminant)) / a;
        if (tmp < max && tmp > min) {
            record.t = tmp;
            record.p = r.pointAtParameter(tmp);
            record.normal = (record.p - center) / radius;
            return true;
        }
        // -b + sqrt(b * b - a * c)
        tmp = (-b + sqrt(b * b - a * c)) / a;
        if (tmp < max && tmp > min) {
            record.t = tmp;
            record.p = r.pointAtParameter(tmp);
            record.normal = (record.p - center) / radius;
            return true;
        }
        return false;
    }

};

#endif