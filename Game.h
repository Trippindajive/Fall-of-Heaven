#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>  // Low-level hardware application layer for 2D Graphics interaction
#include <string>

bool initGame();
bool loadMedia();
void closeGame();
//SDL_Texture* loadTexture(std::string path);

#endif /* GAME_H_INCLUDED */