#pragma once
#ifndef Explode_H
#define Explode_H
#include "Particle.h"
#include "GlobalVariables.h"
#include <list>
#include <memory>

using namespace std;

class Explode : public GameObject
{

public:
	Explode(float x, float y, float xVel, float yVel, float red, float green, float blue);
	void draw();
	int Health;
private:
	float red;
	float green;
	float blue;
	list<shared_ptr<GameObject>> particles;
};

#endif