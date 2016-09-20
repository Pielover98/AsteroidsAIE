#include "AlienSpaceShip.h"
#include "GameObject.h"
#include "GlobalAsteroidVariables.h"

#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include <iostream>
#include <math.h>
#include <string.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <freeglut.h>

using namespace std;

AlienSpaceShip::AlienSpaceShip()
{
	is_small = false;
	alive = false;
	dead = false;
	angle = 0.0f;
	angleX = 0.0f;
	angleY = 0.0f;
	angleZ = 0.0f;
	angularVelocityX = 0.0f;
	angularVelocityY = 0.0f;
	angularVelocityZ = 0.0f;
	x = 2;
	y = 2;
	z = 0;
	velocityZ = 0;
	velocityX = 0;
	velocityY = 0;
	height = .4;
	width = 1.0;
	MaxVelocity = 2.0;
	shotVelocity = 0.29f;
	time = 1;

	p_a = 30;
	p_p = 20;
	p_r = 50;

	init();
}

AlienSpaceShip::AlienSpaceShip(bool is_small_now)
{
	is_small = is_small_now;
	alive = false;
	dead = false;
	angle = 0.0f;
	angleX = 0.0f;
	angleY = 0.0f;
	angleZ = 0.0f;
	angularVelocityX = 0.0f;
	angularVelocityY = 0.0f;
	angularVelocityZ = 0.0f;
	x = 2;
	y = 2;
	z = 0;
	velocityZ = 0;
	velocityX = 0;
	velocityY = 0;
	MaxVelocity = 2.0;
	shotVelocity = 0.29f;
	time = 1;

	if (is_small)
	{
		height = .3;
		width = .7;
		points = SMALL_ALIEN_POINTS;
		p_a = 40;
		p_p = 50;
		p_r = 10;
	}
	else
	{
		height = .4;
		width = 1.0;
		points = LARGE_ALIEN_POINTS;
		p_a = 30;
		p_p = 20;
		p_r = 50;
	}
	init();
}

void AlienSpaceShip::update(long count, long points, int asteroids)
{
	if (alive)
	{
		if (time % 50 == 0)
		{
			time = 1;
			if (is_small)
			{
				velocityY = fRand(SMALL_ALIEN_VELOCITY, -SMALL_ALIEN_VELOCITY);
			}
			else
			{
				velocityY = fRand(SMALL_ALIEN_VELOCITY, -SMALL_ALIEN_VELOCITY);
			}
		}
	}
	else
	{
		if (is_small)
		{
			if (!dead && count > 960 && asteroids <= 3 && points > 10000 && time % 120 == 0)
			{
				alive = true;
				if (rand() % 2)
				{
					x = 15.0f;
					y = fRand(15.0f, -15.0f);
					velocityX = -SMALL_ALIEN_VELOCITY;
					velocityY = fRand(SMALL_ALIEN_VELOCITY, -SMALL_ALIEN_VELOCITY);
				}
				else
				{
					x = -15.0f;
					y = fRand(15.0f, -15.0f);
					velocityX = SMALL_ALIEN_VELOCITY;
					velocityY = fRand(SMALL_ALIEN_VELOCITY, -SMALL_ALIEN_VELOCITY);
				}


			}
		}
		else
		{
			if (!dead && count > 760 && asteroids <= 3)
			{
				alive = true;
				if (rand() % 2)
				{
					x = 15.0f;
					y = fRand(15.0f, -15.0f);
					velocityX = -ALIEN_VELOCITY;
					velocityY = fRand(ALIEN_VELOCITY, -ALIEN_VELOCITY);
				}
				else
				{
					x = -15.0f;
					y = fRand(15.0f, -15.0f);
					velocityX = ALIEN_VELOCITY;
					velocityY = fRand(ALIEN_VELOCITY, -ALIEN_VELOCITY);
				}


			}
		}
	}
	time++;
}

void AlienSpaceShip::init()
{
	GLfloat materialA[] = { 0.329412, 0.329412, 0.329412, 0 };
	GLfloat materialB[] = { 0.309804, 0.309804, 0.184314, 0 };

	name = glGenLists(1);
	glNewList(name, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialA);

	glPushMatrix();
	glRotatef(270.0, 1.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glutSolidCone(width, height, 12, 4);
	glPopMatrix();
	glPushMatrix();
	glutSolidCone(width, height, 12, 4);
	glPopMatrix();
	glTranslatef(0, 0, height);

	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialB);

	glutSolidSphere(height / 2, 7, 7);
	glPopMatrix();
	glEndList();
}

void AlienSpaceShip::draw()
{
	if (alive)
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glPushMatrix();
		glRotatef(angle, angleX, angleY, angleZ);
		glCallList(name);
		glPopMatrix();
		glPopMatrix();
	}
}