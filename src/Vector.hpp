#pragma once
#ifndef RAYLIB_PLUSPLUS_VECTORS
#define RAYLIB_PLUSPLUS_VECTORS
#include "./RaylibExtern.hpp"

namespace raylib {
    namespace cpp {
        class RayMath {
        public:
            static float Clamp(float value, float min, float max) {
                return ::Clamp(value, min, max);
            }

            static float Lerp(float v1, float v2, float amount) {
                return ::Lerp(v1, v2, amount);
            }

            static float Normalize(float value, float lo, float hi) {
                return ::Normalize(value, lo, hi);
            }

            static float Remap(float value, float inStart, float inEnd, float outStart, float outEnd) {
                return ::Remap(value, inStart, inEnd, outStart, outEnd);
            }
        };

        class Vector2D {
        private:
            inline Vector2D& Clone(::Vector2 v) {
                x = v.x, y = v.y;
                return (*this);
            }
        public:
            float x, y;

            Vector2D() { x = 0.0f, y = 0.0f; }
            Vector2D(float x, float y) { this->x = x, this->y = y; }
            Vector2D(Vector2 vec) { x = vec.x, y = vec.y; }
            operator Vector2() const { return { x, y }; };

            static Vector2D Vector2Zero() { return ::Vector2Zero(); }
            Vector2D& Zero() {
                return Clone(::Vector2Zero());
            }

            static Vector2D Vector2One() { return ::Vector2One(); }
            Vector2D& One() {
                return Clone(::Vector2One());
            }

            Vector2D& Add(Vector2D v) {
                return Clone(::Vector2Add(*this, v));
            }

            Vector2D& AddValue(float value) {
                return Clone(::Vector2AddValue(*this, value));
            }

            Vector2D& Subtract(Vector2D v) {
                return Clone(::Vector2Subtract(*this, v));
            }

            Vector2D& SubtractValue(float value) {
                return Clone(::Vector2SubtractValue(*this, value));
            }

            Vector2D& Multiply(Vector2D v) {
                return Clone(::Vector2Multiply(*this, v));
            }

            float Length() {
                return ::Vector2Length(*this);
            }

            float LengthSqr() {
                return ::Vector2LengthSqr(*this);
            }

            float DotProduct(Vector2D v) {
                return ::Vector2DotProduct(*this, v);
            }

            float Distance(Vector2D v) {
                return ::Vector2Distance(*this, v);
            }

            float DistanceSqr(Vector2D v) {
                return ::Vector2DistanceSqr(*this, v);
            }

            float Angle(Vector2D v) {
                return ::Vector2Angle(*this, v);
            }

            Vector2D& Negate(Vector2D v) {
                return Clone(::Vector2Negate(*this));
            }

            Vector2D& Divide(Vector2D v) {
                return Clone(::Vector2Divide(*this, v));
            }

            Vector2D& Normalize() {
                return Clone(::Vector2Normalize(*this));
            }

            Vector2D& Transform(Vector2D v) {
                return Clone(::Vector2Normalize(*this));
            }

            Vector2D& Lerp(Vector2D v, float amount) {
                return Clone(::Vector2Lerp(*this, v, amount));
            }

            Vector2D& Reflect(Vector2D v) {
                return Clone(::Vector2Reflect(*this, v));
            }

            Vector2D& Rotate(float angle) {
                return Clone(::Vector2Rotate(*this, angle));
            }

            Vector2D& MoveTowards(Vector2D v, float maxDist) {
                return Clone(::Vector2MoveTowards(*this, v, maxDist));
            }
        };

        class Vector3D : public Vector2D {
        private:
            inline Vector3D& Clone(::Vector3 v) {
                x = v.x, y = v.y, z = v.z;
                return (*this);
            }
        public:
            float z;

            Vector3D() : Vector2D() { z = 0.0f; }
            Vector3D(float x, float y, float z) : Vector2D(x, y) { this->z = z; }
            Vector3D(Vector3 vec) { x = vec.x, y = vec.y, z = vec.z; }
            operator Vector3() const { return { x, y, z }; };

            static Vector3D Vector3Zero() { return ::Vector3Zero(); }
            Vector3D& Zero() {
                return Clone(::Vector3Zero());
            }

            static Vector3D Vector3One() { return ::Vector3One(); }
            Vector3D& One() {
                return Clone(::Vector3One());
            }

            Vector3D& Add(Vector3D v) {
                return Clone(::Vector3Add(*this, v));
            }

            Vector3D& AddValue(float value) {
                return Clone(::Vector3AddValue(*this, value));
            }

            Vector3D& Subtract(Vector3D v) {
                return Clone(::Vector3Subtract(*this, v));
            }

            Vector3D& SubtractValue(float value) {
                return Clone(::Vector3SubtractValue(*this, value));
            }

            Vector3D& Multiply(Vector3D v) {
                return Clone(::Vector3Multiply(*this, v));
            }

            Vector3D& CrossProduct(Vector3D v) {
                return Clone(::Vector3CrossProduct(*this, v));
            }

            Vector3D Perpendicular() {
                return ::Vector3Perpendicular(*this);
            }

            float Length() {
                return ::Vector3Length(*this);
            }

            float LengthSqr() {
                return ::Vector3LengthSqr(*this);
            }

            float DotProduct(Vector3D v) {
                return ::Vector3DotProduct(*this, v);
            }

            float Distance(Vector3D v) {
                return ::Vector3Distance(*this, v);
            }

            float DistanceSqr(Vector3D v) {
                return ::Vector3DistanceSqr(*this, v);
            }

            float Angle(Vector3D v) {
                return ::Vector3Angle(*this, v);
            }

            Vector3D& Negate(Vector3D v) {
                return Clone(::Vector3Negate(*this));
            }

            Vector3D& Divide(Vector3D v) {
                return Clone(::Vector3Divide(*this, v));
            }

            Vector3D& Normalize() {
                return Clone(::Vector3Normalize(*this));
            }

            static void OrthoNormalize(Vector3D v1, Vector3D v2) {
                Vector3 vv1 = v1, vv2 = v2;
                ::Vector3OrthoNormalize(&vv1, &vv2);
                v1.Clone(vv1);
                v2.Clone(vv2);
            }

            Vector3D OrthoNormalize(Vector3D v) {
                Vector3 v1 = *this, v2 = v;
                ::Vector3OrthoNormalize(&v1, &v2);
                this->Clone(v1);
                v.Clone(v2);
            }

            Vector3D& Transform(Matrix m) {
                return Clone(::Vector3Transform(*this, m));
            }

            Vector3D& RotateByQuaternion(Quaternion q) {
                return Clone(::Vector3RotateByQuaternion(*this, q));
            }

            Quaternion QuaternionFromVector3ToVector3(Vector3D v) {
                return ::QuaternionFromVector3ToVector3(*this, v);
            }

            Vector3D& Lerp(Vector3D v, float amount) {
                return Clone(::Vector3Lerp(*this, v, amount));
            }

            Vector3D& Reflect(Vector3D normal) {
                return Clone(::Vector3Reflect(*this, normal));
            }

            Vector3D& Min(Vector3D v) {
                return Clone(::Vector3Min(*this, v));
            }

            Vector3D& Max(Vector3D v) {
                return Clone(::Vector3Max(*this, v));
            }

            static Vector3D BaryCenter(Vector3D p, Vector3D a, Vector3D b, Vector3D c) {
                return ::Vector3Barycenter(p, a, b, c);
            }
            Vector3D& BaryCenter(Vector3D a, Vector3D b, Vector3D c) {
                return Clone(::Vector3Barycenter(*this, a, b, c));
            }

            Vector3D& Unproejct(Matrix projection, Matrix view) {
                return Clone(::Vector3Unproject(*this, projection, view));
            }

            float3 ToFloatV() {
                return ::Vector3ToFloatV(*this);
            }
        };

        class Vector4D : public Vector3D {
        public:
            float w;

            Vector4D() : Vector3D() { w = 0.0f; }
            Vector4D(float x, float y, float z, float w) : Vector3D(x, y, z) { this->w = w; }
            Vector4D(Vector4 vec) { x = vec.x, y = vec.y, z = vec.z, w = vec.w; }
            operator Vector4() const { return { x, y, z, w }; };
        };

        class Quaternion : public Vector4D {
        private:
            inline Quaternion& Clone(::Quaternion q) {
                x = q.x, y = q.y, z = q.z, w = q.w;
                return (*this);
            }
        public:
            Quaternion(float x, float y, float z, float w) : Vector4D(x, y, z, w) {}
            Quaternion(::Quaternion q) { x = q.x, y = q.y, z = q.z, w = q.w; }
            operator ::Quaternion() const { return { x, y, z, w }; };

            Quaternion& Add(Quaternion q) {
                return Clone(::QuaternionAdd(*this, q));
            }

            Quaternion& AddValue(float value) {
                return Clone(::QuaternionAddValue(*this, value));
            }

            Quaternion& Subtract(Quaternion q) {
                return Clone(::QuaternionSubtract(*this, q));
            }

            Quaternion& SubtractValue(float value) {
                return Clone(::QuaternionSubtractValue(*this, value));
            }

            static Quaternion QuaternionIdentity() { return ::QuaternionIdentity(); }
            Quaternion& Identity() {
                return Clone(::QuaternionIdentity());
            }

            float Length() { return ::QuaternionLength(*this); }

            Quaternion& Normalize() {
                return Clone(::QuaternionNormalize(*this));
            }

            Quaternion& Invert() {
                return Clone(::QuaternionInvert(*this));
            }

            Quaternion& Multiply(Quaternion q) {
                return Clone(::QuaternionMultiply(*this, q));
            }

            Quaternion& Scale(float scale) {
                return Clone(::QuaternionScale(*this, scale));
            }

            Quaternion& Divide(Quaternion q) {
                return Clone(::QuaternionDivide(*this, q));
            }

            Quaternion& Lerp(Quaternion q, float amount) {
                return Clone(::QuaternionLerp(*this, q, amount));
            }

            Quaternion& Slerp(Quaternion q, float amount) {
                return Clone(::QuaternionSlerp(*this, q, amount));
            }

            static Quaternion QuaternionFromVector3toVector3(Vector3D vA, Vector3D vB) { return ::QuaternionFromVector3ToVector3(vA, vB); }
            Quaternion& FromVector3ToVector3(Vector3D vA, Vector3D vB) {
                return Clone(::QuaternionFromVector3ToVector3(vA, vB));
            }

            static Quaternion QuaternionFromMatrix(Matrix m) { return ::QuaternionFromMatrix(m); }
            Quaternion& FromMatrix(Matrix m) {
                return Clone(::QuaternionFromMatrix(m));
            }

            Matrix ToMatrix() {
                return ::QuaternionToMatrix(*this);
            }

            Vector4D ToAxisAngle() {
                Vector3 v;
                float angle;

                ::QuaternionToAxisAngle(*this, &v, &angle);
                return Vector4D(v.x, v.y, v.z, angle);
            }

            Quaternion& FromEuler(float pitch, float yaw, float roll) {
                return Clone(::QuaternionFromEuler(pitch, yaw, roll));
            }

            Vector3D ToEuler() {
                return ::QuaternionToEuler(*this);
            }

            Quaternion& Transform(Matrix m) {
                return Clone(::QuaternionTransform(*this, m));
            }
        };

        class Matrix {
        private:
            inline Matrix& Clone(::Matrix m) {
                m0 = m.m0; m.m4 = m.m4; m.m8 = m8; m12 = m.m12;
                m1 = m.m1; m.m5 = m.m5; m.m9 = m9; m13 = m.m13;
                m2 = m.m2; m.m6 = m.m6; m.m10 = m.m10; m14 = m.m14;
                m3 = m.m3; m.m7 = m.m7; m.m11 = m.m11; m15 = m.m15;
                return (*this);
            }

        public:
            float m0, m4, m8, m12;
            float m1, m5, m9, m13;
            float m2, m6, m10, m14;
            float m3, m7, m11, m15;

            Matrix() {
                m0 = 0.0; m4 = 0.0; m8 = 0.0; m12 = 0.0;
                m1 = 0.0; m5 = 0.0; m9 = 0.0; m13 = 0.0;
                m2 = 0.0; m6 = 0.0; m10 = 0.0; m14 = 0.0;
                m3 = 0.0; m7 = 0.0; m11 = 0.0; m15 = 0.0;
            }

            Matrix(float m0 = 0.0, float m4 = 0.0, float m8 = 0.0, float m12 = 0.0,
            float m1 = 0.0, float m5 = 0.0, float m9 = 0.0, float m13 = 0.0,
            float m2 = 0.0, float m6 = 0.0, float m10 = 0.0, float m14 = 0.0,
            float m3 = 0.0, float m7 = 0.0, float m11 = 0.0, float m15 = 0.0) {
                this->m0 = m0; this->m4 = m4; this->m8 = m8; this->m12 = m12;
                this->m1 = m1; this->m5 = m5; this->m9 = m9; this->m13 = m13;
                this->m2 = m2; this->m6 = m6; this->m10 = m10; this->m14 = m14;
                this->m3 = m3; this->m7 = m7; this->m11 = m11; this->m15 = m15;
            }

            Matrix(::Matrix m) {
                m0 = m.m0; m4 = m.m4; m8 = m.m8; m12 = m.m12;
                m1 = m.m1; m5 = m.m5; m9 = m.m9; m13 = m.m13;
                m2 = m.m2; m6 = m.m6; m10 = m.m10; m14 = m.m14;
                m3 = m.m3; m7 = m.m7; m11 = m.m11; m15 = m.m15;
            }

            operator ::Matrix() {
                return {
                    m0, m4, m8, m12,
                    m1, m5, m9, m13,
                    m2, m6, m10, m14,
                    m3, m7, m11, m15
                };
            }

            float Determinant() {
                return ::MatrixDeterminant(*this);
            }

            float Trace() {
                return ::MatrixTrace(*this);
            }

            Matrix& Transpose() {
                return Clone(::MatrixTranspose(*this));
            }

            Matrix& Invert() {
                return Clone(::MatrixInvert(*this));
            }

            Matrix& Normalize() {
                return Clone(::MatrixNormalize(*this));
            }

            static Matrix MatrixIdentity() { return ::MatrixIdentity(); }
            Matrix& Identity() {
                return Clone(::MatrixIdentity());
            }

            Matrix& Subtract(Matrix m) {
                return Clone(::MatrixSubtract(*this, m));
            }

            Matrix& Multiply(Matrix m) {
                return Clone(::MatrixMultiply(*this, m));
            }

            static Matrix Translate(Vector3D v) { return ::MatrixTranslate(v.x, v.y, v.z); }
            static Matrix Translate(float x, float y, float z) {
                return ::MatrixTranslate(x, y, z);
            }

            static Matrix Rotate(Vector4D v) { return ::MatrixRotate(v, v.w); }
            static Matrix Rotate(Vector3D v, float angle) {
                return ::MatrixRotate(v, angle);
            }

            static Matrix RotateX(float angle) {
                return ::MatrixRotateX(angle);
            }
            
            static Matrix RotateY(float angle) {
                return ::MatrixRotateY(angle);
            }

            static Matrix RotateZ(float angle) {
                return ::MatrixRotateY(angle);
            }

            static Matrix RotateXYZ(Vector3D angle) {
                return ::MatrixRotateXYZ(angle);
            }

            static Matrix RotateZYX(Vector3D angle) {
                return ::MatrixRotateZYX(angle);
            }

            static Matrix Scale(Vector3D v) { return ::MatrixScale(v.x, v.y, v.z); }
            static Matrix Scale(float x, float y, float z) {
                return ::MatrixScale(x, y, z);
            }

            static Matrix Frustum(double left, double right, double bottom, double top, double near, double far) {
                return ::MatrixFrustum(left, right, bottom, top, near, far);
            }

            static Matrix Perspective(double fovy, double aspect, double near, double far) {
                return ::MatrixPerspective(fovy, aspect, near, far);
            }

            static Matrix OrthoProjection(double left, double right, double bottom, double top, double near, double far) {
                return ::MatrixOrtho(left, right, bottom, top, near, far);
            }

            static Matrix LookAt(Vector3D eye, Vector3D target, Vector3D up) {
                return ::MatrixLookAt(eye, target, up);
            }

            float16 ToFloatV() {
                return ::MatrixToFloatV(*this);
            }

            static Matrix MatrixFromQuaternion(Quaternion q) { return ::QuaternionToMatrix(q); }
            inline Matrix& FromQuaternion(Quaternion q) {
                return Clone(::QuaternionToMatrix(q));
            }

            Quaternion ToQuaternion() {
                return ::QuaternionFromMatrix(*this);
            }
        };
    }
}
#endif
