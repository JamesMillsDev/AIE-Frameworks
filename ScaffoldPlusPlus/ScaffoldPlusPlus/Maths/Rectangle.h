#pragma once

#include "../ScaffoldPlusPlus.h"

#include <raylib.h>

struct Rect
{
	float x, y;
	float width, height;

	SPP_DLL Rect(float _x, float _y, float _width, float _height);

	SPP_DLL float Area();
	SPP_DLL Vector2 GetPosition();
	SPP_DLL Vector2 GetSize();
	SPP_DLL Rectangle ToRaylib();

};