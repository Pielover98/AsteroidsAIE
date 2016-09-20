#pragma once
#ifndef IntroScreen_H
#define IntroScreen_H
#include "GameObject.h"
#include "BackGround.h"

using namespace std;

class IntroScreen : public BackGround
{
public:
	IntroScreen();
	void draw();
	void update();
	void makeShot();
};

#endif