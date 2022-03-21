#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <string>

using namespace std;

const int SCREEN_W = 640;
const int SCREEN_H = 480;

bool init();

bool loadMedia();

void quit();

SDL_Texture* loadTexture(string path);

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Texture* gTexture = NULL;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "Error initializing video.";
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL_Tut 7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cerr << "Error creating window";
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				cerr << "Renderer couldn't be created";
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cerr << "Could not initialize SDL_Image";
					success = false;
				}
			}
		}
	}
	return success;
}

SDL_Texture* loadTexture(string path)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface = NULL)
	{
		cerr << "Unable to load image!";
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cerr << "Unable to create texture from image";
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}