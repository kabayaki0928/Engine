//#pragma once
//
//#include "vector3.h"
//
//namespace cengine
//{
//    class Quaternion {
//    public:
//        float x_;
//        float y_;
//        float z_;
//        float w_;
//    public:
//        Quaternion();
//        Quaternion(float x, float y, float z, float w);
//        Quaternion(const Quaternion& q);
//        ~Quaternion();
//        Quaternion& operator=(const Quaternion&);
//
//        bool operator==(Quaternion& rhs);
//        bool operator!=(Quaternion& rhs);
//
//        Quaternion& operator*=(Quaternion& rhs);
//        Quaternion& operator*=(const Quaternion& rhs);
//        Quaternion operator*(Quaternion& rhs);
//        const Quaternion operator*(const Quaternion& rhs);
//        Quaternion operator*(float& rhs);
//        const Quaternion operator*(const float& rhs);
//        Quaternion operator+(Quaternion& rhs);
//        const Quaternion operator+(const Quaternion& rhs);
//        Vector3 operator*(Vector3& rhs);
//        const Vector3 operator*(const Vector3& rhs);
//
//        Quaternion Normalized();
//        void Normalize();
//        Quaternion Conjugate(); // Same as inverse
//
//        void ToAngleAxis(float* angle, Vector3* axis);
//        void SetEuler(float X, float Y, float Z);
//        float Dot(Quaternion& b);
//        void SetLookRotation(Vector3& lookAt);
//        void SetLookRotation(Vector3& lookAt, Vector3& upDirection);
//
//        static Quaternion LookRotation(Vector3& lookAt);
//        static Quaternion LookRotation(Vector3& lookAt, Vector3& upDirection);
//        static Quaternion Slerp(Quaternion& from, Quaternion& to, float t);
//        static Quaternion Lerp(Quaternion& from, Quaternion& to, float t);
//        static float Angle(Quaternion& a, Quaternion& b);
//        static float Dot(Quaternion& a, Quaternion& b);
//        static Quaternion AngleAxis(float angle, Vector3& axis);
//        static Quaternion Inverse(Quaternion& rotation);
//        static Quaternion Euler(float X, float Y, float Z);
//        static Matrix ToMatrix(Quaternion& q);
//
//        static const Quaternion identity;
//    };
//
//    const Vector3 operator*(Vector3& v, const Quaternion& m);
//    Vector3 operator*(Vector& v, Quaternion& m);
//    Quaternion operator*(float f, Quaternion& m);
//    const Quaternion operator*(float f, const Quaternion& m);
//} // cengine