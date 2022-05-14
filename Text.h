#pragma once

#include "Common_Function.h"

class Text
{
public:
	Text();
	~Text();

	enum Textcolor
	{
		WHITE_TEXT = 0,
		BLUE_TEXT = 1,
		RED_TEXT = 2,
		YELLLOW_TEXT = 3,
	};

	bool Loadfromrendertext(TTF_Font* font, SDL_Renderer* screen); //load text to screen
	void free();

	void Setcolor(Uint8 green, Uint8 red, Uint8 blue);
	void Setcolor(int type); //my color

	void loadtexttoscreen(SDL_Renderer* screen,
						  int X_POS, INT Y_POS,
						  double angle = 0.0,
						  SDL_Rect* clip=NULL,
						  SDL_Point* center = NULL,
						  SDL_RendererFlip = SDL_FLIP_NONE);

	int getwidth() const { return text_width; };
	int getheight() const { return text_height; };
	void settext(const std::string& text) { text_content = text; };
	std::string getText() const { return text_content; };


private:
	std::string text_content;
	SDL_Color text_color;
	SDL_Texture* textture;
	int text_width;
	int text_height;
};