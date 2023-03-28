#include "Plank.h"

Plank::Plank()
{
	plankPosX = 300;
	plankPosY = 450;
	plankVelX = 0;
	plankVelY = 0;
}

void Plank::handleKeyPresses(SDL_Event& e)
{
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: plankVelY -= PLANK_MAX_AXIS_VEL; break;
		case SDLK_DOWN: plankVelY += PLANK_MAX_AXIS_VEL; break;
		case SDLK_LEFT: plankVelX -= PLANK_MAX_AXIS_VEL; break;
		case SDLK_RIGHT: plankVelX += PLANK_MAX_AXIS_VEL; break;
		}
	}
	// If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		// Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: plankVelY += PLANK_MAX_AXIS_VEL; break;
		case SDLK_DOWN: plankVelY -= PLANK_MAX_AXIS_VEL; break;
		case SDLK_LEFT: plankVelX += PLANK_MAX_AXIS_VEL; break;
		case SDLK_RIGHT: plankVelX -= PLANK_MAX_AXIS_VEL; break;
		}
	}
}

void Plank::move(const int height, const int width)
{
	// Left/Right
	plankPosX += plankVelX;

	// If the plank went too far to the left or right
	if ((plankPosX < 0) || (plankPosX + PLANK_WIDTH > width))
	{
		// Move back
		plankPosX -= plankVelX;
	}

	// Up/Down
	plankPosY += plankVelY;

	// If the plank went too far up or down
	if ((plankPosY < 0) || (plankPosY + PLANK_HEIGHT > height))
	{
		// Move back
		plankPosY -= plankVelY;
	}
}

void Plank::render(LTexture* gPlankTexture, SDL_Renderer* gRenderer)
{
	gPlankTexture->render(plankPosX, plankPosY, gRenderer);
}

