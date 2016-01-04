// ScalarSystem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
*  Project2: Animation of the Solor System
*  Project2.cpp
*
* -------------------------------------------------------------
*  Student Information
* -------------------------------------------------------------
*  Student Name:
*  Student ID:
*  E-mail:
* -------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../OpenGL_Env/include/glut.h"
#include "Bitmap.h"

#pragma comment(lib, "glaux.lib")
#pragma  comment(lib,"opengl32.lib")
#pragma  comment(lib,"glu32.lib")
#pragma  comment(lib,"glew32.lib")
#define M_PI    3.1415926
#define M_2PI   2 * M_PI
#define M_PI_2  M_PI / 2

#define SOLAR_YEAR	     200	// Rotation Period of the solar system
#define MERCURY_YEAR     360	// Rotation Period of the Moon
#define EARTH_YEAR 	     4320   // Rotation Period of the Earth
#define VENUS_YEAR 	     2880   // Rotation Period of the Venus
#define MARS_YEAR 	     8640   // Rotation Period of the Mars
#define MOON_YEAR 	     1000	// Rotation Period of the Moon	
#define JUPITER_YEAR     4000	// Rotation Period of the Jupiter
#define SATURN_YEAR      1200 // Rotation Period of the Saturn
#define URANUS_YEAR      3600 // Rotation Period of the Uranus
#define NEPTUNE_YEAR     7200 // Rotation Period of the Neptune
#define PLUTO_YEAR 	     3600	// Rotation Period of the Pluto

#define MERCURY_DAY      66		// Self-rotation Period of the Mercury
#define EARTH_DAY 	     30		// Self-rotation Period of the Earth	
#define VENUS_DAY 	     66		// Self-rotation Period of the Venus	
#define MARS_DAY 	     11 	// Self-rotation Period of the Mars	
#define JUPITER_DAY      40		// Self-rotation Period of the Jupiter
#define SATURN_DAY 	     115	    // Self-rotation Period of the Saturn	
#define URANUS_DAY 	     8	    // Self-rotation Period of the Uranus
#define NEPTUNE_DAY      8		// Self-rotation Period of the Neptune
#define PLUTO_DAY 	     66	    // Self-rotation Period of the Pluto

#define	SUN_RADIUS		 0.10	// Radius of the Sun
#define	MERCURY_RADIUS   0.06	// Radius of the Mecury
#define	VENUS_RADIUS	 0.25	// Radius of the Venus
#define	EARTH_RADIUS	 0.25	// Radius of the Earth
#define	MOON_RADIUS		 0.08	// Radius of the Moon
#define	MARS_RADIUS		 0.15	// Radius of the Mars
#define	JUPITER_RADIUS	 0.75	// Radius of the Jupiter
#define	SATURN_RADIUS	 0.65	// Radius of the Saturn
#define	URANUS_RADIUS	 0.40	// Radius of the Uranus
#define	NEPTUNE_RADIUS	 0.30	// Radius of the Neptune
#define	PLUTO_RADIUS	 0.04	// Radius of the Pluto

#define	MERCURY_ORBIT	 0.25	// Orbit Radius of the Venus
#define	VENUS_ORBIT		 0.75	// Orbit Radius of the Venus
#define	EARTH_ORBIT		 1.75	// Orbit Radius of the Earth
#define	MOON_ORBIT		 0.35	// Orbit Radius of the Moon
#define	MARS_ORBIT		 2.5	// Orbit Radius of the Mars
#define	JUPITER_ORBIT	 3.8	// Orbit Radius of the Jupiter
#define	SATURN_ORBIT	 6.5	// Orbit Radius of the Saturn
#define	URANUS_ORBIT	 8.5	// Orbit Radius of the Uranus
#define	NEPTUNE_ORBIT	 10.5	// Orbit Radius of the Neptune
#define	PLUTO_ORBIT		 12.0	// Orbit Radius of the Pluto

#define PRECESSION_YEAR  20 	// Self-rotation Period of the Earth Precession
#define PRECESSION_ANGLE 30
#define MAX_STAR 1000

#define TRUE  1
#define FALSE 0

typedef struct tmp_star {
	float pos[3];
	float col[4];
} Star;

Star star[MAX_STAR];

GLUquadricObj *sun, *mercury, *venus, *earth, *moon, *mars;
GLUquadricObj *jupiter, *saturn, *uranus, *neptune, *pluto;

float angle_global = 0;
float year_mercury, year_earth = 0, year_venus = 0, year_mars = 0, year_moon = 0, year_star=0;
float year_jupiter = 0, year_saturn = 0, year_uranus = 0, year_neptune = 0, year_pluto = 0;
float day_mercury = 0, day_earth = 0, day_venus = 0, day_mars = 0;
float day_jupiter = 0, day_saturn = 0, day_uranus = 0, day_neptune = 0, day_pluto = 0;
float precession = 0;

GLfloat Rotate_x = 0, Rotate_y = 60;
GLfloat Translate_x = 0.0, Translate_y = 0.0;
GLfloat Zoom = 0.0, Scale = 1.0;
GLfloat dx, dy, old_x = 0.0, old_y = 0.0;
GLfloat old_dx = 0, old_dy = 0;
GLfloat dr, theta = 0;
GLfloat new_x, new_y;
int G_mousedown_L = FALSE, G_mousedown_R = FALSE;

float winwidth, winheight;
int _ScreenMode = 3;
int a=1, b=1, w,h;
GLubyte * sun_tex = new GLubyte[256 * 128];
GLubyte * A = new GLubyte[256 * 128], *B = new GLubyte[256 * 128], *C = new GLubyte[256 * 128], *D = new GLubyte[256 * 128],
*E = new GLubyte[256 * 128], *F = new GLubyte[256 * 128], *G = new GLubyte[256 * 128], * H = new GLubyte[256 * 128],
*I = new GLubyte[256 * 128], *J = new GLubyte[256 * 128];

GLubyte * aa = new GLubyte[256 * 128], *bb = new GLubyte[256 * 128], *cc = new GLubyte[256 * 128], *dd = new GLubyte[256 * 128],
*ee = new GLubyte[256 * 128], *ff = new GLubyte[256 * 128], *gg = new GLubyte[256 * 128],  *hh = new GLubyte[256 * 128],
*ii= new GLubyte[256 * 128], *jj = new GLubyte[256 * 128];
GLUquadric* cudgel,*u;

void TransformXY(int ix, int iy, float *x, float *y)
{
	*x = 2.0 * (float)ix / (float)winwidth - 1.0;
	*y = -2.0 * (float)iy / (float)winheight + 1.0;
}

// Capture the BMP file 
GLubyte* TextureLoadBitmap(char *filename, int *w, int *h) // I - Bitmap file to load
{
	BITMAPINFO *info; // Bitmap information
	void		  *bits; // Bitmap pixel bits
	GLubyte	  *rgb;	 // Bitmap RGB pixels
	GLubyte    err = '0';

	// Try to load the bitmap and converting it to RGB...
	bits = LoadDIBitmap(filename, &info);
	if (bits == NULL)
		return (NULL);

	rgb = ConvertRGB(info, bits);

	if (rgb == NULL) {
		free(info);
		free(bits);
	};

	printf("%s: %d %d\n", filename, info->bmiHeader.biWidth, info->bmiHeader.biHeight);
	printf("read %s successfully\n", filename);
	*w = info->bmiHeader.biWidth;
	*h = info->bmiHeader.biHeight;

	// Free the bitmap and RGB images, then return 0 (no errors).
	free(info);
	free(bits);

	return (rgb);
}

// Mouse callback for handling mouse click
void Mouse(int button, int state, int ix, int iy)
{
	float x, y;

	// Transform mouse position from screen coordinate to world 2D coordinate
	TransformXY(ix, iy, &x, &y);

	// Save old cursor location when mouse is clicked
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		G_mousedown_L = TRUE;
		old_x = x;
		old_y = y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		G_mousedown_L = FALSE;
		old_dx = dx;
		old_dy = dy;
		dx = 0;
		dy = 0;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		G_mousedown_R = TRUE;
		old_x = x;
		old_y = y;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		G_mousedown_R = FALSE;
	}
	glutPostRedisplay();
}

void Drag(int ix, int iy)
{
	// Transform mouse position from screen coordinate to world 2D coordinate
	TransformXY(ix, iy, &new_x, &new_y);

	// Increment rotation angle for right mouse dragging
	if (G_mousedown_L) {
		Rotate_y += (new_y - old_y) * 30;
		old_x = new_x;
		old_y = new_y;
	}

	// Increment scale for left mouse dragging
	if (G_mousedown_R) {
		Scale += new_y - old_y;
		if (Scale < 0.2) Scale = (float) 0.2;
		if (Scale > 3.0) Scale = (float) 3.0;
		old_x = new_x;
		old_y = new_y;
	}
	glutPostRedisplay();
}

// Keyboard callback for handling keyboard event
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'G':
	case'g':

		if (a == 1){
			a = 0;
		}
		else{
			a = 1;
		}
		break;

	case'T':
	case't':

		if (b == 1){
			b = 0;
		}
		else{
			b = 1;
		}
		break;

	case 'R':
	case 'r':

		year_mercury = 0, year_earth = 0, year_venus = 0, year_mars = 0, year_moon = 0;
		year_jupiter = 0, year_saturn = 0, year_uranus = 0, year_neptune = 0, year_pluto = 0, year_star = 0;
		break;

	}

}


// Special key-stroke callback function
void Special(int key, int x, int y)
{
	if (key == GLUT_KEY_F1) {
		_ScreenMode++;
		if (_ScreenMode > 3) _ScreenMode = 0;
		if (_ScreenMode == 0)
			glutReshapeWindow(350, 200);
		else if (_ScreenMode == 1)
			glutReshapeWindow(700, 400);
		else if (_ScreenMode == 2)
			glutReshapeWindow(900, 600);
		else if (_ScreenMode == 3)
			glutReshapeWindow(150, 75);
	}
}

// Reshape callback
void Reshape(int w, int h)
{
	winwidth = w;
	winheight = h;
	glViewport(0, 0, w, h);      // Viewport transformation
	glMatrixMode(GL_PROJECTION);	// Projection transformation
	glLoadIdentity();
	gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 40.0);
	glutPostRedisplay();
}

// Display callback
void Display(void)
{
	// Clear the window color before drawing is performed
	gluLookAt(5.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, sun_tex);
	//gluSphere(sun, SUN_RADIUS, 100, 100);
	glScalef(Scale, Scale, Scale);
	glRotatef(Rotate_y, 0.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);

	GLfloat position0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient2[] = { 0.0, 0.0, 0.0, 1.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient2);


	glPushMatrix();
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, position0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glRotatef(year_star, 0.0, 1.0, 0.0);
	for (int num = 1; num <= 1000; num++)
	{
		glBegin(GL_POINTS);
		glVertex3f(star[num].pos[0], star[num].pos[1], star[num].pos[2]);
		glEnd();
	}
	glPopMatrix();



	glPushMatrix();
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, sun_tex);
	gluSphere(sun, SUN_RADIUS, 100, 100);
	glPopMatrix();


	glPushMatrix();
	glRotatef(year_mercury, 0.0, 1.0, 0.0);
	glTranslatef(MERCURY_ORBIT, 0.0, 0.0);
	glPushMatrix();
	glRotatef(day_mercury, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, A);
	gluSphere(mercury, MERCURY_RADIUS, 100, 100);
	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, aa);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.3, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.3, 0.3, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 0.3, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(year_venus, 0.0, 1.0, 0.0);
	glTranslatef(VENUS_ORBIT, 0.0, 0.0);
	glPushMatrix();
	glRotatef(day_venus, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, B);
	gluSphere(venus, VENUS_RADIUS, 100, 100);
	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, bb);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4, 0.1, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4, 0.4, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.1, 0.4, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();



	glPushMatrix();
	glRotatef(year_earth, 0.0, 1.0, 0.0);
	glTranslatef(EARTH_ORBIT, 0.0, 0.0);

	glPushMatrix();
	glRotatef(day_earth, 0.0, 1.0, 0.0);
	glRotatef(60.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, C);
	gluSphere(earth, EARTH_RADIUS, 100, 100);
	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, cc);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2, 0.2, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.6, 0.2, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.6, 0.6, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2, 0.6, 0.0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glScalef(0.1, 5.0, 0.1);
	glutSolidCube(0.2);

	glPopMatrix();

	glRotatef(year_moon, 0, 0, 1);
	glTranslatef(MOON_ORBIT, 0.0, 0.0);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, D);

	gluSphere(moon, MOON_RADIUS, 20, 20);

	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, dd);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4, 0.1, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4, 0.4, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.1, 0.4, 0.0);
	glEnd();
	glPopMatrix();


	glPopMatrix();




	glPopMatrix();

	glPushMatrix();
	glRotatef(year_mars, 0.0, 1.0, 0.0);
	glTranslatef(MARS_ORBIT, 0.0, 0.0);
	glPushMatrix();
	glRotatef(day_mars, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, E);
	gluSphere(mars, MARS_RADIUS, 100, 100);
	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, ee);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4, 0.1, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4, 0.4, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.1, 0.4, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glRotatef(year_jupiter, 0.0, 1.0, 0.0);
	glTranslatef(JUPITER_ORBIT, 0.0, 0.0);
	glPushMatrix();
	glRotatef(day_jupiter, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, F);
	gluSphere(jupiter, JUPITER_RADIUS, 100, 100);
	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, ff);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.3, 0.5, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.8, 0.5, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.8, 1.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.3, 1.0, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glRotatef(year_saturn, 0.0, 1.0, 0.0);
	glTranslatef(SATURN_ORBIT, 0.0, 0.0);
	glPushMatrix();
	glRotatef(day_saturn, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, G);
	gluSphere(saturn, SATURN_RADIUS, 100, 100);
	glPopMatrix();
	glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, G);
	gluDisk(u, SATURN_RADIUS + 0.1, SATURN_RADIUS + 0.2, 100, 1000);
	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, gg);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2, 0.4, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.7, 0.4, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.7, 0.9, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2, 0.9, 0.0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();





	glPushMatrix();
	glRotatef(year_uranus, 0.0, 1.0, 0.0);
	glTranslatef(URANUS_ORBIT, 0.0, 0.0);
	glPushMatrix();
	glRotatef(day_uranus, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, H);
	gluSphere(uranus, URANUS_RADIUS, 100, 100);
	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, hh);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.3, 0.5, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.8, 0.5, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.8, 1.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.3, 1.0, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glRotatef(year_neptune, 0.0, 1.0, 0.0);
	glTranslatef(NEPTUNE_ORBIT, 0.0, 0.0);
	glPushMatrix();
	glRotatef(day_neptune, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, I);
	gluSphere(neptune, NEPTUNE_RADIUS, 100, 100);
	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, ii);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.3, 0.5, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.8, 0.5, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.8, 1.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.3, 1.0, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glRotatef(year_pluto, 0.0, 1.0, 0.0);
	glTranslatef(PLUTO_ORBIT, 0.0, 0.0);
	glPushMatrix();
	glRotatef(day_pluto, 0.0, 1.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, J);
	gluSphere(pluto, PLUTO_RADIUS, 100, 100);
	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, jj);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1, 0.1, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.4, 0.1, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.4, 0.4, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.1, 0.4, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glDisable(GL_TEXTURE_2D);


	glutSwapBuffers();
}

void init()
{
	int i = 0;
	float theta, phi, r = 10;


	// Clear screen color
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0, 0, 0, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Texture mapping setting for Microsoft's OpenGL implementation
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);

	// Texture mapping parameters for filter and repeatance
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);



	sun = gluNewQuadric();
	gluQuadricDrawStyle(sun, GLU_FILL);
	gluQuadricTexture(sun, GL_TRUE);
	sun_tex = TextureLoadBitmap("../Samples/sun.bmp", &w, &h);
	//aa = TextureLoadBitmap("../Samples/mercury_name.bmp", &w, &h);



	mercury = gluNewQuadric();
	gluQuadricDrawStyle(mercury, GLU_FILL);
	gluQuadricTexture(mercury, GL_TRUE);
	A = TextureLoadBitmap("../Samples/mercury.bmp", &w, &h);
	aa = TextureLoadBitmap("../Samples/mercury_name.bmp", &w, &h);



	venus = gluNewQuadric();
	gluQuadricDrawStyle(venus, GLU_FILL);
	gluQuadricTexture(venus, GL_TRUE);
	B = TextureLoadBitmap("../Samples/venus.bmp", &w, &h);
	bb = TextureLoadBitmap("../Samples/venus_name.bmp", &w, &h);

	earth = gluNewQuadric();
	gluQuadricDrawStyle(earth, GLU_FILL);
	gluQuadricTexture(earth, GL_TRUE);
	C = TextureLoadBitmap("../Samples/earth.bmp", &w, &h);
	cc = TextureLoadBitmap("../Samples/earth_name.bmp", &w, &h);


	moon = gluNewQuadric();
	gluQuadricDrawStyle(moon, GLU_FILL);
	gluQuadricTexture(moon, GL_TRUE);
	D = TextureLoadBitmap("../Samples/moon.bmp", &w, &h);
	dd = TextureLoadBitmap("../Samples/moon_name.bmp", &w, &h);

	mars = gluNewQuadric();
	gluQuadricDrawStyle(mars, GLU_FILL);
	gluQuadricTexture(mars, GL_TRUE);
	E = TextureLoadBitmap("../Samples/mars.bmp", &w, &h);
	ee = TextureLoadBitmap("../Samples/mars_name.bmp", &w, &h);

	jupiter = gluNewQuadric();
	gluQuadricDrawStyle(jupiter, GLU_FILL);
	gluQuadricTexture(jupiter, GL_TRUE);
	F = TextureLoadBitmap("../Samples/jupiter.bmp", &w, &h);
	ff = TextureLoadBitmap("../Samples/jupiter_name.bmp", &w, &h);

	u = gluNewQuadric();
	gluQuadricDrawStyle(u, GLU_FILL);

	saturn = gluNewQuadric();
	gluQuadricDrawStyle(saturn, GLU_FILL);
	gluQuadricTexture(saturn, GL_TRUE);
	G = TextureLoadBitmap("../Samples/saturn.bmp", &w, &h);
	gg =  TextureLoadBitmap("../Samples/saturn_name.bmp", &w, &h);


	uranus = gluNewQuadric();
	gluQuadricDrawStyle(uranus, GLU_FILL);
	gluQuadricTexture(uranus, GL_TRUE);
	H = TextureLoadBitmap("../Samples/uranus.bmp", &w, &h);
	hh = TextureLoadBitmap("../Samples/uranus_name.bmp", &w, &h);

	neptune = gluNewQuadric();
	gluQuadricDrawStyle(neptune, GLU_FILL);
	gluQuadricTexture(neptune, GL_TRUE);
	I = TextureLoadBitmap("../Samples/neptune.bmp", &w, &h);
	ii = TextureLoadBitmap("../Samples/neptune_name.bmp", &w, &h);

	pluto = gluNewQuadric();
	gluQuadricDrawStyle(pluto, GLU_FILL);
	gluQuadricTexture(pluto, GL_TRUE);
	J = TextureLoadBitmap("../Samples/pluto.bmp", &w, &h);
	jj = TextureLoadBitmap("../Samples/pluto_name.bmp", &w, &h);

	cudgel = gluNewQuadric();
	gluQuadricDrawStyle(cudgel, GLU_FILL);


	while (i< 1000){
		star[i].col[0] = 1.0;
		star[i].col[1] = 1.0;
		star[i].col[2] = 1.0;
		star[i].col[3] = 1.0;
		theta = rand();
		phi = rand();
		star[i].pos[0] = r*sin(phi)*cos(theta);
		star[i].pos[1] = r*sin(phi)*sin(theta);
		star[i].pos[2] = r*cos(phi);
		i++;
	}


}


void Idle(void)
{

	if (a == 0){
		year_mercury = year_mercury;		
		year_venus =  year_venus;
		year_earth =  year_earth ;
		year_moon =   year_moon ;
		year_mars = year_mars;
		year_jupiter = year_jupiter;
		year_saturn = year_saturn;
		year_uranus = year_uranus;
		year_neptune = year_neptune;
		year_pluto = year_pluto;
		year_star = year_star;
	}
	else{
		year_mercury = year_mercury + (360.0 / MERCURY_YEAR);
		year_venus = year_venus + 360.0 / VENUS_YEAR;
		year_earth = year_earth + 360.0 / EARTH_YEAR;
		year_moon = year_moon + 360.0 / MOON_YEAR;
		year_mars = year_mars + 360.0 / MARS_YEAR;
		year_jupiter = year_jupiter + 360.0 / JUPITER_YEAR;
		year_saturn = year_saturn + 360.0 / SATURN_YEAR;
		year_uranus = year_uranus + 360.0 / URANUS_YEAR;
		year_neptune = year_neptune + 360.0 / NEPTUNE_YEAR;
		year_pluto = year_pluto + 360.0 / PLUTO_YEAR;
		year_star = year_star + 360.0 / SOLAR_YEAR;
	}

	if (b == 0){
		day_mercury = day_mercury;
		day_venus = day_venus;
		day_earth = day_earth;
		day_mars = day_mars;
		day_jupiter = day_jupiter;
		day_saturn = day_saturn;
		day_uranus = day_uranus;
		day_neptune = day_neptune;
		day_pluto = day_pluto;
	}
	else{
		day_mercury = day_mercury + 360 / MERCURY_DAY;
		day_venus = day_venus + 360 / VENUS_DAY;
		day_earth = day_earth + 360 / EARTH_DAY;
		day_mars = day_mars + 360 / MARS_DAY;
		day_jupiter = day_jupiter + 360 / JUPITER_DAY;
		day_saturn = day_saturn + 360 / SATURN_DAY;
		day_uranus = day_uranus + 360 / URANUS_DAY;
		day_neptune = day_neptune + 360 / NEPTUNE_DAY;
		day_pluto = day_pluto + 360 / PLUTO_DAY;

	}

	glutPostRedisplay();

}

void main(int argc, char** argv)
{
	// Initialization of GLUT Library
	glutInitWindowSize(800, 450);
	glutInitWindowPosition(100, 100);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Create a window with title specified
	glutCreateWindow("Li Yan's Homework: Solor System Animation");

	// Register different callback functions for GLUT to response 
	// with different events, e.g. window sizing, mouse click or
	// keyboard stroke
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutIdleFunc(Idle);
	glutMouseFunc(Mouse);
	glutMotionFunc(Drag);
	init();	// not GLUT call, initialize several parameters

	// Enter the GLUT event processing loop which never returns.
	// It will call different registered callback according to different events.
	glutMainLoop();
}
