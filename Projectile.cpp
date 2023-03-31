#include "Projectile.h"

Projectile::Projectile()
{
	projPosX = 350;
	projPosY = 100;
	projVelX = 0;
	projVelY = 0;
	projCollider.x = projPosX;
	projCollider.y = projPosY;
	projCollider.w = PROJECTILE_WIDTH;
	projCollider.h = PROJECTILE_HEIGHT;
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	return false;
}

void Projectile::render(LTexture* gProjTexture, SDL_Renderer* gRenderer)
{
	gProjTexture->render(projPosX, projPosY, gRenderer);
}


int Projectile::getPosX()
{
	return -1;
}

int Projectile::getPosY()
{
	return -1;
}

SDL_Rect* Projectile::getCollider()
{
	return NULL;
}