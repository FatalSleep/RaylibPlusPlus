/* IMPLEMENTATIONS:
    struct Camera;          // Camera type, defines 3d camera position/orientation
    struct Camera2D;        // Camera2D type, defines a 2d camera
    struct Shader;          // Shader type (generic shader)
    struct VrDeviceInfo;    // VR device parameters
    struct VrStereoConfig;  // VR Stereo rendering configuration for simulator


    //
    // Window-related functions
    //
    void InitWindow(int width, int height, const char *title);              // Initialize window and OpenGL context
    bool WindowShouldClose(void);                                           // Check if KEY_ESCAPE pressed or Close icon pressed
    void CloseWindow(void);                                                 // Close window and unload OpenGL context
    bool IsWindowReady(void);                                               // Check if window has been initialized successfully
    bool IsWindowFullscreen(void);                                          // Check if window is currently fullscreen
    bool IsWindowHidden(void);                                              // Check if window is currently hidden (only PLATFORM_DESKTOP)
    bool IsWindowMinimized(void);                                           // Check if window is currently minimized (only PLATFORM_DESKTOP)
    bool IsWindowMaximized(void);                                           // Check if window is currently maximized (only PLATFORM_DESKTOP)
    bool IsWindowFocused(void);                                             // Check if window is currently focused (only PLATFORM_DESKTOP)
    bool IsWindowResized(void);                                             // Check if window has been resized last frame
    bool IsWindowState(unsigned int flag);                                  // Check if one specific window flag is enabled
    void SetWindowState(unsigned int flags);                                // Set window configuration state using flags
    void ClearWindowState(unsigned int flags);                              // Clear window configuration state flags
    void ToggleFullscreen(void);                                            // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
    void MaximizeWindow(void);                                              // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
    void MinimizeWindow(void);                                              // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
    void RestoreWindow(void);                                               // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
    void SetWindowIcon(Image image);                                        // Set icon for window (only PLATFORM_DESKTOP)
    void SetWindowTitle(const char *title);                                 // Set title for window (only PLATFORM_DESKTOP)
    void SetWindowPosition(int x, int y);                                   // Set window position on screen (only PLATFORM_DESKTOP)
    void SetWindowMonitor(int monitor);                                     // Set monitor for the current window (fullscreen mode)
    void SetWindowMinSize(int width, int height);                           // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
    void SetWindowSize(int width, int height);                              // Set window dimensions
    void *GetWindowHandle(void);                                            // Get native window handle
    int GetScreenWidth(void);                                               // Get current screen width
    int GetScreenHeight(void);                                              // Get current screen height
    int GetMonitorCount(void);                                              // Get number of connected monitors
    int GetCurrentMonitor(void);                                            // Get current connected monitor
    Vector2 GetMonitorPosition(int monitor);                                // Get specified monitor position
    int GetMonitorWidth(int monitor);                                       // Get specified monitor width (max available by monitor)
    int GetMonitorHeight(int monitor);                                      // Get specified monitor height (max available by monitor)
    int GetMonitorPhysicalWidth(int monitor);                               // Get specified monitor physical width in millimetres
    int GetMonitorPhysicalHeight(int monitor);                              // Get specified monitor physical height in millimetres
    int GetMonitorRefreshRate(int monitor);                                 // Get specified monitor refresh rate
    Vector2 GetWindowPosition(void);                                        // Get window position XY on monitor
    Vector2 GetWindowScaleDPI(void);                                        // Get window scale DPI factor
    const char *GetMonitorName(int monitor);                                // Get the human-readable, UTF-8 encoded name of the primary monitor
    void SetClipboardText(const char *text);                                // Set clipboard text content
    const char *GetClipboardText(void);                                     // Get clipboard text content

    void ClearBackground(Color color);                                      // Set background color (framebuffer clear color)
    void BeginDrawing(void);                                                // Setup canvas (framebuffer) to start drawing
    void EndDrawing(void);                                                  // End canvas drawing and swap buffers (double buffering)
    void BeginMode2D(Camera2D camera);                                      // Begin 2D mode with custom camera (2D)
    void EndMode2D(void);                                                   // Ends 2D mode with custom camera
    void BeginMode3D(Camera3D camera);                                      // Begin 3D mode with custom camera (3D)
    void EndMode3D(void);                                                   // Ends 3D mode and returns to default 2D orthographic mode
    void BeginTextureMode(RenderTexture2D target);                          // Begin drawing to render texture
    void EndTextureMode(void);                                              // Ends drawing to render texture
    void BeginShaderMode(Shader shader);                                    // Begin custom shader drawing
    void EndShaderMode(void);                                               // End custom shader drawing (use default shader)
    void BeginBlendMode(int mode);                                          // Begin blending mode (alpha, additive, multiplied, subtract, custom)
    void EndBlendMode(void);                                                // End blending mode (reset to default: alpha blending)
    void BeginScissorMode(int x, int y, int width, int height);             // Begin scissor mode (define screen area for following drawing)
    void EndScissorMode(void);                                              // End scissor mode
    void BeginVrStereoMode(VrStereoConfig config);                          // Begin stereo rendering (requires VR simulator)
    void EndVrStereoMode(void);                                             // End stereo rendering (requires VR simulator)

    VrStereoConfig LoadVrStereoConfig(VrDeviceInfo device);                 // Load VR stereo config for VR simulator device parameters
    void UnloadVrStereoConfig(VrStereoConfig config);                       // Unload VR stereo config

    void SetTargetFPS(int fps);                                             // Set target FPS (maximum)
    int GetFPS(void);                                                       // Get current FPS
    float GetFrameTime(void);                                               // Get time in seconds for last frame drawn (delta time)
    double GetTime(void);                                                   // Get elapsed time in seconds since InitWindow()

    int GetRandomValue(int min, int max);                                   // Get a random value between min and max (both included)
    void SetRandomSeed(unsigned int seed);                                  // Set the seed for the random number generator
    void TakeScreenshot(const char *fileName);                              // Takes a screenshot of current screen (filename extension defines format)
    void SetConfigFlags(unsigned int flags);                                // Setup init configuration flags (view FLAGS)

    void TraceLog(int logLevel, const char *text, ...);                     // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
    void SetTraceLogLevel(int logLevel);                                    // Set the current threshold (minimum) log level
    [NOT-REIMPLEMENTED] void *MemAlloc(int size);                           // Internal memory allocator
    [NOT-REIMPLEMENTED] void *MemRealloc(void *ptr, int size);              // Internal memory reallocator
    [NOT-REIMPLEMENTED] void MemFree(void *ptr);                            // Internal memory free

    Ray GetMouseRay(Vector2 mousePosition, Camera camera);                  // Get a ray trace from mouse position
    Matrix GetCameraMatrix(Camera camera);                                  // Get camera transform matrix (view matrix)
    Matrix GetCameraMatrix2D(Camera2D camera);                              // Get camera 2d transform matrix
    Vector2 GetWorldToScreen(Vector3 position, Camera camera);              // Get the screen space position for a 3d world space position
    Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height); // Get size position for a 3d world space position
    Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera);          // Get the screen space position for a 2d camera world space position
    Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera);          // Get the world space position for a 2d camera screen space position

    void SetTraceLogCallback(TraceLogCallback callback);                    // Set custom trace log
    void SetLoadFileDataCallback(LoadFileDataCallback callback);            // Set custom file binary data loader
    void SetSaveFileDataCallback(SaveFileDataCallback callback);            // Set custom file binary data saver
    void SetLoadFileTextCallback(LoadFileTextCallback callback);            // Set custom file text data loader
    void SetSaveFileTextCallback(SaveFileTextCallback callback);            // Set custom file text data saver

    unsigned char *LoadFileData(const char *fileName, unsigned int *bytesRead);     // Load file data as byte array (read)
    void UnloadFileData(unsigned char *data);                               // Unload file data allocated by LoadFileData()
    bool SaveFileData(const char *fileName, void *data, unsigned int bytesToWrite); // Save data to file from byte array (write), returns true on success
    char *LoadFileText(const char *fileName);                               // Load text data from file (read), returns a '\0' terminated string
    void UnloadFileText(char *text);                                        // Unload file text data allocated by LoadFileText()
    bool SaveFileText(const char *fileName, char *text);                    // Save text data to file (write), string must be '\0' terminated, returns true on success
    bool FileExists(const char *fileName);                                  // Check if file exists
    bool DirectoryExists(const char *dirPath);                              // Check if a directory path exists
    bool IsFileExtension(const char *fileName, const char *ext);            // Check file extension (including point: .png, .wav)
    const char *GetFileExtension(const char *fileName);                     // Get pointer to extension for a filename string (includes dot: '.png')
    const char *GetFileName(const char *filePath);                          // Get pointer to filename for a path string
    const char *GetFileNameWithoutExt(const char *filePath);                // Get filename string without extension (uses static string)
    const char *GetDirectoryPath(const char *filePath);                     // Get full path for a given fileName with path (uses static string)
    const char *GetPrevDirectoryPath(const char *dirPath);                  // Get previous directory path for a given path (uses static string)
    const char *GetWorkingDirectory(void);                                  // Get current working directory (uses static string)
    char **GetDirectoryFiles(const char *dirPath, int *count);              // Get filenames in a directory path (memory should be freed)
    void ClearDirectoryFiles(void);                                         // Clear directory files paths buffers (free memory)
    bool ChangeDirectory(const char *dir);                                  // Change working directory, return true on success
    bool IsFileDropped(void);                                               // Check if a file has been dropped into window
    char **GetDroppedFiles(int *count);                                     // Get dropped files names (memory should be freed)
    void ClearDroppedFiles(void);                                           // Clear dropped files paths buffer (free memory)
    long GetFileModTime(const char *fileName);                              // Get file modification time (last write time)

    unsigned char *CompressData(unsigned char *data, int dataLength, int *compDataLength);        // Compress data (DEFLATE algorithm)
    unsigned char *DecompressData(unsigned char *compData, int compDataLength, int *dataLength);  // Decompress data (DEFLATE algorithm)
    char *EncodeDataBase64(const unsigned char *data, int dataLength, int *outputLength);         // Encode data to Base64 string
    unsigned char *DecodeDataBase64(unsigned char *data, int *outputLength);                      // Decode Base64 string data

    bool SaveStorageValue(unsigned int position, int value);                // Save integer value to storage file (to defined position), returns true on success
    int LoadStorageValue(unsigned int position);                            // Load integer value from storage file (from defined position)

    void OpenURL(const char *url);                                          // Open URL with default system browser (if available)


    //
    // Input-related functions: keyboard
    //
    bool IsKeyPressed(int key);                                             // Check if a key has been pressed once
    bool IsKeyDown(int key);                                                // Check if a key is being pressed
    bool IsKeyReleased(int key);                                            // Check if a key has been released once
    bool IsKeyUp(int key);                                                  // Check if a key is NOT being pressed
    void SetExitKey(int key);                                               // Set a custom key to exit program (default is ESC)
    int GetKeyPressed(void);                                                // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
    int GetCharPressed(void);                                               // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty


    //
    // Camera System Functions (Module: rcamera)
    //
    void SetCameraMode(Camera camera, int mode);                            // Set camera mode (multiple camera modes available)
    void UpdateCamera(Camera *camera);                                      // Update camera position for selected mode

    void SetCameraPanControl(int keyPan);                                   // Set camera pan key to combine with mouse movement (free camera)
    void SetCameraAltControl(int keyAlt);                                   // Set camera alt key to combine with mouse movement (free camera)
    void SetCameraSmoothZoomControl(int keySmoothZoom);                     // Set camera smooth zoom key to combine with mouse (free camera)
    void SetCameraMoveControls(int keyFront, int keyBack, int keyRight, int keyLeft, int keyUp, int keyDown); // Set camera move controls (1st person and 3rd person cameras)


    //
    // Shader management functions
    // NOTE: Shader functionality is not available on OpenGL 1.1
    //
    Shader LoadShader(const char *vsFileName, const char *fsFileName);      // Load shader from files and bind default locations
    Shader LoadShaderFromMemory(const char *vsCode, const char *fsCode);    // Load shader from code strings and bind default locations
    int GetShaderLocation(Shader shader, const char *uniformName);          // Get shader uniform location
    int GetShaderLocationAttrib(Shader shader, const char *attribName);     // Get shader attribute location
    void SetShaderValue(Shader shader, int locIndex, const void *value, int uniformType);               // Set shader uniform value
    void SetShaderValueV(Shader shader, int locIndex, const void *value, int uniformType, int count);   // Set shader uniform value vector
    void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat);         // Set shader uniform value (matrix 4x4)
    void SetShaderValueTexture(Shader shader, int locIndex, Texture2D texture); // Set shader uniform value for texture (sampler2d)
    void UnloadShader(Shader shader);                                       // Unload shader from GPU memory (VRAM)


    //
    // Cursor-related functions: Mouse, Gestures & Touch
    //
    void ShowCursor(void);                                                  // Shows cursor
    void HideCursor(void);                                                  // Hides cursor
    bool IsCursorHidden(void);                                              // Check if cursor is not visible
    void EnableCursor(void);                                                // Enables cursor (unlock cursor)
    void DisableCursor(void);                                               // Disables cursor (lock cursor)
    bool IsCursorOnScreen(void);                                            // Check if cursor is on the screen

    bool IsMouseButtonPressed(int button);                                  // Check if a mouse button has been pressed once
    bool IsMouseButtonDown(int button);                                     // Check if a mouse button is being pressed
    bool IsMouseButtonReleased(int button);                                 // Check if a mouse button has been released once
    bool IsMouseButtonUp(int button);                                       // Check if a mouse button is NOT being pressed
    int GetMouseX(void);                                                    // Get mouse position X
    int GetMouseY(void);                                                    // Get mouse position Y
    Vector2 GetMousePosition(void);                                         // Get mouse position XY
    Vector2 GetMouseDelta(void);                                            // Get mouse delta between frames
    void SetMousePosition(int x, int y);                                    // Set mouse position XY
    void SetMouseOffset(int offsetX, int offsetY);                          // Set mouse offset
    void SetMouseScale(float scaleX, float scaleY);                         // Set mouse scaling
    float GetMouseWheelMove(void);                                          // Get mouse wheel movement Y
    void SetMouseCursor(int cursor);                                        // Set mouse cursor

    void SetClipboardText(const char *text);                                // Set clipboard text content
    const char *GetClipboardText(void);                                     // Get clipboard text content

    int GetTouchX(void);                                                    // Get touch position X for touch point 0 (relative to screen size)
    int GetTouchY(void);                                                    // Get touch position Y for touch point 0 (relative to screen size)
    Vector2 GetTouchPosition(int index);                                    // Get touch position XY for a touch point index (relative to screen size)
    int GetTouchPointId(int index);                                         // Get touch point identifier for given index
    int GetTouchPointCount(void);                                           // Get number of touch points

    void SetGesturesEnabled(unsigned int flags);                            // Enable a set of gestures using flags
    bool IsGestureDetected(int gesture);                                    // Check if a gesture have been detected
    int GetGestureDetected(void);                                           // Get latest detected gesture
    float GetGestureHoldDuration(void);                                     // Get gesture hold time in milliseconds
    Vector2 GetGestureDragVector(void);                                     // Get gesture drag vector
    float GetGestureDragAngle(void);                                        // Get gesture drag angle
    Vector2 GetGesturePinchVector(void);                                    // Get gesture pinch delta
    float GetGesturePinchAngle(void);                                       // Get gesture pinch angle


    //
    // Monitor-related functions
    //
    int GetMonitorCount(void);                                              // Get number of connected monitors
    int GetCurrentMonitor(void);                                            // Get current connected monitor
    Vector2 GetMonitorPosition(int monitor);                                // Get specified monitor position
    int GetMonitorWidth(int monitor);                                       // Get specified monitor width (max available by monitor)
    int GetMonitorHeight(int monitor);                                      // Get specified monitor height (max available by monitor)
    int GetMonitorPhysicalWidth(int monitor);                               // Get specified monitor physical width in millimetres
    int GetMonitorPhysicalHeight(int monitor);                              // Get specified monitor physical height in millimetres
    int GetMonitorRefreshRate(int monitor);                                 // Get specified monitor refresh rate
    Vector2 GetWindowPosition(void);                                        // Get window position XY on monitor
    Vector2 GetWindowScaleDPI(void);                                        // Get window scale DPI factor
    const char *GetMonitorName(int monitor);                                // Get the human-readable, UTF-8 encoded name of the primary monitor
*/
#pragma once
#ifndef RAYLIB_PLUSPLUS_CORE
#define RAYLIB_PLUSPLUS_CORE
#include "./RaylibExtern.hpp"
#include "./Colors.hpp"
#include "./Vector.hpp"
#include "./Invokable.hpp"
#include <string>

namespace raylib {
    namespace cpp {
        static class Window {
        public:
            static void Init(int width, int height, const char* title) {
                ::InitWindow(width, height, title);
            }

            static bool ShouldClose() {
                return ::WindowShouldClose();
            }

            static void Close() {
                ::CloseWindow();
            }

            static bool IsReady() {
                return ::IsWindowReady();
            }

            static bool IsFullscreen() {
                return ::IsWindowFullscreen(); 
            }

            static bool IsHidden() {
                return ::IsWindowHidden();
            }
            
            static bool IsMinimized() {
                return ::IsWindowMinimized();
            }
            
            static bool IsMaximized() {
                return ::IsWindowMaximized();
            }
            
            static bool IsFocused() {
                return ::IsWindowFocused();
            }

            static bool IsResized() {
                return ::IsWindowResized();
            }
            
            static bool IsState(unsigned int flag) {
                return ::IsWindowState(flag);
            }

            static void SetState(unsigned int flags) {
                ::SetWindowState(flags);
            }

            static void ClearState(unsigned int flags) {
                ::ClearWindowState(flags);
            }

            static void ToggleFullscreen() {
                ::ToggleFullscreen();
            }

            static void Maximize() {
                ::MaximizeWindow();
            }

            static void Minimize() {
                ::MinimizeWindow();
            }

            static void Restore() {
                ::RestoreWindow();
            }
            
            static void Toggle() {
                (IsMinimized()) ? Minimize() : Maximize();
            }

            static void SetIcon(Image image) {
                ::SetWindowIcon(image);
            }

            static void SetTitle(const char* title) {
                ::SetWindowTitle(title);
            }

            static void SetPosition(int x, int y) {
                ::SetWindowPosition(x, y);
            }

            static void SetMonitor(int monitor) {
                ::SetWindowMonitor(monitor);
            }

            static void SetMinSize(int width, int height) {
                ::SetWindowMinSize(width, height);
            }

            static void SetSize(int width, int height) {
                ::SetWindowSize(width, height);
            }

            static void* GetHandle() {
                return ::GetWindowHandle();
            }

            static int GetScreenWidth() {
                return ::GetScreenWidth();
            }
            
            static int GetScreenHeight() {
                return ::GetScreenHeight();
            }

            static Vector2D GetPosition() {
                return ::GetWindowPosition();
            }

            static Vector2D GetScaleDPI() {
                return ::GetWindowScaleDPI();
            }

            static void ClearBackground(Colors color) {
                ::ClearBackground(color);
            }

            static void BeginDrawing() {
                ::BeginDrawing();
            }

            static void EndDrawing() {
                ::EndDrawing();
            }

            static void BeginMode2D(Camera2D camera) {
                ::BeginMode2D(camera);
            }

            static void EndMode2D() {
                ::EndMode2D();
            }

            static void BeginMode3D(Camera3D camera) {
                ::BeginMode3D(camera);
            }

            static void EndMode3D() {
                ::EndMode3D();
            }

            static void BeginTextureMode(RenderTexture2D target) {
                ::BeginTextureMode(target);
            }

            static void EndTextureMode() {
                ::EndTextureMode();
            }

            static void BeginShaderMode(Shader shader) {
                ::BeginShaderMode(shader);
            }

            static void EndShaderMode() {
                ::EndShaderMode();
            }

            static void BeginBlendMode(int mode) {
                ::BeginBlendMode(mode);
            }

            static void EndBlendMode() {
                ::EndBlendMode();
            }

            static void BeginScissorMode(int x, int y, int width, int height) {
                ::BeginScissorMode(x, y, width, height);
            }

            static void EndScissorMode() {
                ::EndScissorMode();
            }

            static void BeginVrStereoMode(VrStereoConfig config) {
                ::BeginVrStereoMode(config);
            }

            static void EndVrStereoMode() {
                ::EndVrStereoMode();
            }

            static VrStereoConfig LoadVrStereoConfig(VrDeviceInfo device) {
                ::LoadVrStereoConfig(device);
            }

            static void UnloadVrStereoConfig(VrStereoConfig config) {
                ::UnloadVrStereoConfig(config);
            }

            static void SetTargetFPS(int fps) {
                ::SetTargetFPS(fps);
            }

            static int GetFPS() {
                return ::GetFPS();
            }

            static float GetFrameTime() {
                return ::GetFrameTime();
            }

            static double GetTime() {
                return ::GetTime();
            }

            static void TakeScreenshot(const char* fileName) {
                ::TakeScreenshot(fileName);
            }

            static void SetConfigFlags(unsigned int flags) {
                ::SetConfigFlags(flags);
            }
        };
        
        static class FileIO {
        public:
            static void SetTraceLogCallback(TraceLogCallback callback) {
                ::SetTraceLogCallback(callback);
            }

            static void SetLoadFileDataCallback(LoadFileDataCallback callback) {
                ::SetLoadFileDataCallback(callback);
            }

            static void SetSaveFileDataCallback(SaveFileDataCallback callback) {
                ::SetSaveFileDataCallback(callback);
            }

            static void SetLoadFileTextCallback(LoadFileTextCallback callback) {
                ::SetLoadFileTextCallback(callback);
            }

            static void SetSaveFileTextCallback(SaveFileTextCallback callback) {
                ::SetSaveFileTextCallback(callback);
            }

            static unsigned char* LoadFileData(const char* fileName, unsigned int* bytesRead) {
                return ::LoadFileData(fileName, bytesRead);
            }

            static void UnloadFileData(unsigned char* data) {
                return ::UnloadFileData(data);
            }

            static bool SaveFileData(const char* fileName, void* data, unsigned int bytesToWrite) {
                return ::SaveFileData(fileName, data, bytesToWrite);
            }

            static char* LoadFileText(const char* fileName) {
                return ::LoadFileText(fileName);
            }
            
            static void UnloadFileText(char* text) {
                return ::UnloadFileText(text);
            }
            
            static bool SaveFileText(const char* fileName, char* text) {
                return ::SaveFileText(fileName, text);
            }
            
            static bool FileExists(const char* fileName) {
                return ::FileExists(fileName);
            }
            
            static bool DirectoryExists(const char* dirPath) {
                return ::DirectoryExists(dirPath);
            }
            
            static bool IsFileExtension(const char* fileName, const char* ext) {
                return ::IsFileExtension(fileName, ext);
            }
            
            static const char* GetFileExtension(const char* fileName) {
                return ::GetFileExtension(fileName);
            }
            
            static const char* GetFileName(const char* filePath) {
                return ::GetFileName(filePath);
            }
            
            static const char* GetFileNameWithoutExt(const char* filePath) {
                return ::GetFileNameWithoutExt(filePath);
            }
            
            static const char* GetDirectoryPath(const char* filePath) {
                return ::GetDirectoryPath(filePath);
            }
            
            static const char* GetPrevDirectoryPath(const char* dirPath) {
                return ::GetPrevDirectoryPath(dirPath);
            }
            
            static const char* GetWorkingDirectory() {
                return ::GetWorkingDirectory();
            }
            
            static char** GetDirectoryFiles(const char* dirPath, int* count) {
                return ::GetDirectoryFiles(dirPath, count);
            }
            
            static void ClearDirectoryFiles() {
                return ::ClearDirectoryFiles();
            }
            
            static bool ChangeDirectory(const char* dir) {
                return ::ChangeDirectory(dir);
            }
            
            static bool IsFileDropped() {
                return ::IsFileDropped();
            }
            
            static char** GetDroppedFiles(int* count) {
                return ::GetDroppedFiles(count);
            }
            
            static void ClearDroppedFiles() {
                ::ClearDroppedFiles();
            }
            
            static long GetFileModTime(const char* fileName) {
                return ::GetFileModTime(fileName);
            }

            static unsigned char* CompressData(unsigned char* data, int dataLength, int* compDataLength) {
                return ::CompressData(data, dataLength, compDataLength);
            }

            static unsigned char* DecompressData(unsigned char* compData, int compDataLength, int* dataLength) {
                return ::DecompressData(compData, compDataLength, dataLength);
            }

            static char* EncodeDataBase64(const unsigned char* data, int dataLength, int* outputLength) {
                return ::EncodeDataBase64(data, dataLength, outputLength);
            }

            static unsigned char* DecodeDataBase64(unsigned char* data, int* outputLength) {
                return ::DecodeDataBase64(data, outputLength);
            }

            static bool SaveStorageValue(unsigned int position, int value) {
                return ::SaveStorageValue(position, value);
            }

            static int LoadStorageValue(unsigned int position) {
                return ::LoadStorageValue(position);
            }

            static void OpenURL(const char* url) {
                ::OpenURL(url);
            }
        };

        class Camera2D {
        public:
            Vector2D offset, target;
            float rotation, zoom;

            Camera2D() {
                rotation = 0.0f, zoom = 0.0f;
            }

            Camera2D(Vector2D offset, Vector2D target, float rotation, float zoom) {
                this->offset = offset, this->target = target;
                this->rotation = rotation, this->zoom = zoom;
            }

            Camera2D(::Camera2D cam) {
                offset = cam.offset, target = cam.target;
                rotation = cam.rotation, zoom = cam.zoom;
            }

            operator ::Camera2D() { return { offset, target, rotation, zoom }; }

            Matrix GetMatrix() {
                return ::GetCameraMatrix2D(*this);
            }

            Vector2D GetWorldToScreen2D(Vector2D position) {
                return ::GetWorldToScreen2D(position, *this);
            }

            Vector2D GetScreenToWorld2D(Vector2D position) {
                return ::GetScreenToWorld2D(position, *this);
            }
        };

        class Camera3D {
        private:
            Camera3D& Clone(::Camera3D cam) {
                this->position = cam.position, this->target = cam.target, this->upVector = cam.up;
                this->fovy = cam.fovy;
                this->projection = cam.projection;
            }
        public:
            Vector3D position, target, upVector;
            float fovy;
            int projection;

            Camera3D() {
                fovy = 0.0f;
                projection = 0;
            }

            Camera3D(Vector3D position, Vector3D target, Vector3D upVector, float fovy, int projection) {
                this->position = position, this->target = target, this->upVector = upVector;
                this->fovy = fovy;
                this->projection = projection;
            }

            Camera3D(::Camera3D cam) {
                this->position = cam.position, this->target = cam.target, this->upVector = cam.up;
                this->fovy = cam.fovy;
                this->projection = cam.projection;
            }

            operator ::Camera3D() {
                return { position, target, upVector, fovy, projection };
            }

            Camera3D& SetMode(int mode) {
                ::SetCameraMode(*this, mode);
                return (*this);
            }

            void Update() {
                ::Camera3D camera = *this;
                ::UpdateCamera(&camera);
                Clone(camera);
            }

            void SetPanControl(int keyPan) {
                ::SetCameraPanControl(keyPan);
            }

            void SetAltControl(int keyAlt) {
                ::SetCameraAltControl(keyAlt);
            }

            void SetSmoothZoomControl(int keySmoothZoom) {
                ::SetCameraSmoothZoomControl(keySmoothZoom);
            }

            void SetMoveControls(int keyFront, int keyBack, int keyRight, int keyLeft, int keyUp, int keyDown) {
                ::SetCameraMoveControls(keyFront, keyBack, keyRight, keyLeft, keyUp, keyDown);
            }

            Matrix GetMatrix() {
                return ::GetCameraMatrix(*this);
            }

            Ray GetMouseRay(Vector2D mousePosition) {
                return ::GetMouseRay(mousePosition, *this);
            }

            Vector2D GetWorldToScreen(Vector3D position) {
                return ::GetWorldToScreen(position, *this);
            }

            Vector2D GetWorldToScreenEx(Vector3D position, int width, int height) {
                return ::GetWorldToScreenEx(position, *this, width, height);
            }
        };
        typedef Camera3D Camera;

        static class Keyboard {
        public:
            static bool IsKeyPressed(int key) {
                return ::IsKeyPressed(key);
            }

            static bool IsKeyDown(int key) {
                return ::IsKeyPressed(key);
            }

            static bool IsKeyReleased(int key) {
                return ::IsKeyReleased(key);
            }

            static bool IsKeyUp(int key) {
                return ::IsKeyUp(key);
            }

            static void SetExitKey(int key) {
                return ::SetExitKey(key);
            }

            static int GetKeyPressed() {
                return ::GetKeyPressed();
            }

            static int GetCharPressed() {
                return ::GetCharPressed();
            }
        };
        
        class GamePad {
        public:
            int id;

            GamePad() {
                id = 0;
            }

            GamePad(int id) {
                this->id = id;
            }

            bool IsAvailable() {
                return ::IsGamepadAvailable(id);
            }

            const char* GetName() {
                return ::GetGamepadName(id);
            }

            bool IsButtonPressed(int button) {
                return ::IsGamepadButtonPressed(id, button);
            }

            bool IsButtonDown(int button) {
                return ::IsGamepadButtonDown(id, button);
            }

            bool IsButtonReleased(int button) {
                return ::IsGamepadButtonReleased(id, button);
            }

            bool IsButtonUp(int button) {
                return ::IsGamepadButtonUp(id, button);
            }

            int IsAnyButtonPressed() {
                return ::GetGamepadButtonPressed();
            }

            int GetAxisCount() {
                return ::GetGamepadAxisCount(id);
            }

            float GetAxisMovement(int axis) {
                return ::GetGamepadAxisMovement(id, axis);
            }

            int SetMappings(const char* mappings) {
                return ::SetGamepadMappings(mappings);
            }
        };

        class Shader {
        private:
            bool isLoaded = false;

            bool MemoryHandler() {
                if (isLoaded) {
                    ::UnloadShader(*this);
                    isLoaded = false;
                }
            }

        public:
            unsigned int id;
            int* locs;

            Shader() { id = 0, locs = nullptr; isLoaded = false; }

            Shader(unsigned int id, int* locs) { this->id, this->locs = locs; isLoaded = true; }

            ~Shader() { MemoryHandler(); }

            operator ::Shader() { return { id, locs }; }

            bool IsLoaded() { return isLoaded; }

            Shader& Load(const char* vsFileName, const char* fsFileName) {
                MemoryHandler();
                ::Shader shad = ::LoadShader(vsFileName, fsFileName);
                id = shad.id, locs = shad.locs;
                isLoaded = true;
                return (*this);
            }

            Shader& LoadFromMemory(const char* vsCode, const char* fsCode) {
                MemoryHandler();
                ::Shader shad = ::LoadShaderFromMemory(vsCode, fsCode);
                id = shad.id, locs = shad.locs;
                isLoaded = true;
                return (*this);
            }

            int GetLocation(const char* uniformName) {
                return ::GetShaderLocation(*this, uniformName);
            }

            int GetLocationAttrib(const char* attribName) {
                return ::GetShaderLocationAttrib(*this, attribName);
            }

            Shader& SetValue(int locIndex, const void* value, int uniformType) {
                ::SetShaderValue(*this, locIndex, value, uniformType);
                return (*this);
            }

            Shader& SetValueV(int locIndex, const void* value, int uniformType, int count) {
                ::SetShaderValueV(*this, locIndex, value, uniformType, count);
                return (*this);
            }

            Shader& SetValueMatrix(int locIndex, Matrix mat) {
                ::SetShaderValueMatrix(*this, locIndex, mat);
                return (*this);
            }

            Shader& SetValueTexture(int locIndex, Texture2D texture) {
                ::SetShaderValueTexture(*this, locIndex, texture);
                return (*this);
            }

            Shader& Unload() {
                MemoryHandler();
                return (*this);
            }
        };


        class MonitorInfo {
        public:
            float x, y;
            int w, h, id, refresh;
            const char* name;

            MonitorInfo() {
                x = 0, y = 0, id = 0, refresh = 0;
                name = nullptr;
            }

            MonitorInfo(float x, float y, int id, int refresh, char* name = nullptr) {
                this->x = x, this->y = y, this->id = id, this->refresh = refresh;
                this->name = name;
            }

            MonitorInfo(int id) {
                this->id = id;
                Vector2D pos = GetPosition();
                x = pos.x, y = pos.y;
                w = GetWidth(), h = GetHeight();
                refresh = GetRefreshRate();
                name = GetName();
            }

            MonitorInfo& Update() {
                Vector2D pos = GetPosition();
                x = pos.x, y = pos.y;
                w = GetWidth(), h = GetHeight();
                refresh = GetRefreshRate();
                name = GetName();
                return (*this);
            }

            static int GetCount() { return ::GetMonitorCount(); }

            static int GetCurrent() { return ::GetCurrentMonitor(); }

            static Vector2D GetPosition(int monitor) { return ::GetMonitorPosition(monitor); }
            Vector2D GetPosition() {
                return ::GetMonitorPosition(id);
            }

            static int GetWidth(int monitor) { return ::GetMonitorWidth(monitor); }
            int GetWidth() {
                return ::GetMonitorWidth(id);
            }
            
            static int GetHeight(int monitor) { return ::GetMonitorHeight(monitor); }
            int GetHeight() {
                return ::GetMonitorHeight(id);
            }

            static int GetPhysicalWidth(int monitor) { return ::GetMonitorPhysicalWidth(monitor); }
            int GetPhysicalWidth() {
                return ::GetMonitorPhysicalWidth(id);
            }

            static int GetPhysicalHeight(int monitor) { return ::GetMonitorPhysicalHeight(monitor); }
            int GetPhysicalHeight() {
                return ::GetMonitorPhysicalHeight(id);
            }

            static int GetRefreshRate(int monitor) { return ::GetMonitorRefreshRate(monitor); }
            int GetRefreshRate() {
                return ::GetMonitorRefreshRate(id);
            }
            
            static const char* GetName(int monitor) { return ::GetMonitorName(monitor); }
            const char* GetName() {
                return ::GetMonitorName(id);
            }
        };

        static class Cursor {
            static void ShowCursor() {
                ::ShowCursor();
            }

            static void HideCursor() {
                ::HideCursor();
            }

            static bool IsCursorHidden() {
                return ::IsCursorHidden();
            }

            static void EnableCursor() {
                ::EnableCursor();
            }

            static void DisableCursor() {
                ::DisableCursor();
            }

            static bool IsCursorOnScreen() {
                return ::IsCursorOnScreen();
            }

            static bool IsMouseButtonPressed(int button) {
                return ::IsMouseButtonPressed(button);
            }

            static bool IsMouseButtonDown(int button) {
                return IsMouseButtonDown(button);
            }

            static bool IsMouseButtonReleased(int button) {
                return IsMouseButtonReleased(button);
            }

            static bool IsMouseButtonUp(int button) {
                return IsMouseButtonUp(button);
            }

            static int GetMouseX() {
                return GetMouseX();
            }

            static int GetMouseY() {
                return GetMouseY();
            }

            static Vector2D GetMousePosition() {
                return ::GetMousePosition();
            }

            static Vector2D GetMouseDelta() {
                return GetMouseDelta();
            }

            static void SetMousePosition(int x, int y) {
                ::SetMousePosition(x, y);
            }

            static void SetMouseOffset(int offsetX, int offsetY) {
                ::SetMouseOffset(offsetX, offsetY);
            }

            static void SetMouseScale(float scaleX, float scaleY) {
                ::SetMouseScale(scaleX, scaleY);
            }

            static float GetMouseWheelMove() {
                return ::GetMouseWheelMove();
            }

            static void SetMouseCursor(int cursor) {
                ::SetMouseCursor(cursor);
            }

            static void SetClipboardText(const char* text) {
                ::SetClipboardText(text);
            }

            static const char* GetClipboardText() {
                return ::GetClipboardText();
            }

            int GetTouchX() {
                return ::GetTouchX();
            }

            int GetTouchY() {
                return ::GetTouchY();
            }

            Vector2D GetTouchPosition(int index) {
                return ::GetTouchPosition(index);
            }

            int GetTouchPointId(int index) {
                return ::GetTouchPointId(index);
            }

            int GetTouchPointCount() {
                return ::GetTouchPointCount();
            }

            void SetGesturesEnabled(unsigned int flags) {
                ::SetGesturesEnabled(flags);
            }

            bool IsGestureDetected(int gesture) {
                ::IsGestureDetected(gesture);
            }
            
            int GetGestureDetected() {
                return ::GetGestureDetected();
            }
            
            float GetGestureHoldDuration() {
                return GetGestureHoldDuration();
            }

            Vector2D GetGestureDragVector() {
                return ::GetGestureDragVector();
            }

            float GetGestureDragAngle() {
                return ::GetGestureDragAngle();
            }

            Vector2D GetGesturePinchVector() {
                return ::GetGesturePinchVector();
            }

            float GetGesturePinchAngle() {
                return ::GetGesturePinchAngle();
            }
        };
    }
}

#endif
