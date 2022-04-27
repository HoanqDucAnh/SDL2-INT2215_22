#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <iostream>
#include <SDL.h>
#include <string>
#include <windows.h>
#include <SDL_image.h>
//#include <SDL_mixer.h>
//#include <SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FRAME_PER_SEC = 300;
const int BACKGROUND_HEIGHT = 800;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;
const int NUM_THREAT = 3;
//const int SPEED_MAIN = 8;
//const int NUM_LIVES = 3;
const int START_XPOS_MAIN = SCREEN_WIDTH / 2;
const int START_YPOS_MAIN = SCREEN_HEIGHT - 100;
//màu color key 
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;


#endif