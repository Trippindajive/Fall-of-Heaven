#include <SDL_image.h>
#include "TextureWrapper.h"

using namespace std;

LTexture::LTexture()
{
	hTexture = NULL;
	hRect = NULL;
	hWidth = 0;
	hHeight = 0;
}

LTexture::~LTexture()
{
	freeTexture();
}

bool LTexture::loadFromFile(string path, SDL_Renderer* gRenderer)
{
	freeTexture();
	SDL_Texture* newTexture = NULL;  // hardware rendering, VRAM, indirect access

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());  // software rendering, RAM, direct access
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			hWidth = loadedSurface->w;
			hHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	hTexture = newTexture;
	return hTexture != NULL;
}

/*#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return mTexture != NULL;
}
#endif*/

void LTexture::freeTexture()
{
	if (hTexture != NULL)
	{
		SDL_DestroyTexture(hTexture);
		hTexture = NULL;
		hWidth = 0;
		hHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(hTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode mode)
{
	SDL_SetTextureBlendMode(hTexture, mode);
}

void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(hTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	// Rendering rectangle for screen
	// x location of rect's upper left corner
	// y location of rect's upper left corner
	// width of rect
	// height of rect
	SDL_Rect renderSpace = { x, y, hWidth, hHeight };

	// Create collision box
	//*hRect = { x, y, hWidth, hHeight };

	// Set renderSpace dimensions to clip rendering dimensions
	if (clip != NULL)
	{
		renderSpace.w = clip->w;
		renderSpace.h = clip->h;
	}

	// Copies texture portion to rendering target (screen)
	SDL_RenderCopyEx(gRenderer, hTexture, clip, &renderSpace, angle, center, flip);
}

int LTexture::getWidth()
{
	return hWidth;
}

int LTexture::getHeight()
{
	return hHeight;
}

SDL_Rect* LTexture::getRect()
{
	return hRect;
}