#ifndef BAR_H_INCLUDED
#define BAR_H_INCLUDED

#include "TextureWrapper.h"

class Bar
{
public:
	static const int BAR_WIDTH = 640;
	static const int BAR_HEIGHT = 1;
	
	Bar();

	void render(LTexture* gBarTexture, SDL_Renderer* gRenderer);

	int getPosX();
	int getPosY();
	SDL_Rect* getCollider();

private:
	int barPosX = 0;
	int barPosY = 400;
	SDL_Rect barCollider;
};

#endif /* BAR_H_INCLUDED */
