#include "ShotExplode.h"
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
#include "ShotParticle.h"
#include <list>
#include <memory>
#include <iostream>

using namespace std;

ShotExplode::ShotExplode(float X, float Y, float xVel, float yVel, float red, float green, float blue) : Explode(X, Y, xVel, yVel, red, green, blue)
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

	for (int i = 0; i < SHOT_PARTICLE_COUNT; i++)
	{
		particles.push_back(shared_ptr<GameObject>(new ShotParticle(X, Y, xVel, yVel)));
	}
}

void ShotExplode::draw()
{
	Movement mover = Movement();

	if (Health < MAX_SHOT_Explode_Health)
	{
		for each(shared_ptr<GameObject> part in particles)
		{
			part->count = Health;
			glPushMatrix();

			if (Health > MAX_SHOT_Explode_Health / 3)
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
	Explode::draw();

}