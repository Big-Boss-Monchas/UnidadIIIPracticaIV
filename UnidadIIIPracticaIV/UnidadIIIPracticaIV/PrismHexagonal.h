#pragma once

#include <GL/glut.h>
#include <cmath>
#include "Shapes3d.h"
#include "Vertex3d.h"
#include "Color.h"

// ------- CLASE HIJA / PRISM HEXAGONAL -----------------------------
class PrismHexagonal : public Shapes3d
{
	// ----- ATRIBUTOS PERTENECIENTES A PRISM HEXAGONAL -----
private:
	Vertex3d vertexPos[12];				// NUMERO DE VERTICES
	Color colors[8];				// NUMERO DE COLORES DE CARAS
	double base;					// DIMENSION DEL LADO DE BASE
	double height;					// DIMENSION DE ALTURA DE PRISMA
	double apothem;

public:
	PrismHexagonal()
	{
		setOrigin(0, 0, 0);
		setColor(1);
		setBase(1);
		setHeight(1);
		setNumVertex(12);
		calculateVertex();
	}

	PrismHexagonal(double _x, double _y, double _z)
	{
		setOrigin(_x, _y, _z);
		setColor(1);
		setBase(1);
		setHeight(1);
		setNumVertex(12);
		calculateVertex();
	}

	PrismHexagonal(double _x, double _y, double _z, double _base, double _height)
	{
		setOrigin(_x, _y, _z);
		setColor(1);
		setBase(_base);
		setHeight(_height);
		setNumVertex(12);
		calculateVertex();
	}

	PrismHexagonal(double _x, double _y, double _z, double _base, double _height, int _col)
	{
		setOrigin(_x, _y, _z);
		setColor(_col);
		setBase(_base);
		setHeight(_height);
		setNumVertex(12);
		calculateVertex();
	}

	PrismHexagonal(const PrismHexagonal& prismhexagonal)
	{
		Vertex3d pos = prismhexagonal.getOrigin();
		setOrigin(pos.getX(), pos.getY(), pos.getZ());
		setColor(prismhexagonal.getNumColor());
		setBase(prismhexagonal.getBase());
		setHeight(prismhexagonal.getHeight());
		setNumVertex(12);
		calculateVertex();
	}

	void setColor(int colorNumber)
	{
		numColor = colorNumber;
		switch (colorNumber)
		{
		case 1:
			colors[0].setRGB(1.0, 1.0, 0.0);	colors[1].setRGB(0.0, 1.0, 1.0);
			colors[2].setRGB(1.0, 0.0, 1.0);	colors[3].setRGB(1.0, 0.0, 0.0);
			colors[4].setRGB(0.0, 1.0, 0.0);	colors[5].setRGB(0.0, 0.0, 1.0);
			colors[6].setRGB(0.30, 0.40, 1.0);	colors[7].setRGB(0.40, 1.0, 0.30);
			break;
		case 2:
			colors[0].setRGB(1.0, 0.0, 1.0);	colors[1].setRGB(1.0, 0.0, 0.0);
			colors[2].setRGB(0.0, 0.0, 0.75);	colors[3].setRGB(0.0, 1.0, 1.0);
			colors[4].setRGB(1.0, 0.75, 0.75);	colors[5].setRGB(0.75, 1.0, 1.0);
			colors[6].setRGB(0.80, 0.20, 1.0);	colors[7].setRGB(0.80, 1.0, 0.60);
			break;
		case 3:
			colors[0].setRGB(0.5, 0.5, 0.5);	colors[1].setRGB(0.9, 0.8, 0.7);
			colors[2].setRGB(0.6, 0.5, 0.4);	colors[3].setRGB(1.0, 1.0, 0.75);
			colors[4].setRGB(0.75, 1.0, 1.0);	colors[5].setRGB(1.0, 0.75, 1.0);
			colors[6].setRGB(0.20, 0.0, 0.40);	colors[7].setRGB(0.90, 0.0, 0.50);
			break;
		case 4:
			for (int i = 0; i < getNumVertex() - 4; i++) { colors[i].setRGB(1.0, 0.0, 0.0); }
			break;
		case 5:
			for (int i = 0; i < getNumVertex() - 4; i++) { colors[i].setRGB(0.0, 1.0, 0.0); }
			break;
		case 6:
			for (int i = 0; i < getNumVertex() - 4; i++) { colors[i].setRGB(0.0, 0.0, 1.0); }
			break;
		case 7:
			for (int i = 0; i < getNumVertex() - 4; i++) { colors[i].setRGB(1.0, 1.0, 0.0); }
			break;
		case 8:
			for (int i = 0; i < getNumVertex() - 4; i++) { colors[i].setRGB(1.0, 0.0, 1.0); }
			break;
		case 9:
			for (int i = 0; i < getNumVertex() - 4; i++) { colors[i].setRGB(0.0, 1.0, 1.0); }
			break;
		default:
			numColor = 0;
			for (int i = 0; i < getNumVertex() - 4; i++) { colors[i].setRGB(0.0, 0.0, 0.0); }
			break;
		}
	}

	void setBase(double _base)
	{
		if (_base > 0) { base = _base; }
		else { setBase(1); }
		apothem = (getBase() / 2) * sqrt(3.0);
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
		//perimeter = calculatePerimeter();
		//area = calculateArea();
		//volume = calculateVolume();
		calculateVertex();
	}

	double getBase()	const { return base; }
	double getHeight()	const { return height; }
	double getApothem() const { return apothem; }

	//double calculatePerimeter() { return getDimension() * 12; }
	//double calculateArea() { return (getDimension() * getDimension()) * 6; }
	//double calculateVolume() { return (getDimension() * getDimension() * getDimension()); }

	void setVertex(double _x1, double _x2, double _x3, double _x4, double _y1,
		double _y2, double _y3, double _z1, double _z2)
	{
		vertexPos[0].setXYZ(_x1, _y1, _z1);
		vertexPos[1].setXYZ(_x2, _y1, _z1);
		vertexPos[2].setXYZ(_x3, _y2, _z1);
		vertexPos[3].setXYZ(_x2, _y3, _z1);
		vertexPos[4].setXYZ(_x1, _y3, _z1);
		vertexPos[5].setXYZ(_x4, _y2, _z1);
		vertexPos[6].setXYZ(_x1, _y1, _z2);
		vertexPos[7].setXYZ(_x2, _y1, _z2);
		vertexPos[8].setXYZ(_x3, _y2, _z2);
		vertexPos[9].setXYZ(_x2, _y3, _z2);
		vertexPos[10].setXYZ(_x1, _y3, _z2);
		vertexPos[11].setXYZ(_x4, _y2, _z2);
	}

	void calculateVertex()
	{
		double ap = getApothem();
		double _base = getBase();
		double x1 = origin.getX() - (_base / 2);
		double y1 = origin.getY() - ap;
		double z1 = origin.getZ();
		double hypotenuse = sqrt(pow(ap, 2.0) + pow((_base / 2), 2.0));
		double x2 = x1 + _base;
		double x3 = origin.getX() + _base;
		double x4 = origin.getX() - _base;
		double y3 = y1 + 2 * ap;
		double y2 = y1 + ap;
		double z2 = z1 + getHeight();
		setVertex(x1, x2, x3, x4, y1, y2, y3, z1, z2);
	}

	void drawFigure()
	{
		Color aux_color = colors[0];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glEnd();

		aux_color = colors[1];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glEnd();

		aux_color = colors[2];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glVertex3f(vertexPos[8].getX(), vertexPos[8].getY(), vertexPos[8].getZ());
		glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
		glEnd();

		aux_color = colors[3];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glVertex3f(vertexPos[9].getX(), vertexPos[9].getY(), vertexPos[9].getZ());
		glVertex3f(vertexPos[8].getX(), vertexPos[8].getY(), vertexPos[8].getZ());
		glEnd();

		aux_color = colors[4];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glVertex3f(vertexPos[10].getX(), vertexPos[10].getY(), vertexPos[10].getZ());
		glVertex3f(vertexPos[9].getX(), vertexPos[9].getY(), vertexPos[9].getZ());
		glEnd();

		aux_color = colors[5];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[11].getX(), vertexPos[11].getY(), vertexPos[11].getZ());
		glVertex3f(vertexPos[10].getX(), vertexPos[10].getY(), vertexPos[10].getZ());
		glEnd();

		aux_color = colors[6];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glVertex3f(vertexPos[11].getX(), vertexPos[11].getY(), vertexPos[11].getZ());
		glEnd();

		aux_color = colors[7];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
		glVertex3f(vertexPos[8].getX(), vertexPos[8].getY(), vertexPos[8].getZ());
		glVertex3f(vertexPos[9].getX(), vertexPos[9].getY(), vertexPos[9].getZ());
		glVertex3f(vertexPos[10].getX(), vertexPos[10].getY(), vertexPos[10].getZ());
		glVertex3f(vertexPos[11].getX(), vertexPos[11].getY(), vertexPos[11].getZ());
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
