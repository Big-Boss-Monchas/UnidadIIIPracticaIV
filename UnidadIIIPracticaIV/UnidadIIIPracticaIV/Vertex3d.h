#pragma once
#include <cmath>

// CLASE DE VERTICE EN 3D ----------------------
class Vertex3d
{
	
// ATRIBUTOS COORDENADA X, Y, Z ----------------	
private:
	double x;
	double y;
	double z;

public:
	// CONSTRUCTORES -----------------------
	Vertex3d()
	{
		setX(0);
		setY(0);
		setZ(0);
	}

	Vertex3d(double _x, double _y, double _z)
	{
		setX(_x);
		setY(_y);
		setZ(_z);
	}

	// GETTERS & SETTERS --------------------
	double getX()
	{
		return x;
	}

	double getY()
	{
		return y;
	}

	double getZ()
	{
		return z;
	}

	void setX(double _x)
	{
		x = _x;
	}

	void setY(double _y)
	{
		y = _y;
	}

	void setZ(double _z)
	{
		z = _z;
	}
	
	// METODO ASIGNA LAS TRES COORDENADAS A LA VEZ
	void setXYZ(double _x, double _y, double _z)
	{
		setX(_x);
		setY(_y);
		setZ(_z);
	}
	
	// METODO PARA MOVER LA COORDENADA DEL VERTICE
	void moveVertex3d(double _x, double _y, double _z)
	{
		setX(getX() + _x);
		setY(getY() + _y);
		setZ(getZ() + _z);
	}

	/*void scaleVertex3d(double _x, double _y, double _z)
	{
	setX(getX() * _x);
	setY(getY() * _y);
	setZ(getZ() * _z);
	}*/
	/*
	void rotateVertex3d(double _x, double _y, double _z)
	{

	}
	*/
};
