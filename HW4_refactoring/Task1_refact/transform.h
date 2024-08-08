#pragma once
#include"shape.h"
class transform
{
public:
	transform(const Shape& sh, int nmbr_of_vrtx);

	Shape shift(int shift_x, int shift_y, int shift_z);
	Shape scaleX(int mult);
	Shape scaleY(int mult);
	Shape scaleZ(int mult);
	Shape scale(int mult);

private:
	Shape shape;
	int nmbr_of_vrtx{};
	//bool D3;
};