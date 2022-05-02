#include "Common_Function.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatObject.h"
#include "explosion.h"

BaseObject g_background;

int score = 0;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        std::cout << "SDL NO INTI\n";
        return false;
    }
        

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Hardcore game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        std::cout << "NO WINDOW"<<std::endl;
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, NULL);
        if (g_screen == NULL) {
            std::cout << "NO SCREEN"<<SDL_GetError() << std::endl;
            success = false;
        }
            
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int ImgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(ImgFlags) && ImgFlags)) {
                std::cout << "NO SDL IMAGE"<<std::endl;
                success = false;
            }
                
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
    {
        std::cerr << "init error";
        return -1;

    }
    if (LoadBackground() == false)
    {
        std::cerr << "loadback error";
        return -1;

    }

    //player
    MainObject p_player(START_XPOS_MAIN,START_YPOS_MAIN);
    p_player.loadImg("player.png",g_screen);


    //threat
    ThreatsObject* p_threats = new ThreatsObject[20];


    //explsion
    ExplosionObj exp_threat;
    bool check = exp_threat.loadImg("exp_eff.png", g_screen);
    if (!check) {
        std::cerr << "unable to open explosion eff, " << SDL_GetError() << std::endl;
        return -1;
    }
    exp_threat.set_clip();


    for (int i = 0; i < NUM_THREAT; i++) {
        ThreatsObject* p_threat = (p_threats+i);

        p_threat->loadImg("threat.png", g_screen);
        p_threat->SetRect(SCREEN_WIDTH, SCREEN_HEIGHT * 0.2);
        p_threat->set_y_val(4);
        AmoObject* p_bullet = new AmoObject();
        p_threat->InitAmo(p_bullet, 5, g_screen);

    }

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

       // if (e.type == SDL_KEYDOWN

        //Main game functions
        p_player.HandleMove();

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        //Background Scrolling
        bkgn_x += 1;
        g_background.Render1(g_screen, NULL, 0, bkgn_x);
        g_background.Render1(g_screen, NULL, 0, bkgn_x - SCREEN_HEIGHT);
        if (bkgn_x >= SCREEN_HEIGHT)
        {
            bkgn_x = 0;
        }

        for (int ii = 0; ii < NUM_THREAT; ii++) {
            ThreatsObject* p_threat = (p_threats + ii);
            if (p_threat->get_dir())
            {
                p_threat->HandleMoveLtoR(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            else
            {
                p_threat->HandleMoveRtoL(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            p_threat->Render(g_screen, NULL, 100, 100);
            p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        p_player.MakeAmo(g_screen);
        p_player.Render(g_screen, NULL);

        SDL_RenderPresent(g_screen);

        int exp_frame_width = exp_threat.get_fr_width();
        int exp_frame_height = exp_threat.get_fr_height();
        //player & threat collision
        for (int ii = 0; ii < NUM_THREAT; ii++) 
        {
            ThreatsObject* p_threat = (p_threats + ii);
            bool is_col = SDLCommonFunction::CheckCollision(p_player.GetRect(), p_threat->GetRect());
            if (is_col)
            {
                for (int ex = 0; ex < explosion_frame; ex++)
                {
                    int x_player_pos= (p_player.GetRect().x + p_player.GetRect().w * 0.5) - exp_frame_width * 0.5;
                    int y_player_pos= (p_player.GetRect().y + p_player.GetRect().h * 0.5) - exp_frame_width * 0.5;

                    exp_threat.set_frame(ex);
                    exp_threat.SetRect(x_player_pos, y_player_pos);
                    exp_threat.render_explosion(g_screen);
                    SDL_RenderPresent(g_screen);
                }
                SDL_Delay(500);
                if (MessageBox(NULL, L"GA VCL!", L"Info", MB_OK) == IDOK)
                {
                    close();
                    return 0;
                }
            }
        }

        //int exp_frame_width = exp_threat.get_fr_width();
        //int exp_frame_height = exp_threat.get_fr_height();
        //player ammo & threat collision
        for (int ii = 0; ii < NUM_THREAT; ii++)
        {
            ThreatsObject* p_threat = (p_threats + ii);
            std::vector<AmoObject*> amo_list = p_player.GetAmoList();
            for (int ia = 0; ia < amo_list.size(); ia++)
            {
                AmoObject* p_amo = amo_list.at(ia);
                if (p_amo != NULL)
                {
                    bool ret_col = SDLCommonFunction::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
                    if (ret_col)
                    {
                        for (int ex = 0; ex < explosion_frame; ex++)
                        {
                            int x_pos = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5) - exp_frame_width * 0.5;
                            int y_pos = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5) - exp_frame_height * 0.5;

                            exp_threat.set_frame(ex);
                            exp_threat.SetRect(x_pos, y_pos);
                            exp_threat.render_explosion(g_screen);
                            SDL_RenderPresent(g_screen);
                        }

                        p_player.DestroyAmo(ia);
                        p_threat->Reset(-100);
                        score++;
                        break;
                    }
                }
            }
        }
      
        //threat ammo & player collision
        for (int ii = 0; ii < NUM_THREAT; ii++)
        {
            ThreatsObject* p_threat = (p_threats + ii);
            std::vector<AmoObject*> amo_list_threat = p_threat->GetAmoList();
            for (int iat = 0; iat < amo_list_threat.size(); iat++)
            {
                AmoObject* p_amo_threat = amo_list_threat.at(iat);
                if (p_amo_threat != NULL)
                {
                    bool ret_col_threat = SDLCommonFunction::CheckCollision(p_amo_threat->GetRect(), p_player.GetRect());
                    if (ret_col_threat)
                    {
                        for (int ex = 0; ex < explosion_frame; ex++)
                        {
                            int x_pos = (p_player.GetRect().x + p_player.GetRect().w * 0.5) - exp_frame_width * 0.5;
                            int y_pos = (p_player.GetRect().y + p_player.GetRect().h * 0.5) - exp_frame_height * 0.5;

                            exp_threat.set_frame(ex);
                            exp_threat.SetRect(x_pos, y_pos);
                            exp_threat.render_explosion(g_screen);
                            SDL_RenderPresent(g_screen);
                        }
                        //p_threat->DestroyAmo(ia);
                        //p_player->Reset(0); 
                        SDL_Delay(500);
                        if (MessageBox(NULL, L"YOU DIED!", L"Info", MB_OK) == IDOK)
                        {
                            close();
                            std::cout << std::endl << score;
                            return 0;
                        }
                    }
                }
            }
        }
        

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