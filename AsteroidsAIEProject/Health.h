#pragma once
#ifndef Health_H
#define Health_H
#include "GameObject.h"

using namespace std;

class Health : public GameObject
{
public:
	Health(int pos);
	void draw();
private:
	void init();
	unsigned int name;
};

#endif