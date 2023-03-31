#include <iostream>
#include "Plank.h"

using namespace std;

Plank::Plank()
{
	plankPosX = 300;
	plankPosY = 450;
	plankVelX = 0;
	plankVelY = 0;
	plankCollider.w = PLANK_WIDTH;
	plankCollider.h = PLANK_HEIGHT;
}

void Plank::handleKeyPresses(SDL_Event& e)
{
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// Adjust the velocity
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

/* Must use parameters (hardcoded temp solution) */
void Plank::move(SDL_Rect& box, const int width, const int height)
{
	// Left/Right
	plankPosX += plankVelX;
	plankCollider.x = plankPosX;
	cout << "Plank X-Position: " << plankPosX << " || Plank Velocity: " <<
		plankVelX << "\n";

	// If the plank went too far to the left or right or collided w/ box
	if ((plankPosX < 0) || (plankPosX > 560) || checkCollision(plankCollider, box))
	{
		// Move back
		plankPosX -= plankVelX;
		plankCollider.x = plankPosX;
	}

	// Up/Down
	plankPosY += plankVelY;
	plankCollider.y = plankPosY;
	cout << "Plank Y-Position: " << plankPosY << " || Plank Velocity: " <<
		plankVelY << "\n";
	// If the plank went too far up or down or collided w/ box
	if ((plankPosY > 470) || (plankPosY < 10) || checkCollision(plankCollider, box))
	{
		// Move back
		plankPosY -= plankVelY;
		plankCollider.y = plankPosY;
	}
}

bool Plank::checkCollision(SDL_Rect a, SDL_Rect b)
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
	if (bottomA <= topB)
	{
		return false;
	}
	if (topA >= bottomB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}

	// O.W. there is an overlap across the separting axis
	return true;
}

void Plank::render(LTexture* gPlankTexture, SDL_Renderer* gRenderer)
{
	gPlankTexture->render(plankPosX, plankPosY, gRenderer);
}

int Plank::getPosX()
{
	return plankPosX;
}

int Plank::getPosY() {
	return plankPosY;
}

void Plank::setVelY(int val)
{
	plankPosY = val;
}