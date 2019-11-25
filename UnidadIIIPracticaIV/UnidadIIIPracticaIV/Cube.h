#pragma once

#include <GL/glut.h>
#include "Shapes3d.h"
#include "Vertex3d.h"
#include "Color.h"

// ------- CLASE HIJA / CUBE --------------------------------
class Cube : public Shapes3d
{
	// ----- ATRIBUTOS PERTENECIENTES A CUBO -------------
private:
	Vertex3d vertexPos[8];				// NUMERO DE VERTICES
	Color colors[6];				// NUMERO DE COLORES DE CARAS
	double dimension;				// DIMENSION DEL CUBO

public:

	// ----- CONSTRUCTORES DEL CUBO ---------------------
	Cube() {
		setOrigin(0, 0, 0);
		setColor(1);
		setDimension(1);
		setNumVertex(8);
		calculateVertex();
	}

	Cube(double x, double y, double z) {
		setOrigin(x, y, z);
		setColor(1);
		setDimension(1);
		setNumVertex(8);
		calculateVertex();
	}

	Cube(double x, double y, double z, double dim) {
		setOrigin(x, y, z);
		setColor(1);
		setDimension(dim);
		setNumVertex(8);
		calculateVertex();
	}

	Cube(double x, double y, double z, double dim, int col) {
		setOrigin(x, y, z);
		setColor(col);
		setDimension(dim);
		setNumVertex(8);
		calculateVertex();
	}

	Cube(const Cube& cube) {
		Vertex3d pos = cube.getOrigin();
		setOrigin(pos.getX(), pos.getY(), pos.getZ());
		setColor(cube.getNumColor());
		setDimension(cube.getDimension());
		setNumVertex(8);
		calculateVertex();
	}

	// ----- ESTABLECE LOS COLORES DEPENDIENDO DEL NUMERO DE PARAMETRO --------------------
	// ENTRA A UN SWITCH QUE ASIGNA UN COLOR A CADA ELEMENTO DEL ARREGLO COLOR
	void setColor(int colorNumber)
	{
		numColor = colorNumber;
		switch (colorNumber)
		{
		case 1:
			   colors[0].setRGB(1.0, 1.0, 0.0);	colors[1].setRGB(0.0, 1.0, 1.0);
			   colors[2].setRGB(1.0, 0.0, 1.0);	colors[3].setRGB(1.0, 0.0, 0.0);
			   colors[4].setRGB(0.0, 1.0, 0.0);	colors[5].setRGB(0.0, 0.0, 1.0);
			   break;
		case 2:
			   colors[0].setRGB(1.0, 0.0, 1.0);	colors[1].setRGB(1.0, 0.0, 0.0);
			   colors[2].setRGB(0.0, 0.0, 0.75);	colors[3].setRGB(0.0, 1.0, 1.0);
			   colors[4].setRGB(1.0, 0.75, 0.75);	colors[5].setRGB(0.75, 1.0, 1.0);
			   break;
		case 3:
			   colors[0].setRGB(0.5, 0.5, 0.5);	colors[1].setRGB(0.9, 0.8, 0.7);
			   colors[2].setRGB(0.6, 0.5, 0.4);	colors[3].setRGB(1.0, 1.0, 0.75);
			   colors[4].setRGB(0.75, 1.0, 1.0);	colors[5].setRGB(1.0, 0.75, 1.0);
			   break;
		case 4:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(1.0, 0.0, 0.0); }
			   break;
		case 5:
			   for (int i = 0; i < getNumVertex() - 2; i++)	{ colors[i].setRGB(0.0, 1.0, 0.0); }
			   break;
		case 6:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(0.0, 0.0, 1.0); }
			   break;
		case 7:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(1.0, 1.0, 0.0); }
			   break;
		case 8:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(1.0, 0.0, 1.0); }
			   break;
		case 9:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(0.0, 1.0, 1.0); }
			   break;
		default:
			numColor = 0;
			for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(0.0, 0.0, 0.0); }
			break;
		}
	}
	
	// ----- SETTERS & GETTERS ----------------------------------
	void setDimension(double _dimension)
	{
		if (_dimension > 0) { dimension = _dimension; }
		else { setDimension(1); }
		assignProperties();
	}

	void assignProperties()
	{
		perimeter = calculatePerimeter();
		area = calculateArea();
		volume = calculateVolume();
		calculateVertex();
	}

	double getDimension()	const { return dimension; }

	double calculatePerimeter() { return getDimension() * 12; }
	double calculateArea() { return (getDimension() * getDimension()) * 6; }
	double calculateVolume() { return (getDimension() * getDimension() * getDimension()); }

	// ----- ASIGNA LAS COORDENADAS EN X, Y, Z EN CADA VERTICE DEL CUBO ---------------------
	void setVertex(double _x1, double _y1, double _z1, double dim)
	{
		vertexPos[0].setXYZ(_x1, _y1, _z1);			vertexPos[1].setXYZ(_x1, _y1, _z1 + dim);
		vertexPos[2].setXYZ(_x1, _y1 + dim, _z1 + dim);		vertexPos[3].setXYZ(_x1, _y1 + dim, _z1);
		vertexPos[4].setXYZ(_x1 - dim, _y1, _z1);		vertexPos[5].setXYZ(_x1 - dim, _y1, _z1 + dim);
		vertexPos[6].setXYZ(_x1 - dim, _y1 + dim, _z1 + dim);	vertexPos[7].setXYZ(_x1 - dim, _y1 + dim, _z1);
	}

	// ----- CALCULA LAS COORDENADAS DEL VERTICE INICIAL PARTIENDO DEL CENTRO DEL CUBO COMO ORIGEN -------
	void calculateVertex()
	{
		Vertex3d aux_origin = getOrigin();
		double aux_dimension = getDimension();
		double x1 = aux_origin.getX() + (aux_dimension / 2);
		double y1 = aux_origin.getY() - (aux_dimension / 2);
		double z1 = aux_origin.getZ() - (aux_dimension / 2);
		setVertex(x1, y1, z1, aux_dimension);	// LLAMA LA ASIGNACION DE LOS VERTICES
	}
	
	// DIBUJA LA FIGURA PINTANDO CADA UNA DE LAS CARAS CON DIFERENTE COLOR
	void drawFigure()
	{
		// ----- POR CADA CARA TOMA EL COLOR DEL ARREGLO ---------------------
		Color aux_color = colors[0];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		for (int i = 0; i < getNumVertex() / 2; i++)
		{
			glVertex3f(vertexPos[i].getX(), vertexPos[i].getY(), vertexPos[i].getZ());
		}
		glEnd();

		aux_color = colors[1];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glEnd();

		aux_color = colors[2];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glEnd();

		aux_color = colors[3];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glEnd();

		aux_color = colors[4];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
		glEnd();

		aux_color = colors[5];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glEnd();
	}

	void moveFigure(double _x, double _y, double _z)
	{
		origin.moveVertex3d(_x, _y, _z);
		calculateVertex();
	}

	void scaleFigure(double factor)
	{
		setDimension(factor * getDimension());
		calculateVertex();
	}
};
