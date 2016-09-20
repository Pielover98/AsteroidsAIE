#pragma once
#ifndef SHOTExplode_H
#define SHOTExplode_H
#include "Particle.h"
#include "GlobalVariables.h"
#include "Explode.h"
#include <list>
#include <memory>

using namespace std;

class ShotExplode : public Explode
{

public:
	ShotExplode(float x, float y, float xVel, float yVel, float red, float green, float blue);
	void draw();
private:
	float red;
	float green;
	float blue;
	list<shared_ptr<GameObject>> particles;
};

#endif