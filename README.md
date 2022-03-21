# RaylibPP
C++ wrapper for Raylib that falls under the namespace: `raylib -> cpp`.

Raylib: https://www.raylib.com

Raylib Cheatsheet: https://www.raylib.com/cheatsheet/cheatsheet.html

Additional header-only libraries:
```
Invokable.hpp (thread safe verion) - https://github.com/FatalSleep/Event-Callback
```

Raymath: https://github.com/raysan5/raylib/blob/master/src/raymath.h

`Vector.hpp` Wraps the Raymath library into a set of C++ classes that directly replace and cast to the Raylib math structs: `Vector2, Vector3, Vector4, Matrix & Quaternion`. Also includes a static class `RayMath` for help functions: `Clamp, Lerp, Normalize & Remap`. Functional usage is completely identical to Raymath with the exception that both the structs AND fucntions are wrapped into their respective class. The Vector/Quaternion classes now have the following inheritance hierarchy: `Quaternion -> Vector4`, `Vector4 -> Vector3 -> Vector2`. Several functions that provide a conversion say from Matrix to Quaternion or vice versa have dual-implementations, one static and one for the class object to clone that passed object.

Colors in RTextures: https://github.com/raysan5/raylib/blob/master/src/rtextures.c

`Colors.hpp` Wraps the Color functions/struct in the `rtextures.c` and `raylib.c` libraries into a complete color handling class. Please reference the `Color/pixel related functions` subsection of the module: textures section of the raylib cheatsheet. Not all of the functions have been implemented directly but their functionality is there, for example `ColorToInt` is not a function, but the `Colors` class auto-casts to an Int in RGBA format. The `Colors` class can also cast directly to raylib `Color` struct and back. There are static implementations for convenience for the following three functions: `GetPixel, SetPixel & GetPixelDataSize`, however proper implementations have been moved into the Textures class.
