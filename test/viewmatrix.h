#pragma once

struct viewmatrix
{
	float* operator[ ](int index) {
		return matrix[index];
	}

	float matrix[4][4];
};
