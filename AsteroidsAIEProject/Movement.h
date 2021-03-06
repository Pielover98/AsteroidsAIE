#pragma once
#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <memory>

using namespace std;

class Movement
{
public:
	void clip(shared_ptr<GameObject> object);
	void clip(shared_ptr<Player> object);
	void rotate(shared_ptr<GameObject> object);
	void rotate(shared_ptr<Player> object);
	void move(shared_ptr<GameObject> object);
	void move(shared_ptr<Player> object);
	void move(shared_ptr<Enemy> object);
};

#endif
