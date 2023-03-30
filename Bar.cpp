#include <SDL.h>
#include <SDL_image.h>
#include "Bar.h"

Bar::Bar()
{
	barCollider.x = barPosX;
	barCollider.y = barPosY;
	barCollider.w = BAR_WIDTH;
	barCollider.h = BAR_HEIGHT;
}

void Bar::render(LTexture* gBarTexture, SDL_Renderer* gRenderer) 
{
	gBarTexture->render(barPosX, barPosY, gRenderer);
}

int Bar::getPosX()
{
	return barPosX;
}

int Bar::getPosY() {
	return barPosY;
}

SDL_Rect* Bar::getCollider()
{
	return &barCollider;
}