#pragma once

// CLASE PERTENECIENTE A LOS COLORES EN RGB
class Color
{
	// ATRIBUTOS COLOR RED, GREEN, BLUE -------
	private:
		float colorR;
		float colorG;
		float colorB;

	public:
		// CONSTRUCTORES ------------------
		Color()
		{
			colorR = 1.0;
			colorG = 1.0;
			colorB = 1.0;
		}

		Color(float _r, float _g, float _b)
		{
			setR(_r);
			setG(_g);
			setB(_b);
		}
		
		// GETTERS & SETTERS --------------
		float getR()
		{
			return colorR;
		}

		float getG()
		{
			return colorG;
		}

		float getB()
		{
			return colorB;
		}

		// SI EL VALOR ENVIADO ES MENOR A 0 O MAYOR A 1 
		// LE ES ASIGNADO EL VALOR DE 1.0 POR DEFECTO
		void setR(float _r)
		{
			if (_r >= 0 && _r <= 1)
			{
				colorR = _r;
			}
			else
			{
				colorR = 1.0;
			}
		}

		void setG(float _g)
		{
			if (_g >= 0 && _g <= 1)
			{
				colorG = _g;
			}
			else
			{
				colorG = 1.0;
			}
		}

		void setB(float _b)
		{
			if (_b >= 0 && _b <= 1)
			{
				colorB = _b;
			}
			else
			{
				colorB = 1.0;
			}
		}

		// METODO DE ASIGNACION DE LOS 3 COLORES A LA VEZ
		void setRGB(float _r, float _g, float _b)
		{
			setR(_r);
			setG(_g);
			setB(_b);
		}
};
