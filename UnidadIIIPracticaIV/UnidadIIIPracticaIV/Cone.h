#pragma once

#include <GL/glut.h>
#include "Shapes3d.h"
#include "Vertex3d.h"
#include "Color.h"


class Cone : public Shapes3d
{
private:
	const double pi = 3.1416;
	Vertex3d top;					// VERTICE DE LA PUNTA
	Vertex3d center;				// CENTRO DEL CIRCULO
	Color colors[2];				// NUMERO DE COLORES DE CARAS
	double height;					// ALTURA DEL CONO
	double radius;					// RADIO DEL CIRCULO DE LA BASE
	double hypotenuse;				// HIPOTENUSA ENTRE LA ALTURA Y EL RADIO

public:
	Cone() {
		setOrigin(0, 0, 0);
		setColor(1);
		setHeight(1);
		setRadius(1);
		calculateVertex();
	}

	Cone(double x, double y, double z) {
		setOrigin(x, y, z);
		setColor(1);
		setHeight(1);
		setRadius(1);
		calculateVertex();
	}

	Cone(double x, double y, double z, double rad) {
		setOrigin(x, y, z);
		setColor(1);
		setHeight(1);
		setRadius(rad);
		calculateVertex();
	}

	Cone(double x, double y, double z, double rad, double height) {
		setOrigin(x, y, z);
		setColor(1);
		setHeight(height);
		setRadius(rad);
		calculateVertex();
	}

	Cone(double x, double y, double z, double rad, double height, int col) {
		setOrigin(x, y, z);
		setColor(col);
		setHeight(height);
		setRadius(rad);
		calculateVertex();
	}

	Cone(const Cone& cone) {
		Vertex3d pos = cone.getOrigin();
		setOrigin(pos.getX(), pos.getY(), pos.getZ());
		setColor(cone.getNumColor());
		setHeight(cone.getHeight());
		setRadius(cone.getRadius());
		calculateVertex();
	}

	void setHeight(double _height) {
		if (_height > 0) {
			height = _height;
		}
		else {
			height = 1;
		}
		
		assignProperties();
	}

	void setRadius(double _radius) {
		if (_radius > 0) {
			radius = _radius;
		}
		else {
			radius = 1;
		}

		assignProperties();
	}

	double getHeight() const {
		return height;
	}

	double getRadius() const {
		return radius;
	}

	void setColor(int colorNumber)
	{
		numColor = colorNumber;
		switch (colorNumber)
		{
		case 1:
			colors[0].setRGB(1.0, 1.0, 0.0);	colors[1].setRGB(0.0, 1.0, 1.0);
			break;
		case 2:
			colors[0].setRGB(1.0, 0.0, 1.0);		colors[1].setRGB(1.0, 0.0, 0.0);
			break;
		case 3:
			colors[0].setRGB(0.5, 0.5, 0.5);		colors[1].setRGB(0.9, 0.8, 0.7);
			break;
		case 4:
			for (int i = 0; i < 2; i++) { colors[i].setRGB(1.0, 0.0, 0.0); }
			break;
		case 5:
			for (int i = 0; i < 2; i++) { colors[i].setRGB(0.0, 1.0, 0.0); }
			break;
		case 6:
			for (int i = 0; i < 2; i++) { colors[i].setRGB(0.0, 0.0, 1.0); }
			break;
		case 7:
			for (int i = 0; i < 2; i++) { colors[i].setRGB(1.0, 1.0, 0.0); }
			break;
		case 8:
			for (int i = 0; i < 2; i++) { colors[i].setRGB(1.0, 0.0, 1.0); }
			break;
		case 9:
			for (int i = 0; i < 2; i++) { colors[i].setRGB(0.0, 1.0, 1.0); }
			break;
		default:
			numColor = 0;
			for (int i = 0; i < 2; i++) { colors[i].setRGB(0.0, 0.0, 0.0); }
			break;
		}
	}

	void assignProperties()
	{
		area = calculateArea();
		volume = calculateVolume();
		calculateVertex();
	}

	double calculateArea() {
		return ((pi * radius) * (radius + hypotenuse)); 
	}
	double calculateVolume() { return ((pi * pow(radius, 2) * height) / 3); }

	void setVertex(double _x1, double _y1, double _z1, double rad, double hg)
	{
		top.setXYZ(_x1, _y1+hg, _z1);
		center.setXYZ(_x1, _y1, _z1);
	}

	void calculateVertex()
	{
		Vertex3d aux_origin = getOrigin();
		double x1 = aux_origin.getX();
		double y1 = aux_origin.getY();
		double z1 = aux_origin.getZ();
		setVertex(x1, y1, z1, getRadius(), getHeight());
	}

	void drawFigure()
	{
		Vertex3d vertexCollection[360];
		Color aux_color = colors[0];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		Vertex3d aux_pos = center;
		
		int circle_points = 360;
		glBegin(GL_POLYGON);
		
		for (int i = 0; i < circle_points; i++)
		{
			float angle = 2 * pi * float(i) / circle_points;
			vertexCollection[i].setXYZ(aux_pos.getX() + getRadius() * cos(angle),0, aux_pos.getY() + getRadius() * sin(angle));
			glVertex3f(aux_pos.getX() + getRadius() * cos(angle), 0,aux_pos.getY() + getRadius() * sin(angle));
		}
		glEnd();
		
		aux_color = colors[1];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		for (int i = 0, j = 1; i < circle_points; i++, j++)
		{
			if (i == 359) {j = 0;}
			glBegin(GL_POLYGON);
			glVertex3f(vertexCollection[i].getX(), vertexCollection[i].getY(), vertexCollection[i].getZ());
			glVertex3f(top.getX(), top.getY(), top.getZ());
			glVertex3f(vertexCollection[j].getX(), vertexCollection[j].getY(), vertexCollection[j].getZ());
			glEnd();
		}
	}

	void moveFigure(double _x, double _y, double _z)
	{
		origin.moveVertex3d(_x, _y, _z);
		calculateVertex();
	}

	void scaleFigure(double factor)
	{
		setHeight(factor * getHeight());
		setRadius(factor * getRadius());
		calculateVertex();
	}
};
