#ifndef BAR_H_INCLUDED
#define BAR_H_INCLUDED

#include "TextureWrapper.h"

class Bar
{
public:
	static const int BAR_WIDTH = 640;
	static const int BAR_HEIGHT = 1;
	
	void render(LTexture* gBarTexture, SDL_Renderer* gRenderer);

private:
	int barPosX = 0;
	int barPosY = 400;
};

#endif /* BAR_H_INCLUDED */
