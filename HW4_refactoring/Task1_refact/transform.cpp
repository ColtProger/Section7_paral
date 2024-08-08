#include "transform.h"

transform::transform(const Shape& sh, int nmbr_of_vrtx)
{
	shape = sh;
	nmbr_of_vrtx = nmbr_of_vrtx;
}

Shape transform::shift(int shift_x, int shift_y, int shift_z)
{
	for (int i = 0; i < nmbr_of_vrtx; i++) {
		shape.vertexes.x[i] += shift_x;
		shape.vertexes.y[i] += shift_x;
		if (shape.dim) {
			shape.vertexes.z[i] += shift_z;
		}
  
	}
	
	return shape;
}

Shape transform::scaleX(int mult)
{
	for (int i = 0; i < nmbr_of_vrtx; i++) {
		shape.vertexes.x[i] *= mult;
	}

	return shape;
}
Shape transform::scaleY(int mult)
{
	for (int i = 0; i < nmbr_of_vrtx; i++) {
		shape.vertexes.y[i] *= mult;
	}

	return shape;
}
Shape transform::scaleZ(int mult)
{
	for (int i = 0; i < nmbr_of_vrtx; i++) {
		shape.vertexes.z[i] *= mult;
	}

	return shape;
}

Shape transform::scale(int mult)
{
	for (int i = 0; i < nmbr_of_vrtx; i++) {
		shape.vertexes.x[i] /= mult;
		shape.vertexes.y[i] /= mult;
		if (shape.dim) {
			shape.vertexes.z[i] += mult;
		}

	}

	return shape;
}

/* Shape transform::scaleX(int a)
{
//	switch (shape.getType())
//	{
	case Shape::line:
		shape.x1 *= a;
		shape.x2 *= a;
		break;
	case Shape::sqr:
		shape.x1 *= a;
		shape.x2 *= a;
		shape.x3 *= a;
		shape.x4 *= a;
		break;
	case Shape::cube:
		shape.x1 *= a;
		shape.x2 *= a;
		shape.x3 *= a;
		shape.x4 *= a;
		shape.x5 *= a;
		shape.x6 *= a;
		shape.x7 *= a;
		shape.x8 *= a;
		break;
	}
	return shape;
}

Shape transform::scaleY(int d)
{
	switch (shape.getType())
	{
	case Shape::line:
		shape.y1 *= d;
		shape.y2 *= d;
		break;
	case Shape::sqr:
		shape.y1 *= d;
		shape.y2 *= d;
		shape.y3 *= d;
		shape.y4 *= d;
		break;
	case Shape::cube:
		shape.y1 *= d;
		shape.y2 *= d;
		shape.y3 *= d;
		shape.y4 *= d;
		shape.y5 *= d;
		shape.y6 *= d;
		shape.y7 *= d;
		shape.y8 *= d;
		break;
	}
	return shape;
}

Shape transform::scaleZ(int e)
{
	switch (shape.getType())
	{
	case Shape::line:
		shape.z1 *= e;
		shape.z2 *= e;
		break;
	case Shape::sqr:
		shape.z1 *= e;
		shape.z2 *= e;
		shape.z3 *= e;
		shape.z4 *= e;
		break;
	case Shape::cube:
		shape.z1 *= e;
		shape.y2 *= e;
		shape.z3 *= e;
		shape.z4 *= e;
		shape.z5 *= e;
		shape.z6 *= e;
		shape.z7 *= e;
		shape.z8 *= e;
		break;
	}
	return shape;
}

Shape transform::scale(int s)
{
	switch (shape.getType())
	{
	case Shape::line:
		shape.x1 /= s; shape.y1 /= s;
		shape.x2 /= s; shape.y2 /= s;
		break;
	case Shape::sqr:
		shape.x1 /= s; shape.y1 /= s;
		shape.x2 /= s; shape.y2 /= s;
		shape.x3 /= s; shape.y3 /= s;
		shape.x4 /= s; shape.y4 /= s;
		break;
	case Shape::cube:
		shape.x1 /= s; shape.y1 /= s; shape.z1 /= s;
		shape.x2 /= s; shape.y2 /= s; shape.z2 /= s;
		shape.x3 /= s; shape.y3 /= s; shape.z3 /= s;
		shape.x4 /= s; shape.y4 /= s; shape.z4 /= s;
		shape.x5 /= s; shape.y5 /= s; shape.z5 /= s;
		shape.x6 /= s; shape.y6 /= s; shape.z6 /= s;
		shape.x7 /= s; shape.y7 /= s; shape.z7 /= s;
		shape.x8 /= s; shape.y8 /= s; shape.z8 /= s;
		break;
	}

	return shape;
}*/