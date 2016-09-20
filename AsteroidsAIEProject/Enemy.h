#pragma once
#ifndef Enemy_H
#define Enemy_H
#include "GameObject.h"

class Enemy : public GameObject
{

public:
	Enemy();
	Enemy(bool is_small_now);
	void update(long count, long points, int asteroids);
	void draw();
	bool alive;
	bool dead;
	bool is_small;
	float height;
	float width;
	float shotVelocity;
	int p_p;
	int p_a;
	int p_r;
private:
	void init();
	unsigned int name;
	long time;
};

#endif