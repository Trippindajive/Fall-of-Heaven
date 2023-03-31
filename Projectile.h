#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED	

#include <SDL.h>
#include "TextureWrapper.h"

class Projectile
{
public:
	static const int PROJECTILE_WIDTH = 10;
	static const int PROJECTILE_HEIGHT = 20;

	Projectile();

	bool checkCollision(SDL_Rect, SDL_Rect);

	void render(LTexture*, SDL_Renderer*);

	int getPosX();
	int getPosY();
	SDL_Rect* getCollider();

private:
	int projPosX, projPosY;
	int projVelX, projVelY;
	SDL_Rect projCollider;
};

#endif /* PROJECTILE_H_INCLUDED */
