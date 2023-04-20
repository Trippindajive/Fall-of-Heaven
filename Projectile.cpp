#include <cstdlib>
#include <iostream>
#include "Projectile.h"

Projectile::Projectile()
{
	projPosX = rand() % 500;
	projPosY = 0;
	projVelX = 0;
	projVelY = 0;
	projCollider.x = projPosX;
	projCollider.y = projPosY;
	projCollider.w = PROJECTILE_WIDTH;
	projCollider.h = PROJECTILE_HEIGHT;
}

void Projectile::move(/*SDL_Rect& otherpj,*/ SDL_Rect& player, Plank& plk)
{
	// set random seed for random random sequences
	srand(time(NULL));

	projPosY += rand() % 5 + 1;  // postion += velocity (random # from 1-5)
	projCollider.y = projPosY;
	// if projectile contacts the player
	if (/*checkCollision(projCollider, otherpj) ||*/ checkCollision(projCollider, player))  // If it collided, then move projectile back
	{
		
		//projVelY -= projVelY;
		projPosX = rand() % 500;
		projPosY = 0;
		//projPosX -= projVelY;
		//projPosY -= 250;
		projCollider.x = projPosX;
		projCollider.y = projPosY;
		plk.addScore(1);
		std::cout << "score is: " << plk.getScore() << "\n";
	}
	// if projectile falls thru bottom of screen
	if (projPosY >= 500)
	{
		projPosX = rand() % 500;
		projPosY = 0;
		projCollider.x = projPosX;
		projCollider.y = projPosY;
	}
	
}

bool Projectile::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Get sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	// Get sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	// If any sides from A overlap sides from B, then no collision
	// Less than because the coordinate system points downward
	if (bottomA < topB)
	{
		//std::cout << "didn't hit top right\n";
		return false;
	}
	if (topA > bottomB)
	{
		//std::cout << "didn't hit bottom right\n";
		return false;
	}
	if (rightA < leftB)
	{
		//std::cout << "didn't hit left\n";
		return false;
	}
	if (leftA > rightB)
	{
		//std::cout << "didn't hit right\n";
		return false;
	}

	// O.W. there is an overlap across the separting axis
	return true;
}


void Projectile::render(LTexture* gProjTexture, SDL_Renderer* gRenderer)
{
	gProjTexture->render(projPosX, projPosY, gRenderer);
}


int Projectile::getPosX()
{
	return projPosX;
}

int Projectile::getPosY()
{
	return projPosY;
}

SDL_Rect* Projectile::getCollider()
{
	return &projCollider;
}

void Projectile::setVelY(int val)
{
	projVelY += val;
}

int Projectile::getVelX()
{
	return projVelX;
}

int Projectile::getVelY()
{
	return projVelY;
}