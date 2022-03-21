#pragma once
#ifndef RAYLIB_PLUSPLUS_COLORS
#define RAYLIB_PLUSPLUS_COLORS
#include "./RaylibExtern.hpp"
#include "./Vector.hpp"

namespace raylib {
    namespace cpp {
        typedef unsigned char byte;

        class ColorVector : public Vector4D {
        public:
            ColorVector(Vector3D vec) { Set(vec); }
            ColorVector(Vector4D vec) { Set(vec); }
            ColorVector(float x, float y, float z, float w) { Set(x, y, z, w); }

            operator Vector3D() { return { x, y, z }; };
            operator Vector4D() { return { x, y, z, w }; };
            
            void Set(Vector3D vec) { x = vec.x, y = vec.y, z = vec.z, w = 1.0f; }
            void Set(Vector4D vec) { x = vec.x, y = vec.y, z = vec.z, w = vec.w; }
            void Set(float x, float y, float z, float w = 1.0f) { this->x = x, this->y = y, this->z = z, this->w = w; }
        };

        class Colors {
        public:
            byte r, g, b, a;
            Colors() { r = 0x00, g = 0x00, b = 0x00, a = 0xFF; }
            Colors(byte r, byte g, byte b, byte a) { Set(r, g, b, a); }
            Colors(unsigned int color) { Set(color); }
            Colors(Color color) { Set(color); }
            
            operator int() const { return (r) & (g << 0x8) & (b << 0x10) & (a << 0x18); };
            operator Color() const { return { r, g, b, a }; };

            void Set(byte r, byte g, byte b, byte a) { this->r = r, this->b = b, this->g = g, this->a = a; }
            void Set(int color) { r = color & 0x000000FFU, g = color & 0x0000FF00U, b = color & 0x00FF0000U, a = color & 0xFF000000U; }
            void Set(Color color) { r = color.r, g = color.g, b = color.b, a = color.a; }
            void Set(float h, float s, float v) { Set(::ColorFromHSV(h, s, v)); }

            void Fade(float alpha) { Set(::Fade(*this, alpha)); }
            void Alpha(float alpha) { Set(::ColorAlpha(*this, alpha)); }
            void Blend(Colors dest, Colors tint) { Set(::ColorAlphaBlend(dest, *this, tint)); }

            ColorVector ToNormal() { return Vector4D(::ColorNormalize(*this)); }
            void FromNormal(ColorVector normal) { Set(::ColorFromNormalized({ normal.x, normal.y, normal.z, normal.w })); }
            ColorVector ToHsv() { Vector3 vec3 = ::ColorToHSV(*this); return ColorVector(vec3.x, vec3.y, vec3.z, (float)a / 255.0f); }
            void FromHsv(ColorVector color) { Set(::ColorFromHSV(color.x, color.y, color.z)); }

            static Colors GetPixel(void* srcPtr, int format) { return static_cast<Colors>(::GetPixelColor(srcPtr, format)); }
            static void SetPixel(void* dstPtr, Colors color, int format) { ::SetPixelColor(dstPtr, color, format); }
            static int GetPixelDataSize(int width, int height, PixelFormat format) { return ::GetPixelDataSize(width, height, format); }

            #pragma region PREDEFINED_RAYLIB_COLORS
            inline static Colors LightGray() { return LIGHTGRAY; }
            inline static Colors Gray() { return GRAY; }
            inline static Colors DarkGray() { return DARKGRAY; }
            inline static Colors Yellow() { return YELLOW; }
            inline static Colors Gold() { return GOLD; }
            inline static Colors Orange() { return ORANGE; }
            inline static Colors Pink() { return PINK; }
            inline static Colors Red() { return RED; }
            inline static Colors Maroon() { return MAROON; }
            inline static Colors Green() { return GREEN; }
            inline static Colors Lime() { return LIME; }
            inline static Colors DarkGreen() { return DARKGREEN; }
            inline static Colors SkyBlue() { return SKYBLUE; }
            inline static Colors Blue() { return BLUE; }
            inline static Colors DarkBlue() { return DARKBLUE; }
            inline static Colors Purple() { return PURPLE; }
            inline static Colors Violet() { return VIOLET; }
            inline static Colors DarkPurple() { return DARKPURPLE; }
            inline static Colors Beige() { return BEIGE; }
            inline static Colors Brown() { return BROWN; }
            inline static Colors DarkBrown() { return DARKBROWN; }
            inline static Colors White() { return WHITE; }
            inline static Colors Black() { return BLACK; }
            inline static Colors Blank() { return BLANK; }
            inline static Colors Magenta() { return MAGENTA; }
            inline static Colors RayWhite() { return RAYWHITE; }
            #pragma endregion PREDEFINED_RAYLIB_COLORS
        };
    }
}
	
#endif
