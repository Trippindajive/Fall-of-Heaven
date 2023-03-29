#ifndef PLANK_H_INCLUDED
#define PLANK_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "TextureWrapper.h"

class Plank
{
public:
	
	static const int PLANK_WIDTH = 80;
	static const int PLANK_HEIGHT = 20;
	static constexpr int PLANK_MAX_AXIS_VEL = 10;
	static constexpr int GFORCE = -1;

	Plank();

	void handleKeyPresses(SDL_Event& e);

	void move(const int height, const int width);

	void render(LTexture* gPlankTexture, SDL_Renderer* gRenderer);

private:
	int plankPosX, plankPosY;
	int plankVelX, plankVelY;
};

#endif /* PLANK_H_INCLUDED */