#include "Common_Function.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatObject.h"
#include "explosion.h"
#include "GameButton.h"
#include "PlayerHealth.h"
#include "Text.h";

BaseObject g_background;
BaseObject test_menu;
BaseObject test_help;
BaseObject test_pause;
TTF_Font* general_font = NULL;
GameButton PlayButton;
GameButton HelpButton;
GameButton ExitButton;
GameButton BackButton;
GameButton ScoreButton;
int player_score = 0;
TTF_Font* g_font;

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
        std::cout << "NO WINDOW" << std::endl;
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, NULL);
        if (g_screen == NULL) {
            std::cout << "NO SCREEN" << SDL_GetError() << std::endl;
            success = false;
        }

        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int ImgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(ImgFlags) && ImgFlags)) 
            {
                std::cout << "NO SDL IMAGE" << std::endl;
                success = false;
            }
        }
        if (TTF_Init() == -1)
        {
            std::cerr << "ttf error: " << SDL_GetError() << std::endl;
            success = false;
        }
        g_font = TTF_OpenFont("ARCADECLASSIC.TTF", 30);
        if (g_font)
        {
            success = true;
        }
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.loadImg("background.png", g_screen);
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

    test_menu.loadImg("menu.png", g_screen);
    test_help.loadImg("help.png", g_screen);
    test_pause.loadImg("pause.png", g_screen);
    bool play = false;
    bool menu = true;
    bool help = false;
    bool score = false;
    bool QuitMenu = false;

    //game text
    Text game_time,game_mark;
    game_time.Setcolor(Text::WHITE_TEXT);
    game_mark.Setcolor(Text::WHITE_TEXT);

    while (!QuitMenu)
    {
        if (menu)
        {
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    QuitMenu = true;

                }
                PlayButton.PlayButton(g_event, g_screen, menu, play, QuitMenu);
                ScoreButton.HighScoreButton(g_event, g_screen, menu, score);
                HelpButton.HelpButton(g_event, g_screen, menu, help);
                ExitButton.ExitButton(g_event, g_screen, QuitMenu);
            }
            PlayButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_frame_width() / 2, SCREEN_HEIGHT / 2 + 40);
            ScoreButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_frame_width() / 2, SCREEN_HEIGHT / 2 + 120);
            HelpButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_frame_width() / 2, SCREEN_HEIGHT / 2 + 200);
            ExitButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_frame_width() / 2, SCREEN_HEIGHT / 2 + 280);
            test_menu.Render2(g_screen, NULL);
            HelpButton.Render2(g_screen, NULL);
            ScoreButton.Render2(g_screen, NULL);
            PlayButton.Render2(g_screen, NULL);
            ExitButton.Render2(g_screen, NULL);
            SDL_RenderPresent(g_screen);
        }
        if (help)
        {
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    QuitMenu = true;
                }
                PlayButton.PlayButton(g_event, g_screen, menu, play, QuitMenu);
                BackButton.BackButton(g_event, g_screen, menu, help);
            }
            test_help.Render2(g_screen, NULL);
            BackButton.SetRect(30, SCREEN_HEIGHT - BackButton.get_frame_height() - 30);
            PlayButton.SetRect(SCREEN_WIDTH - PlayButton.get_frame_width() - 30, SCREEN_HEIGHT - BackButton.get_frame_height() - 30);
            PlayButton.Render2(g_screen, NULL);
            BackButton.Render2(g_screen, NULL);
            SDL_RenderPresent(g_screen);
        }
        /*if (score)
        {
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    QuitMenu = true;

                }

        }*/
    }
    SDL_WarpMouseInWindow(g_window, SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT - 100);
    bool paused = false;
    bool GameOver = false;

    //create health
    PlayerHealth player_health;
    player_health.loadImg("heart.png", g_screen);
    player_health.init_heart(g_screen);
    

    //player
    MainObject p_player(START_XPOS_MAIN, START_YPOS_MAIN);
    p_player.loadImg("player.png", g_screen);

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
        ThreatsObject* p_threat = (p_threats + i);

        p_threat->loadImg("threat.png", g_screen);
        p_threat->SetRect(SCREEN_WIDTH, SCREEN_HEIGHT * 0.2);
        p_threat->set_y_val(4);
        AmoObject* p_bullet = new AmoObject();
        p_threat->InitAmo(p_bullet, 5, g_screen);

    }

    //player death counts
    int death_counts = 0;

    //main game loop
    while (play) {
        if (!GameOver)
        {
            if (paused)
            {
                SDL_WarpMouseInWindow(g_window, p_player.GetRect().x, p_player.GetRect().y);
                while (SDL_PollEvent(&g_event) != 0)
                {
                    if (g_event.type == SDL_QUIT)
                    {
                        play = false;
                    }
                    if (g_event.type == SDL_KEYDOWN)
                    {
                        if (g_event.key.keysym.sym == SDLK_p)
                        {
                            paused = false;
                        }
                        if (g_event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            play = false;
                        }
                    }
                }
                test_pause.SetRect(0, SCREEN_HEIGHT / 3 - test_pause.GetRect().h);
                test_pause.Render2(g_screen, NULL);
                SDL_RenderPresent(g_screen);
            }
            else if (!paused)
            {
                fps_timer.start();
                while (SDL_PollEvent(&g_event) != 0)
                {
                    if (g_event.type == SDL_QUIT)
                    {
                        play = false;
                    }
                    if (g_event.type == SDL_KEYDOWN)
                    {
                        if (g_event.key.keysym.sym == SDLK_p)
                        {
                            paused = true;
                        }
                        if (g_event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            play = false;
                        }
                    }
                    p_player.HandleInputAction(g_event, g_screen);
                }
              
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

                //render health
                player_health.show_heart(g_screen);


                int exp_frame_width = exp_threat.get_fr_width();
                int exp_frame_height = exp_threat.get_fr_height();

                //player & threat collision
                for (int ii = 0; ii < NUM_THREAT; ii++)
                {
                    ThreatsObject* p_threat = (p_threats + ii);
                    bool is_col = SDLCommonFunction::CheckCollision(p_player.GetRect(), p_threat->GetRect());
                    if (is_col)
                    {
                        p_threat->Reset(-100);
                        for (int ex = 0; ex < explosion_frame; ex++)
                        {
                            int x_player_pos = (p_player.GetRect().x + p_player.GetRect().w * 0.5) - exp_frame_width * 0.5;
                            int y_player_pos = (p_player.GetRect().y + p_player.GetRect().h * 0.5) - exp_frame_width * 0.5;

                            exp_threat.set_frame(ex);
                            exp_threat.SetRect(x_player_pos, y_player_pos);
                            exp_threat.render_explosion(g_screen);
                            SDL_RenderPresent(g_screen);
                        }
                        SDL_Delay(500);
                        death_counts++;
                        if (death_counts <= 2) {

                            p_player.reset_main_pos(START_XPOS_MAIN, START_YPOS_MAIN);
                            player_health.minus_health();
                            player_health.show_heart(g_screen);
                            
                        }
                        else {
                            if (MessageBox(NULL, L"GA VCL!", L"Info", MB_OK) == IDOK)
                            {
                                close();
                                return 0;
                            }
                        }
                    }
                }


                //player score 
                std::string string_score = "Score ";

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
                                    SDL_Delay(4);
                                }

                                p_player.DestroyAmo(ia);
                                p_threat->Reset(-100);
                                player_score++;
                                //std::string score_value = std::to_string(player_score);
                                //string_score += score_value;
                                //game_mark.settext(string_score);
                                //game_mark.Loadfromrendertext(g_font, g_screen);
                                //game_mark.loadtexttoscreen(g_screen, 150, 0);
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
                                p_threat->ResetAmo(p_amo_threat);
                                for (int ex = 0; ex < explosion_frame; ex++)
                                {
                                    int x_pos = (p_player.GetRect().x + p_player.GetRect().w * 0.5) - exp_frame_width * 0.5;
                                    int y_pos = (p_player.GetRect().y + p_player.GetRect().h * 0.5) - exp_frame_height * 0.5;

                                    exp_threat.set_frame(ex);
                                    exp_threat.SetRect(x_pos, y_pos);
                                    exp_threat.render_explosion(g_screen);
                                    SDL_RenderPresent(g_screen);
                                }
                                //p_threat->ResetAmo(p_amo_threat);
                                //p_player.Reset(0); 
                                SDL_Delay(500);
                                death_counts++;
                                if (death_counts <= 2)
                                {
                                    //SDL_Delay(500);
                                    p_player.reset_main_pos(START_XPOS_MAIN, START_YPOS_MAIN);
                                    player_health.minus_health();
                                    player_health.show_heart(g_screen);
                                    for (int i = 0; i < NUM_THREAT; i++) {
                                        p_threat->Reset(-100);
                                    }
                                }
                                else
                                {
                                    SDLCommonFunction::CheckHighScore(player_score);
                                    if (MessageBox(NULL, L"YOU DIED!", L"Info", MB_OK) == IDOK)
                                    {
                                        close();
                                        std::cout << std::endl << player_score;
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }


                //game score
                std::string score_value = std::to_string(player_score);
                string_score += score_value;
                game_mark.settext(string_score);
                game_mark.Loadfromrendertext(g_font, g_screen);
                game_mark.loadtexttoscreen(g_screen, 350, 0);

                //push game time to screen
                std::string string_time = "Time ";
                Uint32 time_value = SDL_GetTicks() / 1000;
                //Uint32 value_time = 300 - time_val;
                std::string string_value = std::to_string(time_value);
                string_time += string_value;
                game_time.settext(string_time);
                game_time.Loadfromrendertext(g_font, g_screen);
                game_time.loadtexttoscreen(g_screen, 150, 0);

                SDL_RenderPresent(g_screen);

                int real_time = fps_timer.get_ticks();
                int time_one_frame = (1000 / 3) / FRAME_PER_SEC; //ms

                if (real_time < time_one_frame) {
                    int delay_time = time_one_frame - real_time;
                    if (delay_time >= 0) {
                        SDL_Delay(delay_time - 1);
                    }
                }
            }
        }
    }
    close();
    return 0;
}