#include <SDL.h>
#include <SDL_image.h>  // Hardware-Accelerated Rendering, loads images as SDL surfaces/textures
#include <SDL_ttf.h>
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

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gPlankTexture;
LTexture gBarTexture;
LTexture gProjTexture;
TTF_Font* gFont = NULL;
LTexture gTextTexture;

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

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				// Initialize SDL True Type Font
				if (TTF_Init() == -1)
				{
					printf("SDL TTF could not be initialized! SDL_ttf Error: %s\n", TTF_GetError());
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

	// Open Font
	gFont = TTF_OpenFont("textures/lazy.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		// Render Text
		SDL_Color textColor = { 0, 0, 0 };
		if (!gTextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, gFont, gRenderer))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void closeGame()
{
	gPlankTexture.freeTexture();
	gBarTexture.freeTexture();
	gProjTexture.freeTexture();
	gTextTexture.freeTexture();
	TTF_CloseFont(gFont);
	gFont = NULL;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void moveProjectiles(Projectile* pj, int gravity)
{
	pj->setVelY(gravity);
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
			// Trying to make a small HUD at upper right corner
			/*SDL_Rect topLeftViewport;
			topLeftViewport.x = 500;
			topLeftViewport.y = 0;
			topLeftViewport.w = SCREEN_WIDTH / 4;
			topLeftViewport.h = SCREEN_HEIGHT / 4;
			SDL_RenderSetViewport(gRenderer, &topLeftViewport);*/

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
				ball.move(/**bar.getCollider(),*/ *plank.getCollider(), plank);

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(gRenderer);

				// Render objects
				plank.render(&gPlankTexture, gRenderer);
				bar.render(&gBarTexture, gRenderer);
				ball.render(&gProjTexture, gRenderer);

				// Render Current Frame
				gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2, gRenderer);
				//moveProjectiles(&ball, 10);
				//ball.projVelY += 10;

				// Update screen space
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	
	closeGame();

	return 0;
}