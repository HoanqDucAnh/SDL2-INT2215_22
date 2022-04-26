#include "Common_Function.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatObject.h"

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
    Timer fps_timer;

    int bkgn_x = 0;
    if (InitData() == false)
        return -1;
    if (LoadBackground() == false)
        return -1;

    MainObject p_player(START_XPOS_MAIN,START_YPOS_MAIN);
    p_player.loadImg("player.png",g_screen);

    ThreatsObject* p_threat = new ThreatsObject();
   
    p_threat->loadImg("threat.png", g_screen);
    p_threat->SetRect(SCREEN_WIDTH, SCREEN_HEIGHT * 0.2);
    p_threat->set_y_val(4);
    AmoObject* p_bullet = new AmoObject();
    p_threat->InitAmo(p_bullet, 10 , g_screen);
   


    bool is_quit = false;
    while (!is_quit)
    {

        fps_timer.start();
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

        bkgn_x += 1;
        g_background.Render1(g_screen, NULL, 0, bkgn_x);
        g_background.Render1(g_screen, NULL, 0, bkgn_x - SCREEN_HEIGHT);
        if (bkgn_x >= SCREEN_HEIGHT)
        {
            bkgn_x = 0;
        }
        p_player.MakeAmo(g_screen);
        p_threat->Render(g_screen, NULL, 100, 100);
        p_threat->HandleMove2(SCREEN_WIDTH, SCREEN_HEIGHT);
        p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        p_player.Render(g_screen, NULL);

        SDL_RenderPresent(g_screen);

        int real_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SEC; //ms

        if (real_time < time_one_frame) {
            int delay_time = time_one_frame - real_time;
            if (delay_time >= 0) {
                SDL_Delay(delay_time);
            }
        }
    }
    close();
    return 0;
}