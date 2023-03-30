#include <SDL.h>
#include <SDL_image.h>
#include "Bar.h"

void Bar::render(LTexture* gBarTexture, SDL_Renderer* gRenderer) 
{
	gBarTexture->render(barPosX, barPosY, gRenderer);
}
