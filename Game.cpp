#include <SDL.h>
#include <SDL_image.h>  // Hardware-Accelerated Rendering, loads images as SDL surfaces/textures
#include <stdexcept>
#include <stdio.h>		// standard input/output
#include <string>
#include "Bar.h"
#include "Game.h"
#include "Plank.h"
#include "Projectile.h"
#include "TextureWrapper.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* GAME_NAME = "Fall of Heaven";

/*The application time based timer
class LTimer
{
public:
	//Initializes variables
	LTimer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;
};*/

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gPlankTexture;
LTexture gBarTexture;
LTexture gProjTexture;

bool initGame()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if (!gPlankTexture.loadFromFile("textures/plank.png", gRenderer))
	{
		printf("Failed to load plank texture!\n");
		success = false;
	}

	if (!gBarTexture.loadFromFile("textures/bar.png", gRenderer))
	{
		throw exception("Failed to load bar texture!\n");
	}

	if (!gProjTexture.loadFromFile("textures/projectile.png", gRenderer))
	{
		throw exception("Failed to load projectile texture!\n");
	}

	return success;
}

void closeGame()
{
	gPlankTexture.freeTexture();
	gBarTexture.freeTexture();
	gProjTexture.freeTexture();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (!initGame())
	{
		printf("Failed to initialize game!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool game_quit = false;
			SDL_Event e;
			Plank plank;
			Bar bar;
			Projectile ball;

			while (!game_quit)
			{
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					// Quit game if user requests quit
					if (e.type == SDL_QUIT)
					{
						game_quit = true;
					}

					// Handle input for the dot
					plank.handleKeyPresses(e);
				}

				plank.move(*bar.getCollider(), SCREEN_HEIGHT, SCREEN_WIDTH);

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render objects
				plank.render(&gPlankTexture, gRenderer);
				bar.render(&gBarTexture, gRenderer);
				ball.render(&gProjTexture, gRenderer);


				// Update screen space
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	
	closeGame();

	return 0;
}