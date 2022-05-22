#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <iostream>
#include <SDL.h>
#include <string>
#include <windows.h>
#include <SDL_image.h>
#include <fstream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FRAME_PER_SEC = 60;
const int BACKGROUND_HEIGHT = 800;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;
const int BOSS_WIDTH = 300;
const int BOSS_HEIGHT = 375;
const int SCREEN_BPP = 32;
const int NUM_THREAT = 3;
const int START_XPOS_MAIN = SCREEN_WIDTH / 2.33;
const int START_YPOS_MAIN = SCREEN_HEIGHT - 120;
//màu color key 
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const double PI = 3.141592653589793238463;
const int RENDER_DRAW_COLOR = 0xff;

static Mix_Chunk* g_sound_fire[2];
static Mix_Chunk* g_sound_explo[3];

static Mix_Music* music;

namespace SDLCommonFunction
{
	bool CheckCollision(const SDL_Rect& obj1, const SDL_Rect& obj2);
	void CheckHighScore(int score);
	int FetchHighScore();
}


#endif