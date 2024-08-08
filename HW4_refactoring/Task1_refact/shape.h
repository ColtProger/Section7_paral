#pragma once
#include<string>
#include<vector>
struct coord {
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> z;
};

enum figures
{
	line,
	square,
	cube,
	circle,
	cilinder
};
class Shape
{
protected:

	int fig_type;
	

public:
	double volume;
	double square;
	coord vertexes;
	bool dim;

	virtual int getType(); 
	virtual bool getDimension();
};


class Line : public Shape {
protected:
	coord vert;


public:
	Line(coord& vert);	
};

class Square : public Shape {
protected:
	
	coord vertexes;
	

public:
	Square(coord& vertexes);

};

class Cube : public Shape {
protected:
	coord vertexes;

public:

	Cube(coord& vertexes); 
};

class Circle : public Shape {
protected:
	coord center;
public:
	Circle(coord& center, double radius);
};

class Cilinder : public Shape {
protected:
	coord center;
public:
	Cilinder(coord& center, double radius, double height);
};

