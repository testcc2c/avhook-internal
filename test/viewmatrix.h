#pragma once
#include "Vec3.h"
struct viewmatrix
{
	float* operator[ ](int index) {
		return matrix[index];
	}

	float matrix[4][4];
};

Vec3 WorldToScreen(const Vec3 pos, viewmatrix matrix) 
{	float _x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
	float _y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];

	float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];

	float inv_w = 1.f / w;
	_x *= inv_w;
	_y *= inv_w;

	float x = 640 * .5f;
	float y = 480 * .5f;

	x += 0.5f * _x * 640 + 0.5f;
	y -= 0.5f * _y * 480 + 0.5f;

	return { x,y,w };
}