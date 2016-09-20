#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include "Explode.h"
#include "ShotExplode.h"
#include "Asteroid.h"
#include "Enemy.h"
#include "Player.h"
#include "GameObject.h"
#include "Movement.h"
#include "Collide.h"
#include "GlobalVariables.h"
#include "BackGround.h"
#include "Shot.h"
#include "Score.h"
#include "Level.h"
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <freeglut.h>
#include <math.h>
#include <memory>
#include <list>

using namespace std;


Level::Level()
{
	mover = Movement();
	deadCount = 0;
	collider = Collide();
	alienShip = shared_ptr<Enemy>(new Enemy());

	lives = 3;
	game_over = false;
	safe = true;
	score = Score();
	count = 0;

	current = 1;
	done = false;
	for (int i = 0; i < 1; i++)
	{
		objects.push_back(shared_ptr<GameObject>(new Asteroid(1)));
	}
	for (int i = 0; i < lives; i++)
	{
		player_lives.push_back(shared_ptr<GameObject>(new Health(i)));
	}
}

Level::Level(int numberOfAsteroids, shared_ptr<Player> player, int lives_to_start, long score_to_start)
{

	lives = lives_to_start;
	game_over = false;
	safe = true;
	score = Score(score_to_start);

	
	if (numberOfAsteroids > MAX_ASTEROIDS)
		numberOfAsteroids = MAX_ASTEROIDS;

	playerShip = player;
	collider = Collide();
	mover = Movement();
	deadCount = 0;
	count = 0;

	done = false;
	current = numberOfAsteroids;
	alienShip = shared_ptr<Enemy>(new Enemy(false));

	

	for (int i = 0; i < numberOfAsteroids; i++)
	{
		objects.push_back(shared_ptr<GameObject>(new Asteroid(1)));
	}
	for (int i = 0; i < lives; i++)
	{
		player_lives.push_back(shared_ptr<GameObject>(new Health(i)));
	}

}

Level::~Level()
{
	

	
	
	
	
}

void Level::draw()
{
	stars->draw();
	playerShip->draw();
	alienShip->draw();

	for each(shared_ptr<GameObject> toDraw in objects)
	{
		toDraw->draw();
	}

	for each(shared_ptr<GameObject> toDraw in pshots)
	{
		toDraw->draw();
	}

	for each(shared_ptr<GameObject> toDraw in ashots)
	{
		toDraw->draw();
	}

	for each(shared_ptr<Explode> toDraw in Explodes)
	{
		toDraw->draw();
	}

	for each(shared_ptr<GameObject> toDraw in player_lives)
	{
		toDraw->draw();
	}

	score.draw();

	if (game_over)
	{
		string value = "Game Over";

		
		int length = value.size();
		float size = 0;

		

		GLfloat material[] = { 63 / 255.0, 69 / 255.0, 101 / 255.0, 0 };
		GLfloat shine[] = { 2 };
		GLfloat reflect[] = { 26 / 255.0, 39 / 255.0, 105 / 255.0, 0 };
		GLfloat none[] = { 0,0,0 };

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material);
		glMaterialfv(GL_FRONT, GL_SHININESS, shine);
		glMaterialfv(GL_FRONT, GL_EMISSION, reflect);

		for (int i = 0; i < length; i++)
		{
			size += glutStrokeWidth(GLUT_STROKE_ROMAN, value[i]);
		}

		glPushMatrix();
		glTranslatef(-size / 152.38, 0.0, 2);
		glScalef(2 / 152.38, 2 / 152.38, 2 / 152.38);
		for (int i = 0; i < length; i++)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, value[i]);
		}

		glPopMatrix();

		value = "Right click to start a new game or quit.";

		
		length = value.size();
		size = 0;

		

		for (int i = 0; i < length; i++)
		{
			size += glutStrokeWidth(GLUT_STROKE_ROMAN, value[i]);
		}

		glPushMatrix();
		glTranslatef(-size / 304.76, -10, 2);
		glScalef(1 / 152.38, 1 / 152.38, 1 / 152.38);
		for (int i = 0; i < length; i++)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, value[i]);
		}

		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, none);
	}
}

void Level::update()
{
	list<shared_ptr<Shot>> shotsTemp = pshots;
	list<shared_ptr<GameObject>> objectsTemp;

	if (objects.size() > 0 || Explodes.size() > 0 || alienShip->alive)
	{

		objectsTemp = objects;

		
		mover.rotate(playerShip);
		mover.move(playerShip);

		mover.move(alienShip);

		for each(shared_ptr<GameObject> toUpdate in objects)
		{
			mover.rotate(toUpdate);
			mover.move(toUpdate);
		}
		for each(shared_ptr<GameObject> toUpdate in player_lives)
		{
			mover.rotate(toUpdate);
		}


		
		if (!playerShip->alive && !game_over)
		{
			if (deadCount > FRAMES_ON_DEATH && safe)
			{
				deadCount = 0;

				


				
				playerShip->x = 0.0f;
				playerShip->y = 0.0f;
				playerShip->alive = true;
			}
			else
			{
				deadCount++;
			}
		}

		safe = true;

		
		for each(shared_ptr<GameObject> object in objectsTemp)
		{

			if (collider.dist(0.0f, object->x, 0.0f, object->y) < SAFE_ZONE)
				safe = false;

			shotsTemp = pshots;

			
			shared_ptr<Asteroid> asteroid = dynamic_pointer_cast<Asteroid>(object);
			
			if (asteroid.use_count() > 0)
			{
				
				
				for each(shared_ptr<Shot> deadly in shotsTemp)
				{
					
					if (collider.shotAndAsteroid(asteroid, deadly))
					{
						
						Explodes.push_back(shared_ptr<ShotExplode>(new ShotExplode(asteroid->x, asteroid->y, deadly->velocityX / 2, deadly->velocityY / 2, 107 / 255.0, 34 / 255.0, 34 / 255.0)));

						
						list<shared_ptr<GameObject>> toAdd = asteroid->split(deadly->velocityX, deadly->velocityY);

						
						for each(shared_ptr<GameObject> add in toAdd)
							objects.push_front(add);

						
						if (score.addScore(object->points))
							player_lives.push_back(shared_ptr<GameObject>(new Health(player_lives.size())));

						
						objects.remove(object);

						
						pshots.remove(deadly);

					}

				}

				shotsTemp = ashots;

				for each(shared_ptr<Shot> deadly in shotsTemp)
				{
					
					if (collider.shotAndAsteroid(asteroid, deadly))
					{
						
						Explodes.push_back(shared_ptr<ShotExplode>(new ShotExplode(asteroid->x, asteroid->y, deadly->velocityX, deadly->velocityY, 107 / 255.0, 34 / 255.0, 34 / 255.0)));

						
						list<shared_ptr<GameObject>> toAdd = asteroid->split(deadly->velocityX, deadly->velocityY);

						
						for each(shared_ptr<GameObject> add in toAdd)
							objects.push_front(add);

						
						objects.remove(object);

						
						ashots.remove(deadly);

					}

				}

				
				float dist = collider.dist(playerShip->x, asteroid->x, playerShip->y, asteroid->y);

				
				if (dist < COLLISION_RADIUS)
				{

					
					if (playerShip->alive && collider.shipAndAsteroid(asteroid, playerShip))
					{
						
						playerShip->alive = false;
						removeHealth();

						
						Explodes.push_back(shared_ptr<Explode>(new Explode(playerShip->x, playerShip->y, asteroid->velocityX / 2, asteroid->velocityY / 2, 63 / 255.0f, 69 / 255.0f, 101 / 255.0f)));
						Explodes.push_back(shared_ptr<Explode>(new Explode(asteroid->x, asteroid->y, playerShip->velocityX / 2, playerShip->velocityY / 2, 107 / 255.0, 34 / 255.0, 34 / 255.0)));

						
						float dx = playerShip->x - asteroid->x;
						float dy = playerShip->y - asteroid->y;

						
						list<shared_ptr<GameObject>> toAdd = asteroid->split(dx, dy);

						
						for each(shared_ptr<GameObject> add in toAdd)
							objects.push_front(add);

						
						objects.remove(asteroid);

						
						playerShip->acceleration = 0;
						playerShip->velocityX = 0;
						playerShip->velocityY = 0;
						playerShip->angle = 0;
					}
				}

				
				dist = collider.dist(alienShip->x, asteroid->x, alienShip->y, asteroid->y);

				
				if (dist < COLLISION_RADIUS)
				{
					
					if (alienShip->alive && collider.shipAndAsteroid(asteroid, alienShip))
					{
						
						alienShip->alive = false;
						alienShip->dead = true;

						
						Explodes.push_back(shared_ptr<Explode>(new Explode(alienShip->x, alienShip->y, asteroid->velocityX / 2, asteroid->velocityY / 2, 0.329412, 0.329412, 0.329412)));
						Explodes.push_back(shared_ptr<Explode>(new Explode(asteroid->x, asteroid->y, alienShip->velocityX / 2, alienShip->velocityY / 2, 107 / 255.0, 34 / 255.0, 34 / 255.0)));


						
						float dx = alienShip->x - asteroid->x;
						float dy = alienShip->y - asteroid->y;

						
						list<shared_ptr<GameObject>> toAdd = asteroid->split(dx, dy);

						
						for each(shared_ptr<GameObject> add in toAdd)
							objects.push_front(add);

						
						objects.remove(asteroid);

						
						alienShip->acceleration = 0;
						alienShip->velocityX = 0;
						alienShip->velocityY = 0;
						alienShip->angle = 0;
					}
				}


			}

		}

		
		if (alienShip->alive)
		{
			shotsTemp = pshots;

			for each(shared_ptr<Shot> deadly in shotsTemp)
			{
				if (collider.dist(deadly->x, alienShip->x, deadly->y, alienShip->y) < COLLISION_RADIUS)
				{
					
					if (collider.shotAndShip(deadly, alienShip))
					{
						
						alienShip->alive = false;
						alienShip->dead = true;
						if (score.addScore(alienShip->points))
							player_lives.push_back(shared_ptr<GameObject>(new Health(player_lives.size())));

						Explodes.push_back(shared_ptr<ShotExplode>(new ShotExplode(alienShip->x, alienShip->y, deadly->velocityX, deadly->velocityY, 0.329412, 0.329412, 0.329412)));

						
						pshots.remove(deadly);

						
						alienShip->acceleration = 0;
						alienShip->velocityX = 0;
						alienShip->velocityY = 0;
						alienShip->angle = 0;
					}
				}
			}
		}


		
		if (playerShip->alive)
		{
			shotsTemp = ashots;

			for each(shared_ptr<Shot> deadly in shotsTemp)
			{
				if (collider.dist(deadly->x, playerShip->x, deadly->y, playerShip->y) < COLLISION_RADIUS)
				{
					
					if (collider.shotAndShip(deadly, playerShip))
					{
						
						playerShip->alive = false;
						pshots.remove(deadly);
						removeHealth();

						
						Explodes.push_back(shared_ptr<ShotExplode>(new ShotExplode(playerShip->x, playerShip->y, deadly->velocityX, deadly->velocityY, 63 / 255.0f, 69 / 255.0f, 101 / 255.0f)));


						
						playerShip->acceleration = 0;
						playerShip->velocityX = 0;
						playerShip->velocityY = 0;
						playerShip->angle = 0;
					}
				}
			}
		}

		
		if (playerShip->alive && alienShip->alive && collider.dist(playerShip->x, alienShip->x, playerShip->y, alienShip->y) < COLLISION_RADIUS)
		{
			if (collider.shipAndShip(playerShip, alienShip))
			{
				
				playerShip->alive = false;
				removeHealth();

				
				Explodes.push_back(shared_ptr<Explode>(new Explode(playerShip->x, playerShip->y, alienShip->velocityX / 2, alienShip->velocityY / 2, 63 / 255.0f, 69 / 255.0f, 101 / 255.0f)));
				Explodes.push_back(shared_ptr<Explode>(new Explode(alienShip->x, alienShip->y, alienShip->velocityX / 2, playerShip->velocityY / 2, 0.329412, 0.329412, 0.329412)));


				
				playerShip->acceleration = 0;
				playerShip->velocityX = 0;
				playerShip->velocityY = 0;
				playerShip->angle = 0;

				
				alienShip->alive = false;
				alienShip->dead = true;

				
				alienShip->acceleration = 0;
				alienShip->velocityX = 0;
				alienShip->velocityY = 0;
				alienShip->angle = 0;
			}
		}

		shotsTemp = pshots;

		for each(shared_ptr<Shot> toUpdate in shotsTemp)
		{
			
			
			
			if (toUpdate->HealthCount > MAX_SHOT_Health)
				pshots.pop_front();
			else
			{
				
				mover.move(toUpdate);

				
				toUpdate->HealthCount++;
			}
		}

		list<shared_ptr<Explode>> ExplodesTemp = Explodes;

		for each(shared_ptr<Explode> toUpdate in ExplodesTemp)
		{
			
			
			
			if (toUpdate->Health > MAX_Explode_Health)
				Explodes.pop_front();
			else
				toUpdate->Health++;

		}

		shotsTemp = ashots;

		for each(shared_ptr<Shot> toUpdate in shotsTemp)
		{
			
			
			
			if (toUpdate->HealthCount > MAX_SHOT_Health)
				ashots.pop_front();
			else
			{
				
				mover.move(toUpdate);

				
				toUpdate->HealthCount++;
			}
		}
		if (alienShip->alive && ashots.size() == 0)
		{
			makeAlienShot();
		}

		if (alienShip->dead && !alienShip->is_small)
			alienShip = shared_ptr<Enemy>(new Enemy(true));
		
		alienShip->update(count++, score.getScore(), objects.size());


	}
	else
	{
		done = true;
	}

}

void Level::makeShot()
{
	if (playerShip->alive)
	{
		
		double angle = playerShip->angle*PI / 180;

		if (playerShip->angleZ < 0)
			angle = -angle;

		float xVel = playerShip->shotVelocity*sin(angle) + playerShip->velocityX;
		float yVel = -playerShip->shotVelocity*cos(angle) + playerShip->velocityY;

		if (pshots.size() < MAX_SHOTS)
			pshots.push_back(shared_ptr<Shot>(new Shot(playerShip->x, playerShip->y, xVel, yVel, playerShip->angle)));
		
	}
}

void Level::removeHealth()
{
	player_lives.pop_back();
	if (player_lives.size() == 0)
		game_over = true;
}

void Level::makeAlienShot()
{
	int player_s = 0;
	int player_f = alienShip->p_p - 1;
	int asteroid_s = player_f + 1;
	int asteroid_f = player_f + alienShip->p_a;
	float dirX = 0;
	float dirY = 0;
	float xVel = 0;
	float yVel = 0;
	float angle = 0;

	int random = rand() % 101;

	if (random >= player_s && random <= player_f)
	{
		dirX = playerShip->x - (alienShip->x + alienShip->velocityX);
		dirY = playerShip->y - (alienShip->y + alienShip->velocityY);

		shared_ptr<Player> toShoot = playerShip;

		
		for (int i = 0; i < MAX_SHOT_Health; i++)
		{
			float x = toShoot->x + toShoot->velocityX*i;
			float y = toShoot->y + toShoot->velocityY*i;

			float x_a = alienShip->x + alienShip->velocityX*i;
			float y_a = alienShip->y + alienShip->velocityY*i;

			float distance = collider.dist(x, x_a, y, y_a);

			if (abs(distance - alienShip->shotVelocity*i) <= SHIP_BACK)
			{
				dirX = x - x_a;
				dirY = y - y_a;
				break;
			}

		}

		double mag = sqrt(dirX*dirX + dirY*dirY);

		xVel = alienShip->shotVelocity*(dirX / mag) + alienShip->velocityX;
		yVel = -alienShip->shotVelocity*(dirY / mag) + alienShip->velocityY;

		ashots.push_back(shared_ptr<Shot>(new Shot(alienShip->x, alienShip->y, xVel, yVel, 0)));
	}
	else if (random >= asteroid_s && random <= asteroid_f && objects.size() > 1)
	{
		shared_ptr<GameObject> toShoot;

		float close = FLT_MAX;
		float current = 0.0f;

		for each(shared_ptr<GameObject> asteroid in objects)
		{
			current = collider.dist(asteroid->x, alienShip->x, asteroid->y, alienShip->y);

			if (current < close)
			{
				toShoot = asteroid;
				close = current;
			}
		}

		dirX = (toShoot->x + toShoot->velocityX) - (alienShip->x + alienShip->velocityX);
		dirY = (toShoot->y + toShoot->velocityY) - (alienShip->y + alienShip->velocityY);

		
		for (int i = 1; i <= MAX_SHOT_Health; i++)
		{
			float x = toShoot->x + toShoot->velocityX*i;
			float y = toShoot->y + toShoot->velocityY*i;

			float x_a = alienShip->x + alienShip->velocityX*i;
			float y_a = alienShip->y + alienShip->velocityY*i;

			float distance = collider.dist(x, x_a, y, y_a);

			if (abs(distance - alienShip->shotVelocity*i) <= .5)
			{
				dirX = x - x_a;
				dirY = y - y_a;
				break;
			}

		}

		double mag = sqrt(dirX*dirX + dirY*dirY);

		xVel = alienShip->shotVelocity*(dirX / mag) + alienShip->velocityX;
		yVel = -alienShip->shotVelocity*(dirY / mag) + alienShip->velocityY;

		ashots.push_back(shared_ptr<Shot>(new Shot(alienShip->x, alienShip->y, xVel, yVel, 0)));
	}
	else
	{
		dirX = fRand(-15.0, 15.0) - alienShip->x;
		dirY = fRand(-15.0, 15.0) - alienShip->y;

		angle = getAngle(dirX, dirY);

		xVel = alienShip->shotVelocity*sin(angle) + alienShip->velocityX;
		yVel = -alienShip->shotVelocity*cos(angle) + alienShip->velocityY;

		ashots.push_back(shared_ptr<Shot>(new Shot(alienShip->x, alienShip->y, xVel, yVel, angle)));
	}
}


float Level::getAngle(float x, float y)
{
	if (x == 0)
		return 0;
	return (float)atan2((double)y, (double)x) - PI;
}