#pragma once
#ifndef LEVEL_H
#define LEVEL_H
#include "GameObject.h"
#include "Collide.h"
#include "Player.h"
#include "Explode.h"
#include "Enemy.h"
#include "BackGround.h"
#include "Health.h"
#include "Movement.h"
#include "Score.h"
#include "Shot.h"
#include <memory>
#include <list>

using namespace std;

class Level : public BackGround
{
public:
	Level();
	Level(int n, shared_ptr<Player> player, int lives_to_start, long score_to_start);
	~Level();
	void draw();
	void update();
	void removeHealth();
	void makeShot();
private:
	list<shared_ptr<GameObject>> objects;
	list<shared_ptr<Shot>> pshots;
	list<shared_ptr<Shot>> ashots;
	list<shared_ptr<Explode>> Explodes;
	shared_ptr<Player> playerShip;
	shared_ptr<Enemy> alienShip;
	Movement mover;
	Collide collider;
	int deadCount;
	void makeAlienShot();
	float getAngle(float x, float y);
};

#endif