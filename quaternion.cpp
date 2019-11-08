//#include "quaternion.h"
//
//namespace cengine
//{
//    const Quaternion Quaternion::identity(0.0f, 0.0f, 0.0f, );
//
//    Quaternion::Quaternion()
//        : x_(0.0f), y_(0.0f), z_(0.0f), w_(0.0f) {
//    }
//    Quaternion::Quaternion(float x, float y, float z, float w)
//        : x_(x), y_(y), z_(z), w_(w) {
//    }
//    Quaternion::Quaternion(const Quaternion& q) {
//        w_ = q.w_;
//        x_ = q.x_;
//        y_ = q.y_;
//        z_ = q.z_;
//    }
//    Quaternion::~Quaternion() {
//    }
//
//    Quaternion& Quaternion::operator=(const Quaternion& q) {
//        if (this == &q) return *this;
//        w_ = q.w_;
//        x_ = q.x_;
//        y_ = q.y_;
//        z_ = q.z_;
//        return *this;
//    }
//
//    bool Quaternion::operator==(Quaternion& rhs) {
//        return (w_ == rhs.w_ && x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_);
//    }
//
//    bool Quaternion::operator!=(Quaternion& rhs) {
//        return !(w_ == rhs.w_ && x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_);
//    }
//
//    Quaternion& Quaternion::operator*=(Quaternion& rhs) {
//        Quaternion q;
//
//        q.w_ = w_ * rhs.w_ - x_ * rhs.x_ - y_ * rhs.y_ - z_ * rhs.z_;
//        q.x_ = w_ * rhs.x_ + x_ * rhs.w_ + y_ * rhs.z_ - z_ * rhs.y_;
//        q.y_ = w_ * rhs.y_ - x_ * rhs.z_ + y_ * rhs.w_ + z_ * rhs.x_;
//        q.z_ = w_ * rhs.z_ + x_ * rhs.y_ - y_ * rhs.x_ + z_ * rhs.w_;
//
//        *this = q;
//        return *this;
//    }
//
//    Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
//        Quaternion q;
//
//        q.w_ = w_ * rhs.w_ - x_ * rhs.x_ - y_ * rhs.y_ - z_ * rhs.z_;
//        q.x_ = w_ * rhs.x_ + x_ * rhs.w_ + y_ * rhs.z_ - z_ * rhs.y_;
//        q.y_ = w_ * rhs.y_ - x_ * rhs.z_ + y_ * rhs.w_ + z_ * rhs.x_;
//        q.z_ = w_ * rhs.z_ + x_ * rhs.y_ - y_ * rhs.x_ + z_ * rhs.w_;
//
//        *this = q;
//        return *this;
//    }
//
//    Quaternion Quaternion::operator*(Quaternion& rhs) {
//        Quaternion q;
//
//        q.w_ = w_ * rhs.w_ - x_ * rhs.x_ - y_ * rhs.y_ - z_ * rhs.z_;
//        q.x_ = w_ * rhs.x_ + x * rhs.w_ + y_ * rhs.z_ - z_ * rhs.y_;
//        q.y_ = w_ * rhs.y_ - x * rhs.z_ + y_ * rhs.w_ + z_ * rhs.x;
//        q.z_ = w_ * rhs.z_ + x * rhs.y_ - y_ * rhs.x + z_ * rhs.w_;
//
//        return q;
//    }
//
//    const Quaternion Quaternion::operator*(const Quaternion& rhs) {
//        Quaternion q;
//
//        q.w_ = w_ * rhs.w_ - x * rhs.x - y_ * rhs.y_ - z_ * rhs.z_;
//        q.x = w_ * rhs.x + x * rhs.w_ + y_ * rhs.z_ - z_ * rhs.y_;
//        q.y_ = w_ * rhs.y_ - x * rhs.z_ + y_ * rhs.w_ + z_ * rhs.x;
//        q.z_ = w_ * rhs.z_ + x * rhs.y_ - y_ * rhs.x + z_ * rhs.w_;
//
//        return q;
//    }
//
//    Quaternion Quaternion::Normalized() {
//        float mag = sqrtf(w_ * w_ + x * x + y_ * y_ + z_ * z_);
//        return Quaternion(w_ / mag, x / mag, y_ / mag, z_ / mag);
//    }
//
//    Quaternion Quaternion::Conjugate() {
//        return Quaternion(w_, -x, -y_, -z_);
//    }
//
//    void Quaternion::Normalize() {
//        float mag = sqrtf(w_ * w_ + x * x + y_ * y_ + z_ * z_);
//
//        w_ /= mag;
//        x /= mag;
//        y_ /= mag;
//        z_ /= mag;
//    }
//
//    Vector3 Quaternion::operator*(Vector3& rhs) {
//        return Quaternion::ToMatrix(*this) * rhs;
//    }
//
//    const Vector3 operator*(Vector3& v, const Quaternion& m) {
//        return Quaternion::ToMatrix((Quaternion)m) * v;
//    }
//
//    Vector3 operator*(Vector3& v, Quaternion& m) {
//        return Quaternion::ToMatrix(m) * v;
//    }
//
//    const Vector3 Quaternion::operator*(const Vector3& rhs) {
//        return Quaternion::ToMatrix(*this) * rhs;
//    }
//
//    Quaternion Quaternion::AngleAxis(float angle, Vector3& axis) {
//        Vector3 vn = axis.Normalized();
//
//        angle *= 0.0174532925f; // To radians!
//        angle *= 0.5f;
//        float sinAngle = sin(angle);
//
//        return Quaternion(cos(angle), vn.x * sinAngle, vn.y * sinAngle, vn.z * sinAngle);
//    }
//
//    Quaternion Quaternion::Euler(float X, float Y, float Z) {
//        X *= 0.0174532925f; // To radians!
//        Y *= 0.0174532925f; // To radians!
//        Z *= 0.0174532925f; // To radians!
//
//        X *= 0.5f;
//        Y *= 0.5f;
//        Z *= 0.5f;
//
//        float sinx = sinf(X);
//        float siny = sinf(Y);
//        float sinz = sinf(Z);
//        float cosx = cosf(X);
//        float cosy = cosf(Y);
//        float cosz = cosf(Z);
//
//        Quaternion q;
//
//        q.w_ = cosx * cosy * cosz + sinx * siny * sinz;
//        q.x = sinx * cosy * cosz + cosx * siny * sinz;
//        q.y_ = cosx * siny * cosz - sinx * cosy * sinz;
//        q.z_ = cosx * cosy * sinz - sinx * siny * cosz;
//
//        return q;
//    }
//
//    void Quaternion::SetEuler(float X, float Y, float Z) {
//        X *= 0.0174532925f; // To radians!
//        Y *= 0.0174532925f; // To radians!
//        Z *= 0.0174532925f; // To radians!
//
//        X *= 0.5f;
//        Y *= 0.5f;
//        Z *= 0.5f;
//
//        float sinx = sinf(X);
//        float siny = sinf(Y);
//        float sinz = sinf(Z);
//        float cosx = cosf(X);
//        float cosy = cosf(Y);
//        float cosz = cosf(Z);
//
//        w_ = cosx * cosy * cosz + sinx * siny * sinz;
//        x = sinx * cosy * cosz + cosx * siny * sinz;
//        y_ = cosx * siny * cosz - sinx * cosy * sinz;
//        z_ = cosx * cosy * sinz - sinx * siny * cosz;
//    }
//
//    void Quaternion::ToAngleAxis(float* angle, Vector3* axis) {
//        *angle = acosf(w_);
//        float sinz = sinf(*angle);
//
//        if (fabsf(sinz) > 1e-4f) {
//            sinz = 1.0f / sinz;
//
//            axis->x = x * sinz;
//            axis->y = y_ * sinz;
//            axis->z = z_ * sinz;
//
//            *angle *= 2.0f * 57.2957795f;
//            if (*angle > 180.0f)
//                *angle = 360.0f - *angle;
//        }
//        else {
//            *angle = 0.0f;
//            axis->x = 1.0f;
//            axis->y = 0.0f;
//            axis->z = 0.0f;
//        }
//    }
//
//    Quaternion Quaternion::Inverse(Quaternion& rotation) {
//        return Quaternion(rotation.w_, -1.0f * rotation.x, -1.0f * rotation.y_, -1.0f * rotation.z_);
//    }
//
//    float Quaternion::Dot(Quaternion& a, Quaternion& b) {
//        return (a.w_ * b.w_ + a.x * b.x * a.y_ * b.y_ + a.z_ * b.z_);
//    }
//
//    float Quaternion::Dot(Quaternion& b) {
//        return (w_ * b.w_ + x * b.x * y_ * b.y_ + z_ * b.z_);
//    }
//
//    float Quaternion::Angle(Quaternion& a, Quaternion& b) {
//        float degrees = acosf((b * Quaternion::Inverse(a)).w_) * 2.0f * 57.2957795f;
//        if (degrees > 180.0f)
//            return 360.0f - degrees;
//        return degrees;
//    }
//
//    Quaternion operator*(float f, Quaternion& m) {
//        return Quaternion(m.w_ * f, m.x * f, m.y_ * f, m.z_ * f);
//    }
//
//    const Quaternion operator*(float f, const Quaternion& m) {
//        return Quaternion(m.w_ * f, m.x * f, m.y_ * f, m.z_ * f);
//    }
//
//    Quaternion Quaternion::operator*(float& f) {
//        return Quaternion(w_ * f, x * f, y_ * f, z_ * f);
//    }
//
//    const Quaternion Quaternion::operator*(const float& f) {
//        return Quaternion(w_ * f, x * f, y_ * f, z_ * f);
//    }
//
//    Quaternion Quaternion::operator+(Quaternion& rhs) {
//        return Quaternion(w_ + rhs.w_, x + rhs.x, y_ + rhs.y_, z_ + rhs.z_);
//    }
//
//    const Quaternion Quaternion::operator+(const Quaternion& rhs) {
//        return Quaternion(w_ + rhs.w_, x + rhs.x, y_ + rhs.y_, z_ + rhs.z_);
//    }
//
//    Quaternion Quaternion::Lerp(Quaternion& from, Quaternion& to, float t) {
//        Quaternion src = from * (1.0f - t);
//        Quaternion dst = to * t;
//
//        Quaternion q = src + dst;
//        return q;
//    }
//
//    Quaternion Quaternion::Slerp(Quaternion& from, Quaternion& to, float t) {
//        float cosTheta = Quaternion::Dot(from, to);
//        Quaternion temp(to);
//
//        if (cosTheta < 0.0f) {
//            cosTheta *= -1.0f;
//            temp = temp * -1.0f;
//        }
//
//        float theta = acosf(cosTheta);
//        float sinTheta = 1.0f / sinf(theta);
//
//        return sinTheta * (
//            ((Quaternion)(from * sinf(theta * (1.0f - t)))) +
//            ((Quaternion)(temp * sinf(t * theta)))
//            );
//    }
//
//#define m00 right.x
//#define m01 up.x
//#define m02 forward.x
//#define m10 right.y
//#define m11 up.y
//#define m12 forward.y
//#define m20 right.z
//#define m21 up.z
//#define m22 forward.z
//
//    Quaternion Quaternion::LookRotation(Vector3& lookAt, Vector3& upDirection) {
//        Vector3 forward = lookAt; Vector3 up = upDirection;
//        Vector3::OrthoNormalize(&forward, &up);
//        Vector3 right = Vector3::Cross(up, forward);
//
//        Quaternion ret;
//        ret.w_ = sqrtf(1.0f + m00 + m11 + m22) * 0.5f;
//        float w4_recip = 1.0f / (4.0f * ret.w_);
//        ret.x = (m21 - m12) * w4_recip;
//        ret.y_ = (m02 - m20) * w4_recip;
//        ret.z_ = (m10 - m01) * w4_recip;
//
//        return ret;
//    }
//
//    Quaternion Quaternion::LookRotation(Vector3& lookAt) {
//        Vector3 up = (Vector3)Vector3::up;
//        Vector3 forward = lookAt;
//        Vector3::OrthoNormalize(&forward, &up);
//        Vector3 right = Vector3::Cross(up, forward);
//
//        Quaternion ret;
//        ret.w_ = sqrtf(1.0f + m00 + m11 + m22) * 0.5f;
//        float w4_recip = 1.0f / (4.0f * ret.w_);
//        ret.x = (m21 - m12) * w4_recip;
//        ret.y_ = (m02 - m20) * w4_recip;
//        ret.z_ = (m10 - m01) * w4_recip;
//
//        return ret;
//    }
//
//    void Quaternion::SetLookRotation(Vector3& lookAt) {
//        Vector3 up = (Vector3)Vector3::up;
//        Vector3 forward = lookAt;
//        Vector3::OrthoNormalize(&forward, &up);
//        Vector3 right = Vector3::Cross(up, forward);
//
//        w_ = sqrtf(1.0f + m00 + m11 + m22) * 0.5f;
//        float w4_recip = 1.0f / (4.0f * w_);
//        x = (m21 - m12) * w4_recip;
//        y_ = (m02 - m20) * w4_recip;
//        z_ = (m10 - m01) * w4_recip;
//    }
//
//    void Quaternion::SetLookRotation(Vector3& lookAt, Vector3& upDirection) {
//        Vector3 forward = lookAt; Vector3 up = upDirection;
//        Vector3::OrthoNormalize(&forward, &up);
//        Vector3 right = Vector3::Cross(up, forward);
//
//        w_ = sqrtf(1.0f + m00 + m11 + m22) * 0.5f;
//        float w4_recip = 1.0f / (4.0f * w_);
//        x = (m21 - m12) * w4_recip;
//        y_ = (m02 - m20) * w4_recip;
//        z_ = (m10 - m01) * w4_recip;
//    }
//
//#undef m00
//#undef m01
//#undef m02
//#undef m10
//#undef m11
//#undef m12
//#undef m20
//#undef m21
//#undef m22
//} // cengine