#pragma once

#include <iostream>

namespace cengine
{
    /// <summary>
    /// 3軸ベクトルを管理するクラス
    /// </summary>
    typedef struct Vector3 {
    private:
        float x_;
        float y_;
        float z_;
    public:
        static const Vector3 zero;
        static const Vector3 one;
        static const Vector3 up;
        static const Vector3 down;
        static const Vector3 right;
        static const Vector3 left;
        static const Vector3 forward;
        static const Vector3 back;

        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector3& v);

        inline float x() const noexcept { return x_; }
        inline float y() const noexcept { return y_; }
        inline float z() const noexcept { return z_; }
        inline float r() const noexcept { return x_; }
        inline float g() const noexcept { return y_; }
        inline float b() const noexcept { return z_; }

        inline bool operator==(const Vector3& v);
        inline bool operator!=(const Vector3& v);

        inline const Vector3& operator+() const noexcept { return *this; }
        inline Vector3 operator-()        const noexcept { return Vector3(-x_, -y_, -z_); }

        inline Vector3& operator+=(const Vector3 &v);
        inline Vector3& operator-=(const Vector3 &v);
        inline Vector3& operator*=(const Vector3 &v);
        inline Vector3& operator/=(const Vector3 &v);
        inline Vector3& operator*=(const float t);
        inline Vector3& operator/=(const float t);

        inline std::istream& getInStream(std::istream& istream);
        inline std::ostream& getOutStream(std::ostream& ostream);

        inline Vector3 operator*(float t);

        inline float length() const noexcept;
        inline float squaredLength() const noexcept;
        inline void makeUnitVector() noexcept;
    } Vector3;

} // cengine