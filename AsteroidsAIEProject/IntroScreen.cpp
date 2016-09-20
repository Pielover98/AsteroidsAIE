#include "IntroScreen.h"

#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include "GlobalVariables.h"
#include "BackGround.h"
#include "Stars.h"
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <freeglut.h>
#include <sstream>
#include <iostream>

using namespace std;

IntroScreen::IntroScreen()
{
	lives = 3;
	game_over = false;
	safe = true;
	score = Score();
	count = 0;

	current = 1;
	done = false;
	stars = shared_ptr<Stars>(new Stars());
}

void IntroScreen::makeShot()
{
}

void IntroScreen::draw()
{
	stars->draw();

	string value = "Asteroids Remake by Xavier";

	
	int length = value.size();
	float size = 0;

	

	GLfloat material[] = { 63 / 255.0, 69 / 255.0, 101 / 255.0, 0 };
	GLfloat shine[] = { 2 };
	GLfloat reflect[] = { 26 / 255.0, 39 / 255.0, 105 / 255.0, 0 };
	GLfloat none[] = { 0,0,0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, reflect);

	for (int i = 0; i < length; i++)
	{
		size += glutStrokeWidth(GLUT_STROKE_ROMAN, value[i]);
	}

	glPushMatrix();
	glTranslatef(-size / 152.38, 0.0, 2);
	glScalef(2 / 152.38, 2 / 152.38, 2 / 152.38);
	for (int i = 0; i < length; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, value[i]);
	}

	glPopMatrix();

	value = "Right click to start a new game or quit. Controls with X, Z, Left, Right";
	
	length = value.size();
	size = 0;

	

	for (int i = 0; i < length; i++)
	{
		size += glutStrokeWidth(GLUT_STROKE_ROMAN, value[i]);
	}

	glPushMatrix();
	glTranslatef(-size / 304.76, -10, 2);
	glScalef(1 / 152.38, 1 / 152.38, 1 / 152.38);
	for (int i = 0; i < length; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, value[i]);
	}
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_EMISSION, none);
}

void IntroScreen::update()
{
}