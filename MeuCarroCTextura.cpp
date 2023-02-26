/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2022/23
	................................................ Leonor Reis, uc2019210146
	Meta 2 - LUZ + TEXTURA + MATERIAIS
======================================================================================= */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "RgbImage.h"

#define PI		 3.14159
//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define CYAN     0.0, 1.0, 1.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.3, 0.3, 0.3, 1.0
#define BLUE_C     0.67, 0.84, 0.92, 1.0
#define BORDO    0.51, 0.22, 0.31, 1.0
#define YELLOW_DARK   0.93, 0.68, 0.18, 1.0
#define LIGHT_BLUE 0.6,0.9, 0.9, 0.8
#define LIGHT_BLACK 0.0,0.0, 0.0, 0.2
#define BLACK    0.0, 0.0, 0.0, 1.0
#define RED   1.0, 0.0, 0.0, 1.0

//------------------------------------------------- Propriedades Materiais
void initMaterials(int material);
//=========================================== Objecto
GLint     material = 10;

//================================================================================
//------------------------------------------------------------ Sistema Coordenadas 

GLint		wScreen = 700, hScreen = 600;		//.. janela - pixeis
GLfloat		size = 10.0;	//.. Mundo  SIZE=coordenadas x=y=z

bool troca = 0;
//=================================================================== TEXTURAS
RgbImage imag;
//------------------------------------------------------------ Texturas (2 texturas)
GLuint   texture[3];

// ======================================================== Malha de poligonos
GLint dim = 256;
GLfloat med_dim = (float)dim / 2;
GLint i = 0;
GLint j = 0;



//========================================================= Animacao 
GLfloat	  rotacao = 0;
GLfloat   agRodas = 0;
GLfloat	  incRodas = 0;
GLint     sempreRodar = 0;

//controla a subida do carro
GLfloat   incALT = 0.1;

//controla a transalação do carro
GLfloat	  centrox = 0;
GLfloat	  incX = 0.1;

//controla a translação do vidro
GLfloat vidroy = 0;
GLfloat incVidro = 0.1;

//controla o zoom
GLint zoom = 85;

GLfloat xPar = 0.0, incPar = 0.05;		//.. posicao horizontal da base / incremento para deslocamento




//============================================================= Observador
GLfloat  rVisao = 8, aVisao = -0.5 * PI, incVisao = 1;
GLfloat  obsP[] = { rVisao * cos(aVisao), 2.0, rVisao * sin(aVisao) };
float	 anguloZ = 35;


//===========================================================Variaveis e constantes
GLint     msec = 50;

//---------------------------------------------------- AMBIENTE 
GLint   Dia = 0;     //:::   'D'  
GLfloat intensidadeDia = 0.5;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1.0 };   // 

//---------------------------------------------------- Luz faról (pontual)
GLfloat intensidadeT = 0.05;  //:::   'I'  
GLint   red = 1;		 	 //:::   'R'  
GLint   green = 1;			 //:::   'G'  
GLint   blue = 1;			 //:::   'B'  
GLfloat position[4] = { 3.25, 0.25, 0.80, 1.0 };
GLfloat compAmbiente[4] = { 0, 0, 0, 0.0 };
GLfloat compDifusa[4] = { red, green, blue, 1.0 };
GLfloat compEspecular[4] = { red, green, blue, 1.0 };



// ================================================= Luz p ( Estrada)
GLfloat Foco_direccao[] = { -1,-1, 0, 0 }; //……… x
GLfloat Foco1_cor[] = { 1.0, 0.0, 0.0, 1 }; //……… Cor da luz 1
GLfloat Foco_ak = 0.05;
GLfloat Foco_al = 0.00f;
GLfloat Foco_aq = 0.0f;
GLfloat Foco_Expon = 13;
GLfloat aberturaFoco = 30;
GLfloat Pos1[] = { -2.5, 0.0, 0,1 };



//==================================================================== VERTEX ARAY
//------------------------------------------- coordenadas + normais + cores
GLfloat tam = 0.6;
static GLfloat vertices_base[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
		-tam,  -tam,  tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   tam, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
		//…………………………………………………… Direita
		tam,  -tam,  tam,	// 4 
		tam,   tam,  tam,	// 5 
		tam,   tam, -tam,	// 6 
		tam,  -tam, -tam,	// 7 
		//……………………………………………………… Cima
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		tam,  tam, -tam,// 10 
		tam,  tam,  tam,// 11 
		//……………………………………………………… Baixo
		-tam,  -tam,  tam,	// 12
		-tam,  -tam, -tam,	// 13
		tam,  -tam, -tam,	// 14
		tam,  -tam,  tam,	// 15 
		//……………………………………………………… Frente
		-tam,  -tam,  tam,	// 16
		-tam,   tam,  tam,	// 17
		tam,   tam,  tam,	// 18
		tam,  -tam,  tam,	// 19
		//……………………………………………………… Tras
		-tam,  -tam, -tam,	// 20
		-tam,   tam, -tam,	// 21
		tam,   tam, -tam,	// 22
		tam,  -tam, -tam,	// 23
};



static GLfloat normais[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  //…………………………………………………………………………………………………… x=tam (Direita)
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  1.0,  0.0,  0.0,
	  //…………………………………………………………………………………………………… y=tam (Cima)
   0.0,  1.0,  0.0,
   0.0,  1.0,  0.0,
   0.0,  1.0,  0.0,
   0.0,  1.0,  0.0,
   //…………………………………………………………………………………………………… y=tam (Baixo)
	0.0,  -1.0,  0.0,
   0.0,  -1.0,  0.0,
   0.0,  -1.0,  0.0,
   0.0,  -1.0,  0.0,
   //…………………………………………………………………………………………………… z=tam (Frente)
   0.0,  0.0,  1.0,
   0.0,  0.0,  1.0,
   0.0,  0.0,  1.0,
   0.0,  0.0,  1.0,
   //…………………………………………………………………………………………………… z=tam (Tras)
   0.0,  0.0,  -1.0,
   0.0,  0.0,  -1.0,
   0.0,  0.0,  -1.0,
   0.0,  0.0,  -1.0,
};


//=======================================================
//  <><><><><><><>             FACE  DIREITA  ????
//  <><><><><><><>             FACE  ESQUERDA ????
//=======================================================
static GLuint     cima[] = { 8, 11, 10, 9 };
static GLuint     direita[] = { 4, 7, 6, 5 };
static GLuint     esquerda[] = { 0, 1, 2, 3 };
static GLuint	  frente[] = { 16,19,18,17 };
static GLuint	  tras[] = { 20,23,22,21 };
static GLuint	  baixo[] = { 12,13,14,15 };


//================================================================================
//=========================================================================== INIT

void initTexturas()
{
	//-----------------------------------------  Estrada
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("road66.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	//----------------------------------------- Capô
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("riscasamarelas.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	//----------------------------------------- Jantes
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("jantes2.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

}

//…………………………………………………………………………………………………………………………………………… LUZES
void initLights(void) {
	//…………………………………………………………………………………………………………………………………………… Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, compAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, compDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, compEspecular);

	glLightfv(GL_LIGHT1, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco); // abertura
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon); // concentração
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
}

void initialize(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glShadeModel(GL_SMOOTH);


	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glEnable(GL_NORMALIZE);
	//…………………………………………………………………………………………………………………………… ILUMINACAO / MAteriais
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	initLights();
	initTexturas();
	glVertexPointer(3, GL_FLOAT, 0, vertices_base);	//………………………………………Posicoes
	glEnableClientState(GL_VERTEX_ARRAY);



	glNormalPointer(GL_FLOAT, 0, normais);		//………………………………………Normais
	glEnableClientState(GL_NORMAL_ARRAY);
}




//======================================================================== ILUMINCCAO
void updateLuz() {
	compAmbiente[0] = red * intensidadeT;
	compAmbiente[1] = green * intensidadeT;
	compAmbiente[2] = blue * intensidadeT;
	compDifusa[0] = red * intensidadeT;
	compDifusa[1] = green * intensidadeT;
	compDifusa[2] = blue * intensidadeT;
	compEspecular[0] = red * intensidadeT;
	compEspecular[1] = green * intensidadeT;
	compEspecular[2] = blue * intensidadeT;


	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, compAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, compDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, compEspecular);


	glLightfv(GL_LIGHT1, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco); // abertura
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon); // concentração
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
}

void iluminacao() {
	updateLuz();
	glEnable(GL_LIGHT0);
}



GLvoid resize(GLsizei width, GLsizei height) {
	wScreen = width;
	hScreen = height;
	glViewport(0, 0, wScreen, hScreen);
	glutPostRedisplay();
}


void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo
	glColor4f(ORANGE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5 * size, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5 * size, 0);
	glEnd();
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5 * size);
	glEnd();

}

//mat - material aplicado, tr - transparência aplicada
void desenhaCubo(bool mat, bool tr, bool text1) {
	if (mat) {
		glDisable(GL_COLOR_MATERIAL);
		initMaterials(material);
	}
	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glPopMatrix();

	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glPopMatrix();


	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glPopMatrix();

	if (tr) {
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
		glPopMatrix();

		glBlendFunc(GL_ONE, GL_ZERO);

	}
	else {
		glPushMatrix();
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
		glPopMatrix();
	}

	if (text1) {
		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
	}
	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glPopMatrix(); 

	if (text1) {
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	}

	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();

	if (mat) {
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	}

}

void desenhaCapo() {
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glPopMatrix();

	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glPopMatrix();

	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Face Transparente
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glColor4f(LIGHT_BLUE);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glPopMatrix();

	glBlendFunc(GL_ONE, GL_ZERO);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Mapeamento das texturas
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glNormal3d(1, 0, 0);

	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.6, -0.6, 0.6);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.6, -0.6, 0.6);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.6, 0.6, 0.6);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.6, 0.6, 0.6);

	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.6, -0.6, -0.6);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.6, -0.6, -0.6);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.6, 0.6, -0.6);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.6, 0.6, -0.6);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void desenhaEstrada() {
	GLfloat  corEstrada[] = { 1. ,1.,1.,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, corEstrada);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corEstrada);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corEstrada);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.5);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glNormal3d(0, 1, 0);

	glPushMatrix();
	glTranslatef(-9.0, -2.0, 7.0);
	glScalef(12, 0, 6);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);

	glBegin(GL_QUADS);
	med_dim = (float)dim / 2;
	for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++) {
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
		}
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);


}


void desenhaCarro(GLfloat xPar) {
	glBlendFunc(GL_ONE, GL_ZERO);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glPushMatrix();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Base do carro
	glTranslatef(centrox, 0.0, 0.0); 
	glColor4f(YELLOW_DARK);
	glPushMatrix();
		glScalef(6.5, 2.0, 2.5);
		desenhaCubo(0,0,1);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Luz marcha-atrás
	glPushMatrix();
	glColor4f(RED);
		glTranslatef(-4.0, 0.5, 0);
		glScalef(0.4, 0.2, 1);
		desenhaCubo(0,0,0);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Capô do carro
	glColor4f(WHITE);
	glPushMatrix();
		glTranslatef(0.0, 2.1, 0.0);
		glScalef(3.5, 1.5, 2.5);
		desenhaCapo();
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Limpa Pára-brisas do carro
	glColor4f(BLACK); 
	glPushMatrix();
		glTranslatef(2.2, 1.25, 0.0);
		glRotatef(rotacao, 1, 0, 0);
		glTranslatef(0.0, 0.75, 0.0);
		glScalef(0.3, 1.3, 0.15);
		desenhaCubo(0,0,0);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Faróis dianteiros
	glColor4f(YELLOW); 
	glPushMatrix();
		glTranslatef(xPar, 0.0, 0.0);
		glTranslatef(3.5, 0.25, -0.75);
		glScalef(0.5, 0.5, 0.5);
		desenhaCubo(0, 0,0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(xPar, 0.0, 0.0);
		glTranslatef(3.5, 0.25, 0.75);
		glScalef(0.5, 0.5, 0.5);
		desenhaCubo(0, 0,0);
	glPopMatrix();


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Pneus do carro
	glColor4f(BLACK); 
	glPushMatrix();
	glTranslatef(-2.0, -0.5, 1.25);
	glRotated(rotacao, 0, 0, 1);
	glScalef(1.0, 1.0, 1.0);
	desenhaCubo(1,0,0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.0, -0.5, 1.25);
	glRotated(rotacao, 0, 0, 1);
	glScalef(1.0, 1.0, 1.0);
	desenhaCubo(1,0,0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.0, -0.5, -1.25);
	glRotated(rotacao, 0, 0, 1);
	glScalef(1.0, 1.0, 1.0);
	desenhaCubo(1,0,0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.0, -0.5, -1.25);
	glRotated(rotacao, 0, 0, 1);
	glScalef(1.0, 1.0, 1.0);
	desenhaCubo(1,0,0);
	glPopMatrix();

	glPopMatrix();


	glDisable(GL_COLOR_MATERIAL);

	//==================================== Estrada
	desenhaEstrada();
}



void display(void) {

	//================================================================= APaga 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING);

	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom, (float)wScreen / hScreen, 0.1, 9999);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);


	updateLuz();
	glEnable(GL_LIGHT0);

	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawEixos();
	desenhaCarro(xPar);

	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}






//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {
	case 'A': case 'a':
		centrox = centrox + incX;
		Pos1[0] = Pos1[0] + incX;

		if (centrox > 3) {
			incX = -incX;
		}
		if (centrox < -1) {
			incX = -incX;
		}
		glutPostRedisplay();
		break;


	case 'l': case 'L':
		intensidadeT = intensidadeT + 0.1;
		if (intensidadeT > 1.1) intensidadeT = 0;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'r':case 'R':
		red = (red + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'b':case 'B':
		blue = (blue + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'g':case 'G':
		green = (green + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;


		//--------------------------- Material
	case 'm': case 'M':
		material = (material + 1) % 18;
		initMaterials(material);
		glutPostRedisplay();
		break;
		//______________________ divisão de poligonos
	case 'p': case 'P':
		dim = 2 * dim;
		if (dim > 256) dim = 10;
		glutPostRedisplay();
		break;
		//------------------------------ translação dos faróis
	case 'X': case 'x':
		//+++ movimentar faróis para a frente
		if (xPar < 0.5)
			xPar = xPar + incPar;
		else
			xPar = xPar;
		glutPostRedisplay();
		break;

	case 'Z': case 'z':
		//+++ movimentar faróis para trás
		if (xPar > -0.5)
			xPar = xPar - incPar;
		else
			xPar = xPar;
		glutPostRedisplay();
		break;


	case 27:
		exit(0);
		break;
	}

}



void teclasNotAscii(int key, int x, int y) {

	//=========================================================
	//  <><><><><><>  Movimento do observador  ???
	//=========================================================
	if (key == GLUT_KEY_UP) { // Movimento para cima
		obsP[1] += 0.2;
	}
	if (key == GLUT_KEY_DOWN) { // Movimento para baixo
		obsP[1] -= 0.2;
	}
	if (key == GLUT_KEY_LEFT) { // Movimento para a esquerda
		aVisao -= 0.2;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
	}
	if (key == GLUT_KEY_RIGHT) { // Movimento para a direira
		aVisao += 0.2;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
	}

	glutPostRedisplay();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("PIPIPI... CARRO EM ANDAMENTO SEM TRAVÕES");

	initialize();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}



