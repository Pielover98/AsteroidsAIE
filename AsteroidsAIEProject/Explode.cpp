#include "Explode.h"

#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <freeglut.h>
#include "GlobalVariables.h"
#include "Movement.h"
#include "Particle.h"
#include <list>
#include <memory>
#include <iostream>

using namespace std;

Explode::Explode(float X, float Y, float xVel, float yVel, float red, float green, float blue)
{
	angle = 0.0f;
	angleX = 0.0f;
	angleY = 0.0f;
	angleZ = 0.0f;
	angularVelocityX = 0.0f;
	angularVelocityY = 0.0f;
	angularVelocityZ = 0.0f;
	x = X;
	y = Y;
	z = 0;
	velocityZ = 0;
	velocityX = 0;
	velocityY = 0;

	Health = 0;

	for (int i = 0; i < PARTICLE_COUNT; i++)
	{
		particles.push_back(shared_ptr<GameObject>(new Particle(X, Y, xVel, yVel, red, green, blue)));
	}
}

void Explode::draw()
{
	Movement mover = Movement();

	for each(shared_ptr<GameObject> part in particles)
	{
		part->count = Health;
		glPushMatrix();

		if (Health > MAX_Explode_Health / 4)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
			part->draw();
			glDisable(GL_BLEND);
		}
		else
		{
			part->draw();
		}
		glPopMatrix();

		

		mover.move(part);
		mover.rotate(part);
		mover.clip(part);

	}

}