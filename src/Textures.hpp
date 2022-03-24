/* IMPLEMENTATIONS:
    struct Rectangle;       // Rectangle type

    struct Image;           // Image type (multiple pixel formats supported)
                            // NOTE: Data stored in CPU memory (RAM)
    struct Texture;         // Texture type (multiple internal formats supported)
                            // NOTE: Data stored in GPU memory (VRAM)
    struct RenderTexture;   // RenderTexture type, for texture rendering
    struct NPatchInfo;      // N-Patch layout info

    // Image loading functions
    // NOTE: These functions do not require GPU access
    Image LoadImage(const char *fileName);                                                             // Load image from file into CPU memory (RAM)
    Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);       // Load image from RAW file data
    Image LoadImageAnim(const char *fileName, int *frames);                                            // Load image sequence from file (frames appended to image.data)
    Image LoadImageFromMemory(const char *fileType, const unsigned char *fileData, int dataSize);      // Load image from memory buffer
    Image LoadImageFromTexture(Texture2D texture);                                                     // Load image from GPU texture data
    Image LoadImageFromScreen(void);                                                                   // Load image from screen buffer and (screenshot)
    void UnloadImage(Image image);                                                                     // Unload image from CPU memory (RAM)
    bool ExportImage(Image image, const char *fileName);                                               // Export image data to file, returns true on success
    bool ExportImageAsCode(Image image, const char *fileName);                                         // Export image as code file defining an array of bytes, returns true on success

    // Image generation functions
    Image GenImageColor(int width, int height, Color color);                                           // Generate image: plain color
    Image GenImageGradientV(int width, int height, Color top, Color bottom);                           // Generate image: vertical gradient
    Image GenImageGradientH(int width, int height, Color left, Color right);                           // Generate image: horizontal gradient
    Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);      // Generate image: radial gradient
    Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);    // Generate image: checked
    Image GenImageWhiteNoise(int width, int height, float factor);                                     // Generate image: white noise
    Image GenImageCellular(int width, int height, int tileSize);                                       // Generate image: cellular algorithm. Bigger tileSize means bigger cells

    // Image manipulation functions
    Image ImageCopy(Image image);                                                                      // Create an image duplicate (useful for transformations)
    Image ImageFromImage(Image image, Rectangle rec);                                                  // Create an image from another image piece
    Image ImageText(const char *text, int fontSize, Color color);                                      // Create an image from text (default font)
    Image ImageTextEx(Font font, const char *text, float fontSize, float spacing, Color tint);         // Create an image from text (custom sprite font)
    void ImageFormat(Image *image, int newFormat);                                                     // Convert image data to desired format
    void ImageToPOT(Image *image, Color fill);                                                         // Convert image to POT (power-of-two)
    void ImageCrop(Image *image, Rectangle crop);                                                      // Crop an image to a defined rectangle
    void ImageAlphaCrop(Image *image, float threshold);                                                // Crop image depending on alpha value
    void ImageAlphaClear(Image *image, Color color, float threshold);                                  // Clear alpha channel to desired color
    void ImageAlphaMask(Image *image, Image alphaMask);                                                // Apply alpha mask to image
    void ImageAlphaPremultiply(Image *image);                                                          // Premultiply alpha channel
    void ImageResize(Image *image, int newWidth, int newHeight);                                       // Resize image (Bicubic scaling algorithm)
    void ImageResizeNN(Image *image, int newWidth,int newHeight);                                      // Resize image (Nearest-Neighbor scaling algorithm)
    void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill);  // Resize canvas and fill with color
    void ImageMipmaps(Image *image);                                                                   // Generate all mipmap levels for a provided image
    void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                            // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
    void ImageFlipVertical(Image *image);                                                              // Flip image vertically
    void ImageFlipHorizontal(Image *image);                                                            // Flip image horizontally
    void ImageRotateCW(Image *image);                                                                  // Rotate image clockwise 90deg
    void ImageRotateCCW(Image *image);                                                                 // Rotate image counter-clockwise 90deg
    void ImageColorTint(Image *image, Color color);                                                    // Modify image color: tint
    void ImageColorInvert(Image *image);                                                               // Modify image color: invert
    void ImageColorGrayscale(Image *image);                                                            // Modify image color: grayscale
    void ImageColorContrast(Image *image, float contrast);                                             // Modify image color: contrast (-100 to 100)
    void ImageColorBrightness(Image *image, int brightness);                                           // Modify image color: brightness (-255 to 255)
    void ImageColorReplace(Image *image, Color color, Color replace);                                  // Modify image color: replace color
    Color *LoadImageColors(Image image);                                                               // Load color data from image as a Color array (RGBA - 32bit)
    Color *LoadImagePalette(Image image, int maxPaletteSize, int *colorsCount);                        // Load colors palette from image as a Color array (RGBA - 32bit)
    void UnloadImageColors(Color *colors);                                                             // Unload color data loaded with LoadImageColors()
    void UnloadImagePalette(Color *colors);                                                            // Unload colors palette loaded with LoadImagePalette()
    Rectangle GetImageAlphaBorder(Image image, float threshold);                                       // Get image alpha border rectangle
    Color GetImageColor(Image image, int x, int y);                                                    // Get image pixel color at (x, y) position

    // Image drawing functions
    // NOTE: Image software-rendering functions (CPU)
    void ImageClearBackground(Image *dst, Color color);                                                // Clear image background with given color
    void ImageDrawPixel(Image *dst, int posX, int posY, Color color);                                  // Draw pixel within an image
    void ImageDrawPixelV(Image *dst, Vector2 position, Color color);                                   // Draw pixel within an image (Vector version)
    void ImageDrawLine(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color); // Draw line within an image
    void ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color);                          // Draw line within an image (Vector version)
    void ImageDrawCircle(Image *dst, int centerX, int centerY, int radius, Color color);               // Draw circle within an image
    void ImageDrawCircleV(Image *dst, Vector2 center, int radius, Color color);                        // Draw circle within an image (Vector version)
    void ImageDrawRectangle(Image *dst, int posX, int posY, int width, int height, Color color);       // Draw rectangle within an image
    void ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color);                 // Draw rectangle within an image (Vector version)
    void ImageDrawRectangleRec(Image *dst, Rectangle rec, Color color);                                // Draw rectangle within an image
    void ImageDrawRectangleLines(Image *dst, Rectangle rec, int thick, Color color);                   // Draw rectangle lines within an image
    void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);             // Draw a source image within a destination image (tint applied to source)
    void ImageDrawText(Image *dst, const char *text, int posX, int posY, int fontSize, Color color);   // Draw text (using default font) within an image (destination)
    void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text (custom sprite font) within an image (destination)

    // Texture loading functions
    // NOTE: These functions require GPU access
    Texture2D LoadTexture(const char *fileName);                                                       // Load texture from file into GPU memory (VRAM)
    Texture2D LoadTextureFromImage(Image image);                                                       // Load texture from image data
    TextureCubemap LoadTextureCubemap(Image image, int layout);                                        // Load cubemap from image, multiple image cubemap layouts supported
    RenderTexture2D LoadRenderTexture(int width, int height);                                          // Load texture for rendering (framebuffer)
    void UnloadTexture(Texture2D texture);                                                             // Unload texture from GPU memory (VRAM)
    void UnloadRenderTexture(RenderTexture2D target);                                                  // Unload render texture from GPU memory (VRAM)
    void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data
    void UpdateTextureRec(Texture2D texture, Rectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data

    // Texture configuration functions
    void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
    void SetTextureFilter(Texture2D texture, int filter);                                              // Set texture scaling filter mode
    void SetTextureWrap(Texture2D texture, int wrap);                                                  // Set texture wrapping mode

    // Texture drawing functions
    void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
    void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
    void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
    void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint);            // Draw a part of a texture defined by a rectangle
    void DrawTextureQuad(Texture2D texture, Vector2 tiling, Vector2 offset, Rectangle quad, Color tint);  // Draw texture quad with tiling and offset parameters
    void DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint);      // Draw part of a texture (defined by a rectangle) with rotation and scale tiled into dest.
    void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);           // Draw a part of a texture defined by a rectangle with 'pro' parameters
    void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint);   // Draws a texture (or part of it) that stretches or shrinks nicely
    void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points, Vector2 *texcoords, int pointsCount, Color tint);      // Draw a textured polygon
*/
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
                isLoaded = true;
                return Clone(::LoadImage(fileName));
            }

            Image& LoadRaw(const char* fileName, int width, int height, int format, int headerSize) {
                isLoaded = true;
                return Clone(::LoadImageRaw(fileName, width, height, format, headerSize));
            }

            Image& LoadAnim(const char* fileName, int* frames) {
                isLoaded = true;
                return Clone(::LoadImageAnim(fileName, frames));
            }

            Image& LoadFromMemory(const char* fileType, const unsigned char* fileData, int dataSize) {
                isLoaded = true;
                return Clone(::LoadImageFromMemory(fileType, fileData, dataSize));
            }

            Image& LoadFromTexture(Texture2D texture) {
                isLoaded = true;
                return Clone(::LoadImageFromTexture(texture));
            }

            Image& LoadFromScreen(void) {
                isLoaded = true;
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

            Image& GenFromColor(int width, int height, Colors color) {
                return Clone(::GenImageColor(width, height, color));
            }

            Image& GenFromGradientV(int width, int height, Colors top, Colors bottom) {
                return Clone(::GenImageGradientV(width, height, top, bottom));
            }

            Image& GenFromGradientH(int width, int height, Colors top, Colors bottom) {
                return Clone(::GenImageGradientH(width, height, top, bottom));
            }

            Image& GenFromGradientR(int width, int height, float density, Colors inner, Colors outer) {
                return Clone(::GenImageGradientRadial(width, height, density, inner, outer));
            }

            Image& GenChecked(int width, int height, int checksX, int checksY, Colors col1, Colors col2) {
                return Clone(::GenImageChecked(width, height, checksX, checksY, col1, col2));
            }

            Image& GenWhiteNoise(int width, int height, float factor) {
                return Clone(::GenImageWhiteNoise(width, height, factor));
            }

            Image& GenCellular(int width, int height, int tileSize) {
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

            Colors* LoadColors() {
                return (Colors*) ::LoadImageColors(*this);
            }

            Colors* LoadPalette(int maxPaletteSize, int* colorsCount) {
                return (Colors*) ::LoadImagePalette(*this, maxPaletteSize, colorsCount);
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

            Texture& DrawNPatch(NPatchInfo nPatchInfo, Rectangle dest, Vector2D origin, float rotation, Color tint) {
                ::DrawTextureNPatch(*this, nPatchInfo, dest, origin, rotation, tint);
                return (*this);
            }

            Texture& DrawPoly(Vector2D center, Vector2D* points, Vector2D* texcoords, int pointCount, Color tint) {
                ::DrawTexturePoly(*this, center, (::Vector2*)points, (::Vector2*)texcoords, pointCount, tint);
                return (*this);
            }

            Texture& Update(Texture2D texture, const void* pixels) {
                ::UpdateTexture(*this, pixels);
                return (*this);
            }

            Texture& UpdateRec(Texture2D texture, Rectangle rec, const void* pixels) {
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
