/**
 * RaylibPP is a header-only library wrapper around RayLib's C-struct interface.
 * C++ header provides object-oriented wrappers around raylib's struct interfaces.
 *
 * @see raylib/cpp for available classes & functions.
 * @author Rob Loach (RobLoach)
 * @copyright zlib/libpng
 *
 *   RaylibPP is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software:
 *
 *   Copyright 2022 Alexander Griffis (Yaazarai)
 *
 *   This software is provided "as-is", without any express or implied warranty. In no event
 *   will the authors be held liable for any damages arising from the use of this software.
 *
 *   Permission is granted to anyone to use this software for any purpose, including commercial
 *   applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not claim that you
 *     wrote the original software. If you use this software in a product, an acknowledgment
 *     in the product documentation would be appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be misrepresented
 *     as being the original software.
 *
 *     3. This notice may not be removed or altered from any source distribution.
 */
#pragma once
#ifndef RAYLIB_PLUSPLUS
#define RAYLIB_PLUSPLUS
	#include "./RaylibExtern.hpp"
	#include "./Colors.hpp"
	#include "./Vector.hpp"

	/// NON-RAYLIB ADDITIONS ///
	#include "./Invokable.hpp" // For event/callback invokation.

namespace raylib {
	namespace cpp {

	}
}

#endif
