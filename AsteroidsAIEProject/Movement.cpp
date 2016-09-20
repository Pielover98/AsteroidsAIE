#include "Movement.h"
#include "GameObject.h"
#include "GlobalVariables.h"
#include "Enemy.h"
#include "Player.h"
#include <memory>
#include "math.h"
#include <iostream>

using namespace std;

void Movement::clip(shared_ptr<GameObject> object)
{
	
	if (object->angle > CIRCLE)
		object->angle = object->angle - CIRCLE;
	if (object->angle < -CIRCLE)
		object->angle = object->angle + CIRCLE;
}

void Movement::clip(shared_ptr<Player> object)
{
	
	if (object->angle > CIRCLE)
		object->angle = object->angle - CIRCLE;
	if (object->angle < -CIRCLE)
		object->angle = object->angle + CIRCLE;
}

void Movement::rotate(shared_ptr<GameObject> object)
{
	
	object->angleX += object->angularVelocityX;
	object->angleY += object->angularVelocityY;
	object->angleZ += object->angularVelocityZ;

	
	object->angle = (float)sqrt((double)(pow(object->angleX, 2) + pow(object->angleY, 2) + pow(object->angleZ, 2)));
	clip(object);
}

void Movement::rotate(shared_ptr<Player> object)
{
	
	object->angleX += object->angularVelocityX;
	object->angleY += object->angularVelocityY;
	object->angleZ += object->angularVelocityZ;

	
	object->angle = (float)sqrt((double)(pow(object->angleX, 2) + pow(object->angleY, 2) + pow(object->angleZ, 2)));
	clip(object);
}

void Movement::move(shared_ptr<GameObject> object)
{

	object->x += object->velocityX;
	object->y += object->velocityY;
	object->z += object->velocityZ;

	
	if (object->x > WIDTH)
		object->x = -WIDTH + 0.1f;
	else if (object->x < -WIDTH)
		object->x = WIDTH - 0.1f;
	if (object->y > HEIGHT)
		object->y = -HEIGHT + 0.1f;
	else if (object->y < -HEIGHT)
		object->y = HEIGHT - 0.1f;
}

void Movement::move(shared_ptr<Player> object)
{
	
	double angle = object->angle*PI / HALF_CIRCLE;

	if (object->angleZ < 0)
		angle = -angle;


	if (object->moving)
	{
		object->velocityX += (float)object->acceleration*((float)sin(angle));
		object->velocityY -= (float)object->acceleration*((float)cos(angle));

		if (object->velocityX > object->MaxVelocity)
		{
			object->velocityX = object->MaxVelocity;
		}
		else if (object->velocityX < -object->MaxVelocity)
		{
			object->velocityX = -object->MaxVelocity;
		}
		if (object->velocityY > object->MaxVelocity)
		{
			object->velocityY = object->MaxVelocity;
		}
		else if (object->velocityY < -object->MaxVelocity)
		{
			object->velocityY = -object->MaxVelocity;
		}
	}
	else
	{
		float vel = sqrt(object->velocityX*object->velocityX + object->velocityY*object->velocityY);

		if (vel > DECEL_MIN)
		{
			object->velocityX -= DECEL_FACTOR*object->velocityX / vel;

			object->velocityY -= DECEL_FACTOR*object->velocityY / vel;
		}
		else
		{
			object->velocityX = 0;
			object->velocityY = 0;
		}

	}

	object->x += object->velocityX;
	object->y += object->velocityY;

	
	if (object->x > WIDTH)
		object->x = -WIDTH + 0.1f;
	else if (object->x < -WIDTH)
		object->x = WIDTH - 0.1f;
	if (object->y > HEIGHT)
		object->y = -HEIGHT + 0.1f;
	else if (object->y < -HEIGHT)
		object->y = HEIGHT - 0.1f;
}

void Movement::move(shared_ptr<Enemy> object)
{
	object->x += object->velocityX;
	object->y += object->velocityY;
	object->z += object->velocityZ;

	
	if (object->x > WIDTH)
	{
		object->alive = false;
		object->dead = true;
	}
	else if (object->x < -WIDTH)
	{
		object->alive = false;
		object->dead = true;
	}
	if (object->y > HEIGHT)
		object->y = -HEIGHT + 0.1f;
	else if (object->y < -HEIGHT)
		object->y = HEIGHT - 0.1f;
}