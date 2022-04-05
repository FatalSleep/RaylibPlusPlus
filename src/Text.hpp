/* IMPLEMENTATIONS:
    struct GlyphInfo;       // Font character glyph info
    struct Font;            // Font type, includes texture and chars data

    // Font loading/unloading functions
    Font GetFontDefault(void);                                                                      // Get the default Font
    Font LoadFont(const char *fileName);                                                            // Load font from file into GPU memory (VRAM)
    Font LoadFontEx(const char *fileName, int fontSize, int *fontChars, int glyphCount);            // Load font from file with extended parameters
    Font LoadFontFromImage(Image image, Color key, int firstChar);                                  // Load font from Image (XNA style)
    Font LoadFontFromMemory(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize, int *fontChars, int glyphCount); // Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
    GlyphInfo *LoadFontData(const unsigned char *fileData, int dataSize, int fontSize, int *fontChars, int glyphCount, int type);      // Load font data for further use
    Image GenImageFontAtlas(const GlyphInfo *chars, Rectangle **recs, int glyphCount, int fontSize, int padding, int packMethod);      // Generate image font atlas using chars info
    void UnloadFontData(GlyphInfo *chars, int glyphCount);                                          // Unload font chars info data (RAM)
    void UnloadFont(Font font);                                                                     // Unload Font from GPU memory (VRAM)

    // Text drawing functions
    void DrawFPS(int posX, int posY);                                                               // Draw current FPS
    void DrawText(const char *text, int posX, int posY, int fontSize, Color color);                 // Draw text (using default font)
    void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);  // Draw text using font and additional parameters
    void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
    void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)

    // Text misc. functions
    int MeasureText(const char *text, int fontSize);                                                // Measure string width for default font
    Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);              // Measure string size for Font
    int GetGlyphIndex(Font font, int codepoint);                                                    // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
    GlyphInfo GetGlyphInfo(Font font, int codepoint);                                               // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
    Rectangle GetGlyphAtlasRec(Font font, int codepoint);                                           // Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

    // Text codepoints management functions (unicode characters)
    int *LoadCodepoints(const char *text, int *count);                                              // Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
    void UnloadCodepoints(int *codepoints);                                                         // Unload codepoints data from memory
    int GetCodepointCount(const char *text);                                                        // Get total number of codepoints in a UTF-8 encoded string
    int GetCodepoint(const char *text, int *bytesProcessed);                                        // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
    const char *CodepointToUTF8(int codepoint, int *byteSize);                                      // Encode one codepoint into UTF-8 byte array (array length returned as parameter)
    char *TextCodepointsToUTF8(int *codepoints, int length);                                        // Encode text as codepoints array into UTF-8 text string (WARNING: memory must be freed!)

    // Text strings management functions (no utf8 strings, only byte chars)
    // NOTE: Some strings allocate memory internally for returned strings, just be careful!
    int TextCopy(char *dst, const char *src);                                                       // Copy one string to another, returns bytes copied
    bool TextIsEqual(const char *text1, const char *text2);                                         // Check if two text string are equal
    unsigned int TextLength(const char *text);                                                      // Get text length, checks for '\0' ending
    const char *TextFormat(const char *text, ...);                                                  // Text formatting with variables (sprintf style)
    const char *TextSubtext(const char *text, int position, int length);                            // Get a piece of a text string
    char *TextReplace(char *text, const char *replace, const char *by);                             // Replace text string (memory must be freed!)
    char *TextInsert(const char *text, const char *insert, int position);                           // Insert text in a position (memory must be freed!)
    const char *TextJoin(const char **textList, int count, const char *delimiter);                  // Join text strings with delimiter
    const char **TextSplit(const char *text, char delimiter, int *count);                           // Split text into multiple strings
    void TextAppend(char *text, const char *append, int *position);                                 // Append text at specific position and move cursor!
    int TextFindIndex(const char *text, const char *find);                                          // Find first text occurrence within a string
    const char *TextToUpper(const char *text);                                                      // Get upper case version of provided string
    const char *TextToLower(const char *text);                                                      // Get lower case version of provided string
    const char *TextToPascal(const char *text);                                                     // Get Pascal case notation version of provided string
    int TextToInteger(const char *text);                                                            // Get integer value from text (negative values not supported)
*/
#pragma once
#ifndef RAYLIB_PLUSPLUS_FONTS
#define RAYLIB_PLUSPLUS_FONTS
#include "./RaylibExtern.hpp"
#include "./Textures.hpp"

namespace raylib {
    namespace cpp {
        class GlyphInfo {
        public:
            int value, offsetX, offsetY, advanceX;
            Image image;

            GlyphInfo() { value = 0, offsetX = 0, offsetY = 0, advanceX = 0; }
            GlyphInfo(int value, int offsetX, int offsetY, int advanceX, Image image) {
                this->value = value, this->offsetX = offsetX, this->offsetY = offsetY, this->advanceX = advanceX;
                this->image = image;
            }
            GlyphInfo(::GlyphInfo glyph) {
                value = glyph.value, offsetX = glyph.offsetX, offsetY = glyph.offsetY, advanceX = glyph.advanceX;
                image = glyph.image;
            }

            operator ::GlyphInfo() { return { value, offsetX, offsetY, advanceX, image }; }
        };

        class Font {
        private:
            bool isLoaded = false;

            bool MemoryHandler() {
                if (isLoaded) {
                    ::UnloadFont(*this);
                    isLoaded = false;
                }
            }

            Font& Clone(::Font font) {
                baseSize = font.baseSize, glyphCount = font.glyphCount, glyphPadding = font.glyphPadding;
                texture = font.texture;
                recs = font.recs;
                glyphs = font.glyphs;
            }
        public:
            int baseSize, glyphCount, glyphPadding;
            Texture2D texture;
            ::Rectangle* recs;
            ::GlyphInfo* glyphs;

            Font() {
                baseSize = 0, glyphCount = 0, glyphPadding = 0;
                recs = nullptr, glyphs = nullptr;
                isLoaded = false;
            }
            Font(int baseSize, int glyphCount, int glyphPadding, ::Texture2D texture, ::Rectangle* recs, ::GlyphInfo* glyphs) {
                Clone(::Font{ baseSize, glyphCount, glyphPadding, texture, recs, glyphs });
                isLoaded = true;
            }
            Font(::Font font) {
                Clone(font);
                isLoaded = true;
            }
            ~Font() { MemoryHandler(); }

            operator ::Font() { return { baseSize, glyphCount, glyphPadding, texture, recs, glyphs }; }

            bool IsLoaded() { return isLoaded; }

            Font& GetFontDefault(void) {
                ::Font font = ::GetFontDefault();
                return (*this);
            }

            Font& Load(const char* fileName) {
                MemoryHandler();
                isLoaded = true;
                return Clone(::LoadFont(fileName));
            }

            Font& LoadEx(const char* fileName, int fontSize, int* fontChars, int glyphCount) {
                MemoryHandler();
                isLoaded = true;
                return Clone(::LoadFontEx(fileName, fontSize, fontChars, glyphCount));
            }

            Font& LoadFromImage(Image image, Color key, int firstChar) {
                MemoryHandler();
                isLoaded = true;
                return Clone(::LoadFontFromImage(image, key, firstChar));
            }

            Font& LoadFromMemory(const char* fileType, const unsigned char* fileData, int dataSize, int fontSize, int* fontChars, int glyphCount) {
                MemoryHandler();
                isLoaded = true;
                return Clone(::LoadFontFromMemory(fileType, fileData, dataSize, fontSize, fontChars, glyphCount));
            }

            GlyphInfo* LoadFontData(const unsigned char* fileData, int dataSize, int fontSize, int* fontChars, int glyphCount, int type) {
                return (GlyphInfo*) ::LoadFontData(fileData, dataSize, fontSize, fontChars, glyphCount, type);
            }

            Image GenImageFontAtlas(GlyphInfo* chars, Rectangle** recs, int glyphCount, int fontSize, int padding, int packMethod) {
                return ::GenImageFontAtlas((::GlyphInfo*)chars, (::Rectangle**) recs, glyphCount, fontSize, padding, packMethod);
            }
            
            void UnloadFontData() {
                ::UnloadFontData((::GlyphInfo*)glyphs, glyphCount);
            }
            
            Font& Unload() {
                MemoryHandler();
                return (*this);
            }

            static void DrawFPS(int posX, int posY) {
                ::DrawFPS(posX, posY);
            }
            
            static void DrawText(const char* text, int posX, int posY, int fontSize, Colors color) {
                ::DrawText(text, posX, posY, fontSize, color);
            }

            Font& DrawTextEx(const char* text, Vector2D position, float fontSize, float spacing, Colors tint) {
                ::DrawTextEx(*this, text, position, fontSize, spacing, tint);
                return (*this);
            }
            
            Font& DrawTextPro(const char* text, Vector2D position, Vector2D origin, float rotation, float fontSize, float spacing, Colors tint) {
                ::DrawTextPro(*this, text, position, origin, rotation, fontSize, spacing, tint);
                return (*this);
            }

            Font& DrawTextCodepoint(int codepoint, Vector2D position, float fontSize, Colors tint) {
                ::DrawTextCodepoint(*this, codepoint, position, fontSize, tint);
                return (*this);
            }

            static int MeasureText(const char* text, int fontSize) {
                return ::MeasureText(text, fontSize);
            }

            Vector2D MeasureTextEx(const char* text, float fontSize, float spacing) {
                return ::MeasureTextEx(*this, text, fontSize, spacing);
            }

            int GetGlyphIndex(int codepoint) {
                return ::GetGlyphIndex(*this, codepoint);
            }
            
            GlyphInfo GetGlyphInfo(int codepoint) {
                return ::GetGlyphInfo(*this, codepoint);
            }

            Rectangle GetGlyphAtlasRec(int codepoint) {
                return ::GetGlyphAtlasRec(*this, codepoint);
            }
        };

        static class Text {
        public:
            static int* LoadCodepoints(const char* text, int* count) {
                return ::LoadCodepoints(text, count);
            }

            static void UnloadCodepoints(int* codepoints) {
                return ::UnloadCodepoints(codepoints);
            }

            static int GetCodepointCount(const char* text) {
                return ::GetCodepointCount(text);
            }

            static int GetCodepoint(const char* text, int* bytesProcessed) {
                return ::GetCodepoint(text, bytesProcessed);
            }

            static const char* CodepointToUTF8(int codepoint, int* byteSize) {
                return ::CodepointToUTF8(codepoint, byteSize);
            }

            static char* TextCodepointsToUTF8(int* codepoints, int length) {
                return ::TextCodepointsToUTF8(codepoints, length);
            }

            static int TextCopy(char* dst, const char* src) {
                return ::TextCopy(dst, src);
            }
            
            static bool TextIsEqual(const char* text1, const char* text2) {
                return ::TextIsEqual(text1, text2);
            }
            
            static unsigned int TextLength(const char* text) {
                return ::TextLength(text);
            }
            
            static const char* TextFormat(const char* text, ...) {
                va_list args;
                va_start(args, text);
                return ::TextFormat(text, args);
            }
            
            static const char* TextSubtext(const char* text, int position, int length) {
                return ::TextSubtext(text, position, length);
            }
            
            static char* TextReplace(char* text, const char* replace, const char* by) {
                return ::TextReplace(text, replace, by);
            }
            
            static char* TextInsert(const char* text, const char* insert, int position) {
                return ::TextInsert(text, insert, position);
            }
            
            static const char* TextJoin(const char** textList, int count, const char* delimiter) {
                return ::TextJoin(textList, count, delimiter);
            }
            
            static const char** TextSplit(const char* text, char delimiter, int* count) {
                return ::TextSplit(text, delimiter, count);
            }
            
            static void TextAppend(char* text, const char* append, int* position) {
                ::TextAppend(text, append, position);
            }
            
            static int TextFindIndex(const char* text, const char* find) {
                return ::TextFindIndex(text, find);
            }
            
            static const char* TextToUpper(const char* text) {
                return ::TextToUpper(text);
            }
            
            static const char* TextToLower(const char* text) {
                return ::TextToLower(text);
            }

            static const char* TextToPascal(const char* text) {
                return ::TextToPascal(text);
            }

            static int TextToInteger(const char* text) {
                return ::TextToInteger(text);
            }
        };
    }
}
#endif
