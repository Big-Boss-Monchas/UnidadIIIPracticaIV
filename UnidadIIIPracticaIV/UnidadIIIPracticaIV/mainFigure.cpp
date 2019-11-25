/*
* GRAFICACION - UNIDAD 3
* INTEGRANTES:
* IVAN FRANCO DELGADO
* JESUS EDUARDO SOSA DIAZ
* JOSUE TORRES AVALOS
*/

#include <GL/glut.h>
#include "PrismHexagonal.h"
#include "PrismPentagonal.h"
#include "PrismCuadrangular.h"
#include "PrismTriangular.h"
#include "PyramidPentagonal.h"
#include "PyramidTriangular.h"
#include "PyramidHexagonal.h"
#include "Cube.h"
#include "Cone.h"
#include <string>

#define HEIGHT 720
#define WIDTH 1280

void drawOptions(void);
void drawDimensionSelection(void);
void baseLengthHeight(void);
void baseHeight(void);
void base(void);
void mouseControl(int, int, int, int);
bool collisionDetection(int);
void writeBitmapString(void *font, const char *string);
void initializer(void);
void drawAxis(void);
void displayScreen(void);
void assignValues(void);
void calculateNumber(int);
void resetDefault(void);
void resetNumbers(void);
void teclado_cb(GLubyte, GLint, GLint);

static long font = (long) GLUT_BITMAP_8_BY_13; // Font selection.
bool draw = false;
int selection = 0;
int state = 0;
int valBase = 0;
int valHeight = 0;
int valLength = 0;
float angle = 0.0;
float angleSingle = 0.0;

Vertex3d mouseClic;
Cone conito(0, 0, 0, valBase, valHeight);
Cube cubito(0, 0, 0);
PrismTriangular prT(0, 0, 0, valBase, valHeight);
PrismCuadrangular prC(0, 0, 0, valBase, valLength, valHeight);
PrismPentagonal prP(0, 0, 0, valBase, valHeight);
PrismHexagonal prH(0, 0, 0, valBase, valHeight);
PyramidTriangular pyT(0, 0, 0, valBase, valHeight);
PyramidPentagonal pyP(0, 0, 0, valBase, valHeight);
PyramidHexagonal pyH(0, 0, 0, valBase, valHeight);

std::string message = "Select a figure to draw";
std::string messageBase = "-";
std::string messageLength = "-";
std::string messageHeight = "-";

/*
 *  FUNCION QUE ESCRIBE LAS DIFERENTES OPCIONES A DIBUJAR
 *  SIRVEN COMO ETIQUETA PARA DAR CLIC SOBRE ELLAS
 *  UNA ETIQUETA POR CADA FIGURA
 */
void drawOptions() {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-300, 330);
	writeBitmapString((void*)font, "Draw a 3D Cone");

	glRasterPos2f(-300, 280);
	writeBitmapString((void*)font, "Draw a 3D Cube");

	glRasterPos2f(-300, 230);
	writeBitmapString((void*)font, "Draw a 3D Prism Triangular");

	glRasterPos2f(-300, 180);
	writeBitmapString((void*)font, "Draw a 3D Prism Cuadrangular");

	glRasterPos2f(-300, 130);
	writeBitmapString((void*)font, "Draw a 3D Prism Pentagonal");

	glRasterPos2f(-300, 80);
	writeBitmapString((void*)font, "Draw a 3D Prism Hexagonal");

	glRasterPos2f(-300, 30);
	writeBitmapString((void*)font, "Draw a 3D Pyramid Triangular");

	glRasterPos2f(-300, -20);
	writeBitmapString((void*)font, "Draw a 3D Pyramid Pentagonal");

	glRasterPos2f(-300, -70);
	writeBitmapString((void*)font, "Draw a 3D Pyramid Hexagonal");
	if (selection == 0)
	{
		glRasterPos2f(-300, -150);
		writeBitmapString((void*)font, message.c_str());
	}
	
}

/*
 *  FUNCION QUE DEPENDIENDO DE LA SELECCION DE FIGURA, 
 *  MOSTRARA LAS INSTRUCCIONES DE LOS VALORES QUE ESPERA
 */
void drawDimensionSelection() {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-300, -330);
	switch (state)
	{
	case 1:	writeBitmapString((void*)font, "Digit length");	break;
	case 2:	writeBitmapString((void*)font, "Digit height");	break;
	default: writeBitmapString((void*)font, "Digit base");	break;
	}

	switch (selection)
	{
	case 1:	baseHeight();		break;
	case 2:	base();				break;
	case 3:	baseHeight();		break;
	case 4:	baseLengthHeight();	break;
	case 5:	baseHeight();		break;
	case 6:	baseHeight();		break;
	case 7:	baseHeight();		break;
	case 8:	baseHeight();		break;
	case 9:	baseHeight();		break;
	default:					break;
	}
}

/*
 *  PIDELA BASE, LONGITUD Y ALTURA PARA PRISMA CUADRANGULAR
 */
void baseLengthHeight() {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-300, -220);
	writeBitmapString((void*)font, "Enter base: ");

	glRasterPos2f(0, -220);
	writeBitmapString((void*)font, messageBase.c_str());

	// SI EL ESTADO ES 1, SIGNIFICA QUE LA BASE YA FUE INGRESADA
	// SI ES PRISMA CUADRANGULAR, PEDIRA LA LONGITUD
	if (state == 1 || (state == 2 && selection == 4))
	{
		glRasterPos2f(-300, -260);
		writeBitmapString((void*)font, "Enter length: ");

		glRasterPos2f(0, -260);
		writeBitmapString((void*)font, messageLength.c_str());
	}
	// SI EL ESTADO ES 2, FINALMENTE PIDE LA ALTURA DE LA FIGURA
	if (state == 2)
	{
		glRasterPos2f(-300, -300);
		writeBitmapString((void*)font, "Enter height: ");

		glRasterPos2f(0, -300);
		writeBitmapString((void*)font, messageHeight.c_str());
	}
}

/*
 *  PIDELA BASE Y ALTURA PARA LAS FIGURAS 3D
 *  EXCEPTO PRISMA CUADRANGULAR Y CUBO
 */
void baseHeight() {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-300, -220);
	writeBitmapString((void*)font, "Enter base: ");

	glRasterPos2f(0, -220);
	writeBitmapString((void*)font, messageBase.c_str());
	if (state > 0)
	{
		glRasterPos2f(-300, -260);
		writeBitmapString((void*)font, "Enter height: ");

		glRasterPos2f(0, -260);
		writeBitmapString((void*)font, messageHeight.c_str());
	}
}

/*
 *  PIDELA BASE UNICAMENTE PARA EL CUBO
 */
void base() {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-300, -220);
	writeBitmapString((void*)font, "Enter base: ");

	glRasterPos2f(0, -220);
	writeBitmapString((void*)font, messageBase.c_str());
}

/*
 *  FUNCION QUE CAPTURA LOS CLIC DEL RATON, SI EL CLIC ESTA DENTRO 
 *  DEL AREA DE ALGUNAS DE LAS ETIQUETAS, ENTONCES LE ES ASIGNADO 
 *  UN NUMERO IDENTIFICADOR PARA LA FIGURA Y ACTUALIZA LA PANTALLA
 */
void mouseControl(int button, int state, int x, int y)
{
	// BOTON IZQUIERDO PRESIONADO
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseClic.setXYZ(x, y, 0);
		if (collisionDetection(1))
		{
			selection = 1;
			resetNumbers();
			glutPostRedisplay();
		}
		else if (collisionDetection(2))
		{
			selection = 2;
			resetNumbers();
			glutPostRedisplay();
		}
		else if (collisionDetection(3))
		{
			selection = 3;
			resetNumbers();
			glutPostRedisplay();
		}
		else if (collisionDetection(4))
		{
			selection = 4;
			resetNumbers();
			glutPostRedisplay();
		}
		else if (collisionDetection(5))
		{
			selection = 5;
			resetNumbers();
			glutPostRedisplay();
		}
		else if (collisionDetection(6))
		{
			selection = 6;
			resetNumbers();
			glutPostRedisplay();
		}
		else if (collisionDetection(7))
		{
			selection = 7;
			resetNumbers();
			glutPostRedisplay();
		}
		else if (collisionDetection(8))
		{
			selection = 8;
			resetNumbers();
			glutPostRedisplay();
		}
		else if (collisionDetection(9))
		{
			selection = 9;
			resetNumbers();
			glutPostRedisplay();
		}
	}
}

/*
 * REALIZA LAS OPERACIONES DE CALCULO DE COLISION DE ACUERDO 
 * A LOS LIMITES FIJADOS POR CADA ETIQUETA DE TEXTO
 */
bool collisionDetection(int figure3d) {
	switch (figure3d) // DEPENDIENDO LA FIGURA SELECCIONADA HACE LA COMPARACION
	{
	case 1: {
		float x1 = 370, x2 = 485;
		float y1 = 82, y2 = 68;
		// COMPARA LAS COORDENADAS EN EJE X E Y
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 2: {
		float x1 = 370, x2 = 485;
		float y1 = 103, y2 = 88;
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 3: {
		float x1 = 370, x2 = 580;
		float y1 = 125, y2 = 110;
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 4: {
		float x1 = 370, x2 = 595;
		float y1 = 145, y2 = 130;
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 5: {
		float x1 = 370, x2 = 580;
		float y1 = 165, y2 = 150;
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 6: {
		float x1 = 370, x2 = 570;
		float y1 = 185, y2 = 170;
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 7: {
		float x1 = 370, x2 = 595;
		float y1 = 210, y2 = 195;
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 8: {
		float x1 = 370, x2 = 595;
		float y1 = 230, y2 = 215;
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	case 9: {
		float x1 = 370, x2 = 585;
		float y1 = 250, y2 = 235;
		bool collisionX = (x1 <= mouseClic.getX() && x2 >= mouseClic.getX());
		bool collisionY = (y1 >= mouseClic.getY() && y2 <= mouseClic.getY());
		return collisionX && collisionY;
	}
	default:
		return false;
	}
}

void writeBitmapString(void *font, const char *string)
{
	const char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void initializer() {
	glClearColor(1.0, 1.0, 1.0, 0.0); // COLOR CANVAS
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-350.0, 350.0, -350.0, 350.0, -300.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

// DIBUJA LOS EJES
void drawAxis() {
		glColor3f(1.0, 0.0, 0.0); 
		glBegin(GL_LINES); 
		glVertex3i(-700, 0, 0); 
		glVertex3i(700, 0, 0);
		glColor3f(0.0, 1.0, 0.0); 
		glBegin(GL_LINES); 
		glVertex3i(0, -700, 0);
		glVertex3i(0, 700, 0);
		glColor3f(0.0, 0.0, 1.0); 
		glBegin(GL_LINES); 
		glVertex3i(0, 0, -700); 
		glVertex3i(0, 0, 700);
	glEnd();
}

void displayScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(350, 350, 300, 300);

	if (draw)
	{
		drawAxis();
		switch (selection)
		{
		case 1:
			glPushMatrix();
			glRotatef(angleSingle, 1.0, 1.0, 1.0);
			conito.drawFigure();
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glRotatef(angleSingle, 1.0, 1.0, 1.0);
			cubito.drawFigure();
			glPopMatrix();			
			break;
		case 3:
			glPushMatrix();
			glRotatef(angleSingle, 1.0, 1.0, 1.0);
			prT.drawFigure();
			glPopMatrix();
			break;
		case 4:
			glPushMatrix();
			glRotatef(angleSingle, 1.0, 1.0, 1.0);
			prC.drawFigure();
			glPopMatrix();
			break;
		case 5:
			glPushMatrix();
			glRotatef(angleSingle, 1.0, 1.0, 1.0);
			prP.drawFigure();
			glPopMatrix();
			break;
		case 6:
			glPushMatrix();
			glRotatef(angleSingle, 1.0, 1.0, 1.0);
			prH.drawFigure();
			glPopMatrix();
			break;
		case 7:
			glPushMatrix();
			glRotatef(angleSingle, 1.0, 1.0, 1.0);
			pyT.drawFigure();
			glPopMatrix();
			break;
		case 8:
			glPushMatrix();
			glRotatef(angleSingle, 1.0, 1.0, 1.0);
			pyP.drawFigure();
			glPopMatrix();
			break;
		case 9:
			glPushMatrix();
			glRotatef(angleSingle, 1.0, 1.0, 1.0);
			pyH.drawFigure();
			glPopMatrix();
			break;
		default:
			break;
		}
	}
	else
	{
		drawOptions();
		if (selection != 0)
		{
			drawDimensionSelection();
			if (state == 3)	{ assignValues(); }
		}
	}
	glutSwapBuffers();
}

// ASIGNA LOS VALORES CAPTURADOS HACIA LAS FIGURAS
void assignValues() {
	switch (selection)
	{
	case 1:
		conito.setRadius(valBase);
		conito.setHeight(valHeight);
		break;
	case 2:
		cubito.setDimension(valBase);
		break;
	case 3:
		prT.setBase(valBase);
		prT.setHeight(valHeight);
		break;
	case 4:
		prC.setBase(valBase);
		prC.setLength(valLength);
		prC.setHeight(valHeight);
		break;
	case 5:
		prP.setBase(valBase);
		prP.setHeight(valHeight);
		break;
	case 6:
		prH.setBase(valBase);
		prH.setHeight(valHeight);
		break;
	case 7:
		pyT.setBase(valBase);
		pyT.setHeight(valHeight);
		break;
	case 8:
		pyP.setSide(valBase);
		pyP.setHeight(valHeight);
		break;
	case 9:
		pyH.setSide(valBase);
		pyH.setHeight(valHeight);
		break;
	default:
		break;
	}
}

// CALCULA LOS VALORES ASIGNADOS
void calculateNumber(int num) {
	if (state == 0)
	{
		valBase = (valBase * 10) + num;
		messageBase = std::to_string(valBase);
	}
	else if (state == 1)
	{
		valLength = (valLength * 10) + num;
		messageLength = std::to_string(valLength);

	}
	else if (state == 2)
	{
		valHeight = (valHeight * 10) + num;
		messageHeight = std::to_string(valHeight);
	}
	else
	{
		return;
	}
}

// ESTABLECE LOS VALORES POR DEFECTO
void resetDefault() {
	draw = false;
	selection = 0;
	glLoadIdentity();
	angle = 0.0;
	resetNumbers();
	angleSingle = 0.0;
}

void resetNumbers() {
	messageBase = "-";
	messageLength = "-";
	messageHeight = "-";
	valBase = 0;
	valHeight = 0;
	valLength = 0;
	state = 0;
}

// CAPTURA LOS EVENTOS DEL TECLADO
void teclado_cb(GLubyte key, GLint x, GLint y) {

	if (!draw)
	{
		if (key == 27)	{ exit(1); } 
		if (selection != 0)
		{
			switch (key)
			{
			case 48: calculateNumber(0);	break;
			case 49: calculateNumber(1);	break;
			case 50: calculateNumber(2);	break;
			case 51: calculateNumber(3);	break;
			case 52: calculateNumber(4);	break;
			case 53: calculateNumber(5);	break;
			case 54: calculateNumber(6);	break;
			case 55: calculateNumber(7);	break;
			case 56: calculateNumber(8);	break;
			case 57: calculateNumber(9);	break;
			case 'r':	resetDefault();		break;
			case 13:
				if (state == 0 && valBase > 0)
				{
					state++;
					if (selection != 4)	{	state = 2;	}
					if (selection == 2)
					{
						state++;
						draw = true;
						assignValues();
					}
				}
				else if (state == 1 && valLength > 0)
				{
					state++;
				}
				else if (state == 2 && valHeight > 0)
				{
					state++;
					draw = true;
					assignValues();
				}
				break;
			case 27:	exit(1);	break;
			default:				break;
			}
		}	
		glutPostRedisplay();
	}

	switch (key) {
	case 27:	exit(1);		break;
	case 'x':
		// aqu  se procesar a la tecla <x>
		glRotatef(1.0, 1.0, 0.0, 0.0);
		break;
	case 'y':
		// aqu  se procesar a la tecla <y>
		glRotatef(1.0, 0.0, 1.0, 0.0);
		break;
	case 'z':
		// aqu  se procesar a la tecla <z>
		glRotatef(1.0, 0.0, 0.0, 1.0);
		break;
	case 'c':
		// aqu  se procesar a la tecla <c>
		glRotatef(-1.0, 1.0, 0.0, 0.0);
		break;
	case 't':
		// aqu  se procesar a la tecla <t>
		glRotatef(-1.0, 0.0, 1.0, 0.0);
		break;
	case 'a':
		// aqu  se procesar a la tecla <a>
		glRotatef(-1.0, 0.0, 0.0, 1.0);
		break;
	case 'e':
		// aqu  se procesar a la tecla <e>
		glRotatef(5.0, 1.0, 1.0, 1.0);
		break;
	case 'r':
		// aqu  se procesar a la tecla <r>
		resetDefault();
		break;
	case 'q':
		// aqu  se procesar a la tecla <q>
		angleSingle += 3;
		break;
	default:		break;
	}
	glutPostRedisplay();
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT); // ESTABLECE EL TAMANO DE LA VENTANA
	glutCreateWindow("FIGURAS 3D");

	initializer(); // INICIALIZA LA VENTANA
	glutDisplayFunc(displayScreen); // ACTUALIZA LA PANTALLA DE TRAZADO
	glutKeyboardFunc(teclado_cb);
	glutMouseFunc(mouseControl); // CAPTURA LOS CLICS

	glutMainLoop(); // GENERA EL LOOP

	return 0;
}