#include "Text.h"

Text::Text()
{
	text_color.r = 255;
	text_color.g = 255;
	text_color.r = 255;
	textture = NULL;
}

Text::~Text()
{

}

bool Text::Loadfromrendertext(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text_content.c_str(), text_color);
	if (!text_surface) {
		std::cerr << "cant load text, error: " << SDL_GetError() << std::endl;
	}
	else {
		textture = SDL_CreateTextureFromSurface(screen, text_surface);
		text_width = text_surface->w;
		text_height = text_surface->h;

		SDL_FreeSurface(text_surface);
	}
	return textture != NULL;
}

void Text::free()
{
	if (textture) {
		SDL_DestroyTexture(textture);
		textture = NULL;
	}
}

void Text::Setcolor(Uint8 green, Uint8 red, Uint8 blue)
{
	text_color.g = green;
	text_color.r = red;
	text_color.b = blue;
}

void Text::Setcolor(int type)
{
	if (type == WHITE_TEXT)
	{
		SDL_Color white = { 255,255,255 };
		text_color = white;
	}
	else if (type == BLUE_TEXT)
	{
		SDL_Color blue = { 0, 255, 255 };
		text_color = blue;
	}
	else if (type == RED_TEXT)
	{
		SDL_Color red = { 255,0,0 };
		text_color = red;
	}
}

void Text::loadtexttoscreen(SDL_Renderer* screen,
							int X_POS, INT Y_POS,
							double angle,
							SDL_Rect* clip,
							SDL_Point* center,
							SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { X_POS,Y_POS,text_width,text_height };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(screen, textture, clip, &renderQuad, angle, center, flip);
}