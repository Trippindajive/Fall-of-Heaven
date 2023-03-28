#ifndef TEXTURE_WRAPPER_INCLUDED
#define TEXTURE_WRAPPER_INCLUDED

#include <cstddef>
#include <cstdint> 
#include <SDL.h>
#include <string>

class LTexture
{
public:
	LTexture();
	~LTexture();

	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	/*#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	#endif*/

	void freeTexture();

	// Alters color of rendered texture
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending mode for copying texture portion to current rendering target
	void setBlendMode(SDL_BlendMode mode);

	// Set alpha modulation multiplier for render copy operations
	void setAlpha(Uint8 alpha);

	// Renders texture at given point
	void render(int x, int y, SDL_Renderer* , SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	SDL_Texture* hTexture;  // hardware-based texture
	int hWidth;
	int hHeight;
};

#endif /* TEXTURE_WRAPPER */