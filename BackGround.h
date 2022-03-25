#pragma once
#include "Game.h"
class BackGround {
public:
	BackGround();
	~BackGround();
	void DrawBackGround();
private:
	SDL_Rect src, dest;
	SDL_RendererFlip flip;
	SDL_Texture* background;
};