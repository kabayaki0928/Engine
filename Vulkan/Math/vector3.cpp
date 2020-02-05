#include "vector3.h"

namespace cengine
{
    const Vector3 Vector3::zero = Vector3();
    const Vector3 Vector3::one  = Vector3(1.0f, 1.0f, 1.0f);

    const Vector3 Vector3::up       = Vector3( 0.0f,  1.0f,  0.0f);
    const Vector3 Vector3::down     = Vector3( 0.0f, -1.0f,  0.0f);
    const Vector3 Vector3::right    = Vector3( 1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::left     = Vector3(-1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::forward  = Vector3( 0.0f,  0.0f,  1.0f);
    const Vector3 Vector3::back     = Vector3( 0.0f,  0.0f, -1.0f);

    /// <summary>
    /// コンストラクタ
    /// </summary>
    Vector3::Vector3()
        : x_(0),
          y_(0),
          z_(0) {
    }
    Vector3::Vector3(float x, float y, float z)
        : x_(x),
          y_(y),
          z_(z) {
    }
    Vector3::Vector3(const Vector3& v)
        : x_(v.x_),
          y_(v.y_),
          z_(v.z_) {
    }

    /// <summary>
    /// Vector3型の一致比較
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    inline bool Vector3::operator==(const Vector3& v) {
        return fabs(x_ - v.x_) < FLT_EPSILON
            && fabs(y_ - v.y_) < FLT_EPSILON
            && fabs(z_ - v.z_) < FLT_EPSILON;
    }

    /// <summary>
    /// Vector3型の不一致比較
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    inline bool Vector3::operator!=(const Vector3& v) {
        return !(*this == v);
    }
    inline Vector3& Vector3::operator+=(const Vector3 &v) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
        return *this;
    }
    inline Vector3& Vector3::operator*=(const Vector3 &v) {
        x_ *= v.x_;
        y_ *= v.y_;
        z_ *= v.z_;
        return *this;
    }
    inline Vector3& Vector3::operator/=(const Vector3 &v) {
        x_ /= v.x_;
        y_ /= v.y_;
        z_ /= v.z_;
        return *this;
    }
    inline Vector3& Vector3::operator-=(const Vector3 &v) {
        x_ -=v.x_;
        y_ -=v.y_;
        z_ -=v.z_;
        return *this;
    }
    inline Vector3& Vector3::operator*=(const float t) {
        x_ *= t;
        y_ *= t;
        z_ *= t;
        return *this;
    }
    inline Vector3& Vector3::operator/=(const float t) {
        float k = 1.0 / t;
        x_ *= k;
        y_ *= k;
        z_ *= k;
        return *this;
    }

    inline std::istream& Vector3::getInStream(std::istream& istream) {
        istream >> x_ >> y_ >> z_;
        return istream;
    }
    inline std::ostream& Vector3::getOutStream(std::ostream& ostream) {
        ostream << x_ << y_ << z_;
        return ostream;
    }

    inline float Vector3::length() const {
        return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }
    inline float Vector3::squaredLength() const {
        return x_ * x_ + y_ * y_ + z_ * z_;
    }
    inline void Vector3::makeUnitVector() {
        float k = 1.0 / sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        x_ *= k;
        y_ *= k;
        z_ *= k;
    }
    inline Vector3 unitVector(Vector3 v) {
        return v / v.length();
    }

    inline std::istream& operator>>(std::istream& is, Vector3& t) {
        return t.getInStream(is);
    }
    inline std::ostream& operator<<(std::ostream& os, Vector3& t) {
        return t.getOutStream(os);
    }
    inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
        return Vector3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
    }
    inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2) {
        return Vector3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
    }
    inline Vector3 operator* (const Vector3 &v1, const Vector3 &v2) {
        return Vector3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
    }
    inline Vector3 operator/(const Vector3 &v1, const Vector3 &v2) {
        return Vector3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
    }
    inline Vector3 operator*(float t, const Vector3 &v) {
        return Vector3(t*v.x(), t*v.y(), t*v.z());
    }
    inline Vector3 operator/(Vector3 v, float t) {
        return Vector3(v.x() / t, v.y() / t, v.z() / t);
    }
    inline Vector3 Vector3::operator*(float t) {
        return Vector3(t*x_, t*y_, t*z_);
    }
    inline float dot(const Vector3 &v1, const Vector3 &v2) {
        return v1.x() * v2.x()
             + v1.y() * v2.y()
             + v1.z() * v2.z();
    }
    inline Vector3 cross(const Vector3 &v1, const Vector3 & v2) {
        return Vector3
        (
            (v1.y()   * v2.z() - v1.z() * v2.y()),
            (-(v1.x() * v2.z() - v1.z() * v2.x())),
            (v1.x()   * v2.y() - v1.y() * v2.x())
        );
    }
} // cengine