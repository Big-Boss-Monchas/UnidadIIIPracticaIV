#pragma once

#include <GL/glut.h>
#include <cmath>
#include "Shapes3d.h"
#include "Vertex3d.h"
#include "Color.h"

// ------- CLASE HIJA / PYRAMID -----------------------------
class PyramidTriangular : public Shapes3d
{
	// ----- ATRIBUTOS PERTENECIENTES A PYRAMID TRIANGULAR-----
private:
	Vertex3d vertexPos[4];	// NUMERO DE VERTICES
	Color colors[4];				// NUMERO DE COLORES DE CARAS
	double base;						// DIMENSION DEL LADO DE BASE
  double height;					// DIMENSION DE ALTURA DE PIRAMIDE

public:
	// PyramidTriangular() {
	// 	setOrigin(0, 0, 0);
	// 	setColor(1);
	// 	setDimension(1);
	// 	setNumVertex(8);
	// 	calculateVertex();
	// }
	//
	// PyramidTriangular(double x, double y, double z) {
	// 	setOrigin(x, y, z);
	// 	setColor(1);
	// 	setDimension(1);
	// 	setNumVertex(8);
	// 	calculateVertex();
	// }
	//
	// PyramidTriangular(double x, double y, double z, double dim) {
	// 	setOrigin(x, y, z);
	// 	setColor(1);
	// 	setDimension(dim);
	// 	setNumVertex(8);
	// 	calculateVertex();
	// }
	//
	// PyramidTriangular(double x, double y, double z, double dim, int col) {
	// 	setOrigin(x, y, z);
	// 	setColor(col);
	// 	setDimension(dim);
	// 	setNumVertex(8);
	// 	calculateVertex();
	// }
	//
	// PyramidTriangular(const PyramidTriangular& pyramidtriangular) {
	// 	Vertex3d pos = pyramidtriangular.getOrigin();
	// 	setOrigin(pos.getX(), pos.getY(), pos.getZ());
	// 	setColor(pyramidtriangular.getColor());
	// 	setDimension(pyramidtriangular.getDimension());
	// 	setNumVertex(8);
	// 	calculateVertex();
	// }

	void setColor(int colorNumber)
	{
		numColor = colorNumber;
		switch (colorNumber)
		{
		case 1:
			   colors[0].setRGB(1.0, 1.0, 0.0);	colors[1].setRGB(0.0, 1.0, 1.0);
			   colors[2].setRGB(1.0, 0.0, 1.0);	colors[3].setRGB(1.0, 0.0, 0.0);
			   break;
		case 2:
			   colors[0].setRGB(1.0, 0.0, 1.0);	colors[1].setRGB(1.0, 0.0, 0.0);
			   colors[2].setRGB(0.0, 0.0, 0.75);	colors[3].setRGB(0.0, 1.0, 1.0);
			   break;
		case 3:
			   colors[0].setRGB(0.5, 0.5, 0.5);	colors[1].setRGB(0.9, 0.8, 0.7);
			   colors[2].setRGB(0.6, 0.5, 0.4);	colors[3].setRGB(1.0, 1.0, 0.75);
			   break;
		case 4:
			   for (int i = 0; i < getNumVertex(); i++) { colors[i].setRGB(1.0, 0.0, 0.0); }
			   break;
		case 5:
			   for (int i = 0; i < getNumVertex(); i++)	{ colors[i].setRGB(0.0, 1.0, 0.0); }
			   break;
		case 6:
			   for (int i = 0; i < getNumVertex(); i++) { colors[i].setRGB(0.0, 0.0, 1.0); }
			   break;
		case 7:
			   for (int i = 0; i < getNumVertex(); i++) { colors[i].setRGB(1.0, 1.0, 0.0); }
			   break;
		case 8:
			   for (int i = 0; i < getNumVertex(); i++) { colors[i].setRGB(1.0, 0.0, 1.0); }
			   break;
		case 9:
			   for (int i = 0; i < getNumVertex(); i++) { colors[i].setRGB(0.0, 1.0, 1.0); }
			   break;
		default:
			numColor = 0;
			for (int i = 0; i < getNumVertex(); i++) { colors[i].setRGB(0.0, 0.0, 0.0); }
			break;
		}
	}

	void setBase(double _base)
	{
		if (_base > 0) { base = _base; }
		else { setBase(1); }
		assignProperties();
	}

	void setHeight(double _height)
	{
		if (_height > 0) { height = _height; }
		else { setHeight(1); }
		assignProperties();
	}

	void assignProperties()
	{
		perimeter = calculatePerimeter();
		area = calculateArea();
		volume = calculateVolume();
	}

	double getBase()	const { return base; }
	double getHeight()	const { return height; }

	//double calculatePerimeter() { return getDimension() * 12; }
	//double calculateArea() { return (getDimension() * getDimension()) * 6; }
	//double calculateVolume() { return (getDimension() * getDimension() * getDimension()); }

	void setVertex(double _x1, double _y1, double _z1, double _b)
	{
		vertexPos[0].setXYZ(_x1, _y1, _z1);
		vertexPos[1].setXYZ(_x1 + _b, _y1, _z1);
		vertexPos[2].setXYZ(_x1 + (_b / 2), origin.getY() + (1 / sqrt(_b)), _z1);
		//vertexPos[2].setXYZ(_x1 + (_b / 2), _y1 + (sqrt(pow(_b,2.0) - (pow((_b/2.0),2.0)))), _z1 + dim);
		vertexPos[3].setXYZ(origin.getX(), origin.getY(), _z1 + getHeight());
	}

	void calculateVertex()
	{
		//Vertex3d aux_origin = getOrigin();
		double x1 = origin.getX() - (getBase() / 2);
		double y1 = origin.getY() - (getHeight() / sqrt(12.0));
		double z1 = origin.getZ();
		setVertex(x1, y1, z1, getBase());
	}

	void drawFigure()
	{
		//glColor3f(1.0, 0.0, 0.0);
		Color aux_color = colors[0];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glEnd();

		aux_color = colors[1];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glEnd();

		aux_color = colors[2];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glEnd();

		aux_color = colors[3];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glEnd();
	}

	void moveFigure(double _x, double _y, double _z)
	{
		origin.moveVertex3d(_x, _y, _z);
		calculateVertex();
	}

	void scaleFigure(double factor)
	{
		setBase(factor * getBase());
		setHeight(factor * getHeight());
		calculateVertex();
	}
};
