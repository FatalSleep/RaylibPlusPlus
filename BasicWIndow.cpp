#include <RaylibPlus.hpp>

#ifdef _WIN32
int __stdcall wWinMain(void* hInstance, void* hPrevInstance, char* cmdLine, int show)
#else
int main(int argc, char* argv[])
#endif
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    raylib::cpp::Window::Init(screenWidth, screenHeight, "raylib [core] example - basic window");
    raylib::cpp::Window::SetTargetFPS(144);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!raylib::cpp::Window::ShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        raylib::cpp::Window::BeginDrawing();

        raylib::cpp::Window::ClearBackground(RAYWHITE);

        raylib::cpp::Font::DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        raylib::cpp::Window::EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    raylib::cpp::Window::Close();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
