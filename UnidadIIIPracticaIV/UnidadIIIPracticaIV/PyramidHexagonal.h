#pragma once

#include <GL/glut.h>
#include <cmath>
#include "Shapes3d.h"
#include "Vertex3d.h"
#include "Color.h"

// ------- CLASE HIJA / PYRAMID HEXAGONAL -----------------------------
class PyramidHexagonal : public Shapes3d
{
	// ----- ATRIBUTOS PERTENECIENTES A PYRAMID HEXAGONAL-----
private:
	Vertex3d vertexPos[7];			// NUMERO DE VERTICES
	Color colors[7];				// NUMERO DE COLORES DE CARAS
	double side;					// DIMENSION DEL LADO DE BASE
	double height;					// DIMENSION DE ALTURA DE PIRAMIDE
	double apothem;

public:
	PyramidHexagonal()
	{
		setOrigin(0, 0, 0);
		setColor(1);
		setSide(1);
		setHeight(1);
		setNumVertex(7);
		calculateVertex();
	}

	PyramidHexagonal(double _x, double _y, double _z)
	{
		setOrigin(_x, _y, _z);
		setColor(1);
		setSide(1);
		setHeight(1);
		setNumVertex(7);
		calculateVertex();
	}

	PyramidHexagonal(double _x, double _y, double _z, double _side, double _height)
	{
		setOrigin(_x, _y, _z);
		setColor(1);
		setSide(_side);
		setHeight(_height);
		setNumVertex(7);
		calculateVertex();
	}

	PyramidHexagonal(double _x, double _y, double _z, double _side, double _height, int _col)
	{
		setOrigin(_x, _y, _z);
		setColor(_col);
		setSide(_side);
		setHeight(_height);
		setNumVertex(7);
		calculateVertex();
	}

	PyramidHexagonal(const PyramidHexagonal& pyramidhexagonal)
	{
		Vertex3d pos = pyramidhexagonal.getOrigin();
		setOrigin(pos.getX(), pos.getY(), pos.getZ());
		setColor(pyramidhexagonal.getNumColor());
		setSide(pyramidhexagonal.getSide());
		setHeight(pyramidhexagonal.getHeight());
		setNumVertex(7);
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
			colors[6].setRGB(1.0, 1.0, 0.50);	
			break;
		case 2:
			colors[0].setRGB(1.0, 0.0, 1.0);	colors[1].setRGB(1.0, 0.0, 0.0);
			colors[2].setRGB(0.0, 0.0, 0.75);	colors[3].setRGB(0.0, 1.0, 1.0);
			colors[4].setRGB(1.0, 0.75, 0.75);	colors[5].setRGB(0.75, 1.0, 1.0);
			colors[6].setRGB(0.50, 1.0, 1.0);	
			break;
		case 3:
			colors[0].setRGB(0.5, 0.5, 0.5);	colors[1].setRGB(0.9, 0.8, 0.7);
			colors[2].setRGB(0.6, 0.5, 0.4);	colors[3].setRGB(1.0, 1.0, 0.75);
			colors[4].setRGB(0.75, 1.0, 1.0);	colors[5].setRGB(1.0, 0.75, 1.0);
			colors[6].setRGB(1.0, 0.50, 1.0);
			break;
		case 4:
			for (int i = 0; i < getNumVertex(); i++) { colors[i].setRGB(1.0, 0.0, 0.0); }
			break;
		case 5:
			for (int i = 0; i < getNumVertex(); i++) { colors[i].setRGB(0.0, 1.0, 0.0); }
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

	void setSide(double _side)
	{
		if (_side > 0) { side = _side; }
		else { setSide(1); }
		apothem = (getSide() / 2) * sqrt(3.0);
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

	double getSide()	const { return side; }
	double getHeight()	const { return height; }
	double getApothem() const { return apothem; }

	//double calculatePerimeter() { return getDimension() * 12; }
	//double calculateArea() { return (getDimension() * getDimension()) * 6; }
	//double calculateVolume() { return (getDimension() * getDimension() * getDimension()); }

	void setVertex(double _x1, double _y1, double _z1, double _apothem)
	{
		double _x2 = _x1 + getSide();
		double _x3 = origin.getX() + getSide();
		double _x4 = origin.getX() - getSide();
		double _y2 = _y1 + 2 * _apothem;
		vertexPos[0].setXYZ(_x1, _y1, _z1);
		vertexPos[1].setXYZ(_x2, _y1, _z1);
		vertexPos[2].setXYZ(_x3, _y1 + _apothem, _z1);
		vertexPos[3].setXYZ(_x2, _y2, _z1);
		vertexPos[4].setXYZ(_x1, _y2, _z1);
		vertexPos[5].setXYZ(_x4, _y1 + _apothem, _z1);
		vertexPos[6].setXYZ(origin.getX(), origin.getY(), _z1 + getHeight());
	}

	void calculateVertex()
	{
		double x1 = origin.getX() - (getSide() / 2);
		double y1 = origin.getY() - getApothem();
		double z1 = origin.getZ();
		double hypotenuse = sqrt(pow(getApothem(), 2) + pow((getSide() / 2), 2.0));
		setVertex(x1, y1, z1, getApothem());
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
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glEnd();

		aux_color = colors[2];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glEnd();

		aux_color = colors[3];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glEnd();

		aux_color = colors[4];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glEnd();

		aux_color = colors[5];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glEnd();

		aux_color = colors[6];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glEnd();
	}

	void moveFigure(double _x, double _y, double _z)
	{
		origin.moveVertex3d(_x, _y, _z);
		calculateVertex();
	}

	void scaleFigure(double factor)
	{
		setSide(factor * getSide());
		setHeight(factor * getHeight());
		calculateVertex();
	}
};
