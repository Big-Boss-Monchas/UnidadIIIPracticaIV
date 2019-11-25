#pragma once

#include <GL/glut.h>
#include "Vertex3d.h"

// ------- CLASE PRINCIPAL SHAPES3D--------------------------------
class Shapes3d
{
	// ----- ATRIBUTOS DE LAS FIGURAS -------------------------
protected:
	Vertex3d origin;
	int numColor;
	int numVertex;
	double perimeter;
	double area;
	double volume;

	// ----- GETTERS & SETTERS -------------------------------
	// ALGUNAS SON VIRTUALES DEBIDO A QUE SERAN IMPLEMENTADAS
	// EN LA CLASE HIJA --------------------------------------
public:

	// GETTERS & SETTERS--------------------------------------
	
	// ESTABLECE EL ORIGEN DE LA FIGURA
	void setOrigin(double _x, double _y, double _z)
	{
		origin.setX(_x);
		origin.setY(_y);
		origin.setZ(_z);
	}

	void setNumVertex(int _numVertex) { numVertex = _numVertex; }

	Vertex3d getOrigin() const { return origin; }
	int getNumColor() const { return numColor; }
	int getNumVertex() const { return numVertex; }
	double getPerimeter() const { return perimeter; }
	double getArea() const { return area; }
	double getVolume() const { return volume; }

	// --- METODOS DE LAS FIGURAS ---------------------------
	//virtual double calculateArea() = 0;
	//virtual double calculatePerimeter() = 0;
	//virtual double calculateVolume() = 0;
	//virtual void assignProperties() = 0;
	//virtual void drawFigure() = 0;
	//virtual void moveFigure() = 0;
	//virtual void scaleFigure() = 0;
};
