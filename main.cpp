#include "Common_Function.h"
#include "BaseObject.h"
#include "MainObject.h"

BaseObject g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int ImgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(ImgFlags) && ImgFlags))
                success = false;
        }
    }
    return success;
}   

bool LoadBackground()
{
    bool ret = g_background.loadImg("background.png",g_screen);
    if (ret == false)
        return false;

    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    int bkgn_x = 0;
    if (InitData() == false)
        return -1;
    if (LoadBackground() == false)
        return -1;

    MainObject p_player(START_XPOS_MAIN,START_YPOS_MAIN);
    p_player.loadImg("player.png",g_screen);


    bool is_quit = false;
    while (!is_quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandleInputAction(g_event,g_screen);
        }

        p_player.HandleMove();

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        p_player.MakeAmo(g_screen);

        bkgn_x += 1;
        g_background.Render(g_screen, NULL, 0, bkgn_x);
        g_background.Render(g_screen, NULL, 0, bkgn_x - SCREEN_HEIGHT);
        if (bkgn_x >= SCREEN_HEIGHT)
        {
            bkgn_x = 0; 
        }
                                                                                                        
        p_player.MakeAmo(g_screen);
        p_player.Render(g_screen, NULL);

        SDL_RenderPresent(g_screen);

    }
    close();
    return 0;
}