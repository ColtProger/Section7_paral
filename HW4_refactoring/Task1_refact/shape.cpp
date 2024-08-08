#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>

int Shape::getType() {
	return fig_type;
};

bool Shape::getDimension() {
	return dim;
};


Line::Line(coord& vert) : Shape() {
	dim = false;
	fig_type = figures::line;
	square = 0;
	volume = 0;
};

Square::Square(coord& vertexes) : vertexes(vertexes){
	dim = false;
	fig_type = figures::square;

	double a = abs(vertexes.x[0] - vertexes.x[1]);
	double b = abs(vertexes.y[0] - vertexes.y[1]);
	
	square = a * b;
	volume = 0;

};

Cube::Cube(coord& vertexes) : vertexes(vertexes) {
	dim = true;
	fig_type = figures::cube;

	double a = abs(vertexes.x[0] - vertexes.x[1]);
	double b = abs(vertexes.y[0] - vertexes.y[1]);
	double c = abs(vertexes.z[0] - vertexes.z[1]);

	square = 2 * a * b + 2 * a * c + 2 * b * c;
	volume = a * b * c;
};

Circle::Circle(coord& center, double radius) {

	fig_type = figures::circle;

	square = M_PI * radius * radius;
	volume = 0;
};

Cilinder::Cilinder(coord& center, double radius, double height) {
	fig_type = figures::cilinder;
	square = 2 * M_PI * radius * radius + 2 * M_PI * radius * height;
	volume = M_PI * radius * radius * height;
};