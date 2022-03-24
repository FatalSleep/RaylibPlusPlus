#pragma once
#ifndef RAYLIB_PLUSPLUS_TEXTURES
#define RAYLIB_PLUSPLUS_TEXTURES
#include "./RaylibExtern.hpp"
#include "./Colors.hpp"
#include "./Vector.hpp"
#include <exception>
#include <vector>
#include <numeric>

namespace raylib {
    namespace cpp {
        class Rectangle {
        public:
            float x, y, w, h;

            Rectangle() { x = 0, y = 0, w = 0, h = 0; }
            Rectangle(::Rectangle rect) { x = rect.x, y = rect.y, w = rect.width, h = rect.height; }
            Rectangle(float x, float y, float w, float h) {
                this->x = x; this->y = y; this->w = w; this->h = h;
            }

            operator ::Rectangle() { return { x, y, w, h }; }
        };

        class Image {
        private:
            bool isLoaded;

            inline Image& Clone(::Image img) {
                data = img.data;
                w = img.width, h = img.height;
                mipmaps = img.mipmaps, format = img.format;
                return (*this);
            }

            inline void ThrowException(const char* message) {
                throw std::exception(message);
            }
        public:
            void* data;
            int w, h, mipmaps, format;

            Image() { data = nullptr, w = 0, h = 0, mipmaps = 0, format = 0; isLoaded = false; }
            Image(::Image image) {
                data = image.data; w = image.width, h = image.height;
                mipmaps = image.mipmaps, format = image.format;
                isLoaded = false;
            }
            Image(void* ptr, int w, int h, int mipmaps, int format) {
                this->data = ptr; this->w = w; this->h = h;
                this->mipmaps = mipmaps, this->format = format;
                this->isLoaded = true;
            }

            operator ::Image() { return { data, w, h, mipmaps, format }; }

            bool IsLoaded() { return isLoaded; }

            Image& Load(const char* fileName) {
                return Clone(::LoadImage(fileName));
            }

            Image& LoadRaw(const char* fileName, int width, int height, int format, int headerSize) {
                return Clone(::LoadImageRaw(fileName, width, height, format, headerSize));
            }

            Image& LoadAnim(const char* fileName, int* frames) {
                return Clone(::LoadImageAnim(fileName, frames));
            }

            Image& LoadFromMemory(const char* fileType, const unsigned char* fileData, int dataSize) {
                return Clone(::LoadImageFromMemory(fileType, fileData, dataSize));
            }

            Image& LoadFromTexture(Texture2D texture) {
                return Clone(::LoadImageFromTexture(texture));
            }

            Image& LoadFromScreen(void) {
                return Clone(::LoadImageFromScreen());
            }

            Image& Unload() {
                ::UnloadImage(*this);
                isLoaded = false;
                return (*this);
            }

            bool Export(const char* fileName) {
                return ::ExportImage(*this, fileName);
            }

            bool ExportAsCode(const char* fileName) {
                return ::ExportImageAsCode(*this, fileName);
            }

            Image& GenImageFromColor(int width, int height, Colors color) {
                return Clone(::GenImageColor(width, height, color));
            }

            Image& GenImageFromGradientV(int width, int height, Colors top, Colors bottom) {
                return Clone(::GenImageGradientV(width, height, top, bottom));
            }

            Image& GenImageFromGradientH(int width, int height, Colors top, Colors bottom) {
                return Clone(::GenImageGradientH(width, height, top, bottom));
            }

            Image& GenImageFromGradientR(int width, int height, float density, Colors inner, Colors outer) {
                return Clone(::GenImageGradientRadial(width, height, density, inner, outer));
            }

            Image& GenImageChecked(int width, int height, int checksX, int checksY, Colors col1, Colors col2) {
                return Clone(::GenImageChecked(width, height, checksX, checksY, col1, col2));
            }

            Image& GenImageWhiteNoise(int width, int height, float factor) {
                return Clone(::GenImageWhiteNoise(width, height, factor));
            }

            Image& GenImageCellular(int width, int height, int tileSize) {
                return Clone(::GenImageCellular(width, height, tileSize));
            }
            
            Image& Copy(Image image) {
                return Clone(::ImageCopy(image));
            }

            Image& FromImage(Image image, Rectangle rec) {
                return Clone(::ImageFromImage(image, rec));
            }

            Image& FromText(const char* text, int fontSize, Colors color) {
                return Clone(::ImageText(text, fontSize, color));
            }

            Image& TextEx(Font font, const char* text, float fontSize, float spacing, Colors tint) {
                return Clone(::ImageTextEx(font, text, fontSize, spacing, tint));
            }

            Image& Format(int newFormat) {
                ::Image img = (*this);
                ::ImageFormat(&img, newFormat);
                return Clone(img);
            }

            Image& ToPOT(Colors fill) {
                ::Image img = (*this);
                ::ImageToPOT(&img, fill);
                return Clone(img);
            }

            Image& Crop(Rectangle crop) {
                ::Image img = (*this);
                ::ImageCrop(&img, crop);
                return Clone(img);
            }

            Image& AlphaCrop(float threshold) {
                ::Image img = (*this);
                ::ImageAlphaCrop(&img, threshold);
                return Clone(img);
            }

            Image& AlphaClear(Colors color, float threshold) {
                ::Image img = (*this);
                ::ImageAlphaClear(&img, color, threshold);
                return Clone(img);
            }

            Image& AlphaMask(Image alphaMask) {
                ::Image img = (*this);
                ::ImageAlphaMask(&img, alphaMask);
                return Clone(img);
            }

            Image& AlphaPremultiply() {
                ::Image img = (*this);
                ::ImageAlphaPremultiply(&img);
                return Clone(img);
            }

            Image& Resize(int newWidth, int newHeight) {
                ::Image img = (*this);
                ::ImageResize(&img, newWidth, newHeight);
                return Clone(img);
            }

            Image& ResizeNN(int newWidth, int newHeight) {
                ::Image img = (*this);
                ::ImageResizeNN(&img, newWidth, newHeight);
                return Clone(img);
            }

            Image& ResizeCanvas(int newWidth, int newHeight, int offsetX, int offsetY, Colors fill) {
                ::Image img = (*this);
                ::ImageResizeCanvas(&img, newWidth, newHeight, offsetX, offsetY, fill);
                return Clone(img);
            }

            Image& Mipmaps() {
                ::Image img = (*this);
                ::ImageMipmaps(&img);
                return Clone(img);
            }

            Image& Dither(int rBpp, int gBpp, int bBpp, int aBpp) {
                ::Image img = (*this);
                ::ImageDither(&img, rBpp, gBpp, bBpp, aBpp);
                return Clone(img);
            }

            Image& FlipVertical() {
                ::Image img = (*this);
                ::ImageFlipVertical(&img);
                return Clone(img);
            }

            Image& FlipHorizontal() {
                ::Image img = (*this);
                ::ImageFlipHorizontal(&img);
                return Clone(img);
            }

            Image& RotateCW() {
                ::Image img = (*this);
                ::ImageRotateCW(&img);
                return Clone(img);
            }

            Image& RotateCCW() {
                ::Image img = (*this);
                ::ImageRotateCCW(&img);
                return Clone(img);
            }

            Image& ColorTint(Colors color) {
                ::Image img = (*this);
                ::ImageColorTint(&img, color);
                return Clone(img);
            }

            Image& ColorInvert() {
                ::Image img = (*this);
                ::ImageColorInvert(&img);
                return Clone(img);
            }

            Image& ColorGrayscale() {
                ::Image img = (*this);
                ::ImageColorGrayscale(&img);
                return Clone(img);
            }

            Image& ColorContrast(float contrast) {
                ::Image img = (*this);
                ::ImageColorContrast(&img, contrast);
                return Clone(img);
            }

            Image& ColorBrightness(int brightness) {
                ::Image img = (*this);
                ::ImageColorBrightness(&img, brightness);
                return Clone(img);
            }

            Image& ColorReplace(Colors color, Colors replace) {
                ::Image img = (*this);
                ::ImageColorReplace(&img, color, replace);
                return Clone(img);
            }

            std::vector<Colors> LoadColors() {
                Color* colors = ::LoadImageColors(*this);
                std::vector<Colors> cols;
                
                for (int i = 0; i < (w * h); i++)
                    cols.push_back(*(colors + i));

                ::UnloadImageColors(colors);
                return cols;
            }

            std::vector<Colors> LoadPalette(int maxPaletteSize) {
                int colorsCount = 0;
                Color* colors = ::LoadImagePalette(*this, maxPaletteSize, &colorsCount);
                std::vector<Colors> cols;

                for (int i = 0; i < (w * h); i++)
                    cols.push_back(*(colors + i));

                ::UnloadImagePalette(colors);
                return cols;
            }

            Rectangle GetAlphaBorder(float threshold) {
                return ::GetImageAlphaBorder(*this, threshold);
            }

            Colors GetColor(int x, int y) {
                return ::GetImageColor(*this, x, y);
            }

            Image& ClearBackground(Colors color) {
                ::Image img = *this;
                ::ImageClearBackground(&img, color);
                return (*this);
            }

            Image& DrawPixel(int posX, int posY, Colors color) {
                ::Image img = *this;
                ::ImageDrawPixel(&img, posX, posY, color);
                return (*this);
            }
            
            Image& DrawPixelV(Vector2D position, Colors color) {
                ::Image img = *this;
                ::ImageDrawPixelV(&img, position, color);
                return (*this);
            }
            
            Image& DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Colors color) {
                ::Image img = *this;
                ::ImageDrawLine(&img, startPosX, startPosY, endPosX, endPosY, color);
                return (*this);
            }
            
            Image& DrawLineV(Vector2D start, Vector2D end, Colors color) {
                ::Image img = *this;
                ::ImageDrawLineV(&img, start, end, color);
                return (*this);
            }
            
            Image& DrawCircle(int centerX, int centerY, int radius, Colors color) {
                ::Image img = *this;
                ::ImageDrawCircle(&img, centerX, centerY, radius, color);
                return (*this);
            }

            Image& DrawCircleV(Vector2D center, int radius, Colors color) {
                ::Image img = *this;
                ::ImageDrawCircleV(&img, center, radius, color);
                return (*this);
            }

            Image& DrawRectangle(int posX, int posY, int width, int height, Colors color) {
                ::Image img = *this;
                ::ImageDrawRectangle(&img, posX, posY, width, height, color);
                return (*this);
            }

            Image& DrawRectangleV(Vector2D position, Vector2D size, Colors color) {
                ::Image img = *this;
                ::ImageDrawRectangleV(&img, position, size, color);
                return (*this);
            }

            Image& DrawRectangleRec(Rectangle rec, Colors color) {
                ::Image img = *this;
                ::ImageDrawRectangleRec(&img, rec, color);
                return (*this);
            }

            Image& DrawRectangleLines(Rectangle rec, int thick, Colors color) {
                ::Image img = *this;
                ::ImageDrawRectangleLines(&img, rec, thick, color);
                return (*this);
            }

            Image& Draw(Image src, Rectangle srcRec, Rectangle dstRec, Colors tint) {
                ::Image img = *this;
                ::ImageDraw(&img, src, srcRec, dstRec, tint);
                return (*this);
            }

            Image& DrawText(const char* text, int posX, int posY, int fontSize, Colors color) {
                ::Image img = *this;
                ::ImageDrawText(&img, text, posX, posY, fontSize, color);
                return (*this);
            }

            Image& DrawTextEx(Font font, const char* text, Vector2D position, float fontSize, float spacing, Colors tint) {
                ::Image img = *this;
                ::ImageDrawTextEx(&img, font, text, position, fontSize, spacing, tint);
                return (*this);
            }

            Texture LoadTextureCubemap(int layout) {
                return Texture(::LoadTextureCubemap(*this, layout));
            }
        };

        class Texture {
        private:
            bool isLoaded;

            inline Texture& Clone(::Texture tex) {
                id = tex.id;
                w = tex.width, h = tex.height;
                mipmaps = tex.mipmaps, format = tex.format;
                return (*this);
            }
        public:
            unsigned int id;
            int w, h, mipmaps, format;

            Texture() {
                id = 0;
                w = 0, h = 0, mipmaps = 0, format = 0;
                this->isLoaded = false;
            }
            Texture(::Texture text) {
                id = text.id; w = text.width, h = text.height;
                mipmaps = text.mipmaps, format = text.format;
                this->isLoaded = true;
            }
            Texture(unsigned int id, int w, int h, int mipmaps, int format) {
                this->id = id;
                this->w = w, this->h = h;
                this->mipmaps = mipmaps, this->format = format;
                this->isLoaded = true;
            }

            operator ::Texture() { return { id, w, h, mipmaps, format }; }

            bool IsLoaded() { return isLoaded; }

            Texture& Unload() {
                ::UnloadTexture(*this);
                return (*this);
            }

            Texture& Load(const char* fileName) {
                return Clone(::LoadTexture(fileName));
            }

            Texture& LoadFromImage(Image image) {
                return Clone(::LoadTextureFromImage(image));
            }

            Texture& GenMipmaps() {
                ::Texture tex = *this;
                ::GenTextureMipmaps(&tex);
                return (*this);
            }

            Texture& SetFilter(int filter) {
                ::SetTextureFilter(*this, filter);
                return (*this);
            }

            Texture& SetWrap(int wrap) {
                ::SetTextureWrap(*this, wrap);
                return (*this);
            }

            Texture& Draw(Texture2D texture, int posX, int posY, Color tint) {
                ::DrawTexture(*this, posX, posY, tint);
                return (*this);
            }

            Texture& DrawV(Vector2D position, Color tint) {
                ::DrawTextureV(*this, position, tint);
                return (*this);
            }

            Texture& DrawEx(Vector2D position, float rotation, float scale, Color tint) {
                ::DrawTextureEx(*this, position, rotation, scale, tint);
                return (*this);
            }
            
            Texture& DrawRec(Rectangle source, Vector2D position, Color tint) {
                ::DrawTextureRec(*this, source, position, tint);
                return (*this);
            }
            
            Texture& DrawQuad(Vector2D tiling, Vector2D offset, Rectangle quad, Color tint) {
                ::DrawTextureQuad(*this, tiling, offset, quad, tint);
                return (*this);
            }
            
            Texture& DrawTiled(Rectangle source, Rectangle dest, Vector2D origin, float rotation, float scale, Color tint) {
                ::DrawTextureTiled(*this, source, dest, origin, rotation, scale, tint);
                return (*this);
            }
            
            Texture& DrawPro(Rectangle source, Rectangle dest, Vector2D origin, float rotation, Color tint) {
                ::DrawTexturePro(*this, source, dest, origin, rotation, tint);
                return (*this);
            }
            
            Texture& DrawTextureNPatch(NPatchInfo nPatchInfo, Rectangle dest, Vector2D origin, float rotation, Color tint) {
                ::DrawTextureNPatch(*this, nPatchInfo, dest, origin, rotation, tint);
                return (*this);
            }
            
            Texture& DrawTexturePoly(Vector2D center, std::vector<Vector2D> points, std::vector<Vector2D> texcoords, Color tint) {
                ::Vector2 *pnt, *texc;
                pnt = new ::Vector2[points.size()];
                texc = new ::Vector2[texcoords.size()];

                for (int i = 0; i < points.size(); i++) *(pnt + i) = points[i];
                for (int i = 0; i < texcoords.size(); i++) *(texc + i) = texcoords[i];

                ::DrawTexturePoly(*this, center, pnt, texc, points.size(), tint);
                
                delete[] pnt;
                delete[] texc;
                return (*this);
            }

            Texture& UpdateTexture(Texture2D texture, const void* pixels) {
                ::UpdateTexture(*this, pixels);
                return (*this);
            }

            Texture& UpdateTextureRec(Texture2D texture, Rectangle rec, const void* pixels) {
                ::UpdateTextureRec(*this, rec, pixels);
                return (*this);
            }
        };

        class RenderTexture {
        private:
            bool isLoaded;

            inline RenderTexture& Clone(::RenderTexture renderText) {
                id = renderText.id;
                texture = renderText.texture;
                depth = renderText.depth;
                return (*this);
            }
        public:
            unsigned int id;
            Texture texture, depth;

            RenderTexture() {
                id = 0;
                texture = Texture(), depth = Texture();
                isLoaded = false;
            }
            RenderTexture(::RenderTexture renderText) {
                id = renderText.id;
                texture = renderText.texture;
                depth = renderText.depth;
                isLoaded = true;
            }
            RenderTexture(unsigned int id, Texture texture, Texture depth) {
                this->id = id;
                this->texture = texture;
                this->depth = depth;
                this->isLoaded = true;
            }

            operator ::RenderTexture() { return { id, texture, depth }; }

            RenderTexture& Load(int width, int height) {
                return Clone(::LoadRenderTexture(width, height));
            }

            RenderTexture& Unload(RenderTexture target) {
                ::UnloadRenderTexture(*this);
                return (*this);
            }
        };

        class NPatchInfo {
        public:
            Rectangle source;
            int left, top, right, bottom, layout;

            NPatchInfo() {
                source = Rectangle();
                left = 0, top = 0, right = 0, bottom = 0, layout = 0;
            }
            NPatchInfo(::NPatchInfo info) {
                source = info.source;
                left = info.left, top = info.top, right = info.right, bottom = info.bottom, layout = info.layout;
            }
            NPatchInfo(Rectangle source, int left, int top, int right, int bottom, int layout) {
                this->source = source;
                this->left = left, this->top = top, this->right = right, this->bottom = bottom;
                this->layout = layout;
            }

            operator ::NPatchInfo() { return { source, left, top, right, bottom, layout }; }
        };

        typedef Texture Texture2D;
        typedef Texture TextureCubemap;
        typedef RenderTexture RenderTexture2D;
    }
}
#endif
