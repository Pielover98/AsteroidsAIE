#pragma once
#ifndef Player_H
#define Player_H
#include "GameObject.h"

class Player: public GameObject
{
	
public:
	Player();
	void draw();
	bool moving;
	bool rotating;
	float shotVelocity;
	float ANGULAR_MAX;  
	bool alive;

private:
	unsigned int name;
	void init();

};

#endif