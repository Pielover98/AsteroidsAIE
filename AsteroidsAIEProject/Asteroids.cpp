#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include "Asteroid.h"
#include "AlienSpaceShip.h"
#include "PlayerSpaceShip.h"
#include "GameObject.h"
#include "GlobalAsteroidVariables.h"
#include "BackGround.h"
#include "Level.h"
#include "Intro.h"
#include "Stars.h"
#include <time.h> 
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <freeglut.h>
#include <math.h>
#include <iostream>

using namespace std;


#define TIMER_DELAY 1000/60

void  display_obj(void);
void  handle_menu(int);
void  handle_rotation(int);
void  handle_mouse(int, int, int, int);

shared_ptr<BackGround> level;
shared_ptr<PlayerSpaceShip> player;


int    btn[3] = { 0 };
int    mouse_x, mouse_y;
bool leftPressed;
bool rightPressed;
bool firing;

void handle_rotation(int n)

{
	
	level->update();

	if (level->done)
	{
		unsigned int toTransfer = level->stars->getName();
		level = shared_ptr<Level>(new Level((rand() % MAX_SPAWN_ASTEROIDS) + level->current, player, level->player_lives.size(), level->score.getScore()));
		level->stars = shared_ptr<Stars>(new Stars(toTransfer));
	}


	glutPostRedisplay();
}

void display_obj(void)

{

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
	glEnable(GL_CULL_FACE); glCullFace(GL_BACK);
	level->draw();
	glutTimerFunc(TIMER_DELAY, handle_rotation, 0);

	glFlush();				

	glutSwapBuffers();			
}					


void handle_menu(int ID)




{
	switch (ID) {
	case 0:			
		exit(0);
		break;
	case 1:
	{
		player = shared_ptr<PlayerSpaceShip>(new PlayerSpaceShip());
		unsigned int toTransfer = level->stars->getName();
		level = shared_ptr<Level>(new Level((rand() % MAX_NEW_ASTEROIDS) + 1, player, 3, 0));
		level->stars = shared_ptr<Stars>(new Stars(toTransfer));
	}
	}


}					

void handle_mouse(int b, int s, int x, int y)







{
	if (s == GLUT_DOWN) {		
		btn[b] = 1;
	}
	else {
		btn[b] = 0;
	}

	mouse_x = x;
	mouse_y = glutGet(GLUT_WINDOW_HEIGHT) - y;
}					

void handle_left_right(int key, int i, int j)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		leftPressed = true;
		if (!rightPressed) {
			player->angularVelocityZ = player->ANGULAR_MAX;
		}
		break;
	case GLUT_KEY_RIGHT:
		rightPressed = true;
		if (!leftPressed) {
			player->angularVelocityZ = -player->ANGULAR_MAX;
		}
		break;
	}
}
void handle_left_right_release(int key, int i, int j)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		leftPressed = false;
		break;
	case GLUT_KEY_RIGHT:
		rightPressed = false;
		break;
	}
	player->angularVelocityZ = 0.0f;
}

void handle_key(unsigned char key, int i, int j)
{
	switch (key) {
	case 'x':
		player->acceleration = player->MaxAccel;
		player->moving = true;
		break;
	case 'z':
		if (!firing)
			level->makeShot();
		firing = true;
		break;
	}
}

void handle_key_up(unsigned char key, int i, int j)
{
	switch (key) {
	case 'x':
		player->acceleration = 0.0f;
		player->moving = false;
		break;
	case 'z':
		firing = false;
		break;
	}
}

void main(int argc, char *argv[])
{
	
	leftPressed = false;
	rightPressed = false;
	firing = false;

	srand(time(NULL));

	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


	glutCreateWindow("Asteroids Part 2");


	
	player = shared_ptr<PlayerSpaceShip>(new PlayerSpaceShip());
	level = shared_ptr<Intro>(new Intro());

	glutDisplayFunc(display_obj);	

	glutMouseFunc(handle_mouse);

	
	glutSpecialFunc(handle_left_right);
	glutSpecialUpFunc(handle_left_right_release);

	
	glutKeyboardFunc(handle_key);
	glutKeyboardUpFunc(handle_key_up);

	glutCreateMenu(handle_menu);	
	glutAddMenuEntry("Quit", 0);
	glutAddMenuEntry("New Game", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();
	gluPerspective(70, 1, 1, 35);

	glMatrixMode(GL_MODELVIEW);		
	glLoadIdentity();
	gluLookAt(0, 0, 25, 0, 0, -1, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	

	float  amb[] = { 0, 0, 0, 1 };	
	float  lt_amb[] = { .2, .2, .2, 1 };	
	float  lt_dif[] = { .8, .8, .8, 1 };	
	float  lt_pos[] = {			
		0, .39392, .91914, 0
	};
	float  lt_spc[] = { 0, 0, 0, 1 };	


										

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	

	glLightfv(GL_LIGHT0, GL_POSITION, lt_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lt_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lt_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lt_spc);

	

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glShadeModel(GL_FLAT);		
	glEnable(GL_NORMALIZE);		

								

	glClearDepth(1.0);			
	glEnable(GL_DEPTH);
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	glutTimerFunc(TIMER_DELAY, handle_rotation, 0);
	glutMainLoop();			


}					
