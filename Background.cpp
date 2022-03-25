#include "BackGround.h"
#include "TextureManager.h"
BackGround::BackGround() {
	background = TextureManager::LoadTexture("assets/background.png");
	flip = SDL_FLIP_NONE;
	src.x = src.y = 0;
	dest.x = dest.y = 0;
	src.w = dest.w = 1760;
	src.h = dest.h = 960;
}
void BackGround::DrawBackGround() {
	TextureManager::Draw(background, src, dest);
}