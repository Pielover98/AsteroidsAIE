#pragma once
#ifndef Collide_H
#define Collide_H

#include "Enemy.h"
#include "Asteroid.h"
#include "PlayerSpaceShip.h"
#include "Shot.h"
#include <memory>

using namespace std;

class Collide
{
public:
	Collide();
	bool shotAndAsteroid(shared_ptr<Asteroid> asteroid, shared_ptr<Shot> shot);
	bool shipAndAsteroid(shared_ptr<Asteroid> asteroid, shared_ptr<PlayerSpaceShip> playerShip);
	bool shipAndAsteroid(shared_ptr<Asteroid> asteroid, shared_ptr<Enemy> alienShip);
	bool shotAndShip(shared_ptr<Shot> shot, shared_ptr<PlayerSpaceShip> ship);
	bool shotAndShip(shared_ptr<Shot> shot, shared_ptr<Enemy> ship);
	bool shipAndShip(shared_ptr<PlayerSpaceShip> player, shared_ptr<Enemy> alien);
	float dist(float xOne, float xTwo, float yOne, float yTwo);
private:
	bool intersect(float xOne, float xTwo, float yOne, float yTwo, float xCenter, float yCenter, float radius);
	float smallIntersectX(float dx, float dy, float d, float D, float radius);
	float smallIntersectY(float dx, float dy, float d, float D, float radius);
	float largeIntersectX(float dx, float dy, float d, float D, float radius);
	float largeIntersectY(float dx, float dy, float d, float D, float radius);
	bool lineLineIntersection(float xOne, float yOne, float xTwo, float yTwo, float xThree, float yThree, float xFour, float yFour);
	int sgn(float toCheck);
};


#endif