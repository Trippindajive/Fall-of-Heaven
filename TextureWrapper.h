#ifndef TEXTURE_WRAPPER_INCLUDED
#define TEXTURE_WRAPPER_INCLUDED

#include <cstddef>
#include <cstdint> 
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class LTexture
{
public:
	LTexture();
	~LTexture();

	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font*, SDL_Renderer*);

	/*#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	#endif*/

	void freeTexture();

	// Alters color of rendered texture
	void setColor(Uint8, Uint8, Uint8);

	// Set blending mode for copying texture portion to current rendering target
	void setBlendMode(SDL_BlendMode);

	// Set alpha modulation multiplier for render copy operations
	void setAlpha(Uint8);

	// Renders texture at given point
	void render(int, int, SDL_Renderer*, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	// Gets image dimensions
	int getWidth();
	int getHeight();
	SDL_Rect* getRect();

private:
	SDL_Texture* hTexture;  // hardware-based texture
	SDL_Rect* hRect;		// rectangle for detecting collision
	int hWidth;
	int hHeight;
};

#endif /* TEXTURE_WRAPPER */