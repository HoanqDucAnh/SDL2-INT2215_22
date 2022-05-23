#include "Common_Function.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Timer.h"
#include "Enemy.h"
#include "explosion.h"
#include "GameButton.h"
#include "PlayerHealth.h"
#include "Text.h"
#include "Bullet.h"

BaseObject Gameover;
BaseObject g_background;
BaseObject load_menu;
BaseObject load_help;
BaseObject load_pause;
BaseObject load_score;
BaseObject load_win;


GameButton PlayButton;
GameButton HelpButton;
GameButton ExitButton;
GameButton BackButton;
GameButton ScoreButton;
GameButton RestartButton;

TTF_Font* g_font = NULL;
TTF_Font* Gameover_font;

Mix_Chunk* Menu = NULL;
Mix_Chunk* Game = NULL;

Text game_time, game_mark;
Text game_over, game_score;
Text game_over_mark;

int player_score = 0;
int time_value;
int invi_timer = 0;
int boss_health = 160;


bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        std::cout << "SDL NO INTI\n";
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Space Fighter SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
        Gameover_font = TTF_OpenFont("ARCADECLASSIC.TTF", 70);
        if (Gameover_font)
        {
            success = true;
        }
    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.loadImg("img//background.png", g_screen);
    if (ret == false)
        return false;

    return true;
}

void close()
{
    g_background.Free();
    load_help.Free();
    load_menu.Free();
    load_pause.Free();
    load_score.Free();
    load_win.Free();

    Mix_FreeChunk(g_sound_explo[0]);
    Mix_FreeChunk(g_sound_explo[1]);
    Mix_FreeChunk(g_sound_explo[2]);
    Mix_FreeChunk(g_sound_fire[0]);
    Mix_FreeChunk(g_sound_fire[1]);

    Mix_FreeMusic(music);

    Gameover.Free();
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
    {
        std::cerr << "init error";
        return -1;

    }
    if (LoadBackground() == false)
    {
        std::cerr << "loadback error";
        return -1;

    }

    load_menu.loadImg("img//menu.png", g_screen);
    load_help.loadImg("img//help.png", g_screen);
    load_pause.loadImg("img//pause.png", g_screen);
    load_score.loadImg("img//HighScore.png", g_screen);
    load_win.loadImg("img//Win.png", g_screen);
    Gameover.loadImg("img//GameOver.png", g_screen);

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return -1;
    }

    // Read file audio (wav)
    g_sound_fire[0] = Mix_LoadWAV("audio//lazersound.wav");
    g_sound_fire[1] = Mix_LoadWAV("audio//rightfire.wav");
    g_sound_explo[0] = Mix_LoadWAV("audio//explosion.wav");
    g_sound_explo[1] = Mix_LoadWAV("audio//chickdie.wav");
    g_sound_explo[2] = Mix_LoadWAV("audio//botdie.wav");

    music = Mix_LoadMUS("audio//mission.wav");

    if (g_sound_fire[0] == NULL || g_sound_fire[1] == NULL || g_sound_explo[0] == NULL || g_sound_explo[1] == NULL || g_sound_explo[2] == NULL || music == NULL)
        return -1;

    Timer fps_timer;

    bool play = false;
    bool menu = true;
    bool help = false;
    bool score = false;
    bool QuitMenu = false;
    bool end = false;
    bool win = false;

    //game text
    game_time.Setcolor(Text::WHITE_TEXT);
    game_mark.Setcolor(Text::WHITE_TEXT);
    game_over.Setcolor(Text::WHITE_TEXT);
    game_over_mark.Setcolor(Text::WHITE_TEXT);
    game_score.Setcolor(Text::WHITE_TEXT);


    //create health
    PlayerHealth player_health;
    player_health.loadImg("img//heart.png", g_screen);
    player_health.init_heart();

    //player
    MainObject p_player(START_XPOS_MAIN, START_YPOS_MAIN);
    p_player.loadImg("img//player.png", g_screen);

    //explsion
    ExplosionObj exp_threat;
    bool check = exp_threat.loadImg("img//exp_eff.png", g_screen);
    if (!check) {
        std::cerr << "unable to open explosion eff, " << SDL_GetError() << std::endl;
        return -1;
    }
    exp_threat.set_clip();

    //threat

    Enemy* p_threats = new Enemy[3];
    for (int i = 0; i < NUM_THREAT; i++) {
        Enemy* p_threat = (p_threats + i);
        p_threat->loadImg("img//threat.png", g_screen);
        p_threat->SetRect(SCREEN_WIDTH, SCREEN_HEIGHT * 0.2);
        p_threat->set_y_val(4);
        Bullet* p_bullet = new Bullet();
        p_threat->InitBullet(p_bullet, 2, g_screen);
    }

    //meteor

    Enemy* meteors = new Enemy[2];
    for (int i = 0; i < NUM_THREAT - 1; i++) {
        Enemy* meteor = (meteors + i);
        meteor->loadImg("img//meteor.png", g_screen);
        meteor->SetRect(SCREEN_WIDTH, SCREEN_HEIGHT * 0.2);
    }

    //boss

    Enemy* boss = new Enemy();
    boss->loadImg("img//boss.png", g_screen);
    boss->SetRect(SCREEN_WIDTH / 2 - 150, -200);
    boss->set_x_val(2);
    Bullet* p_bullet = new Bullet();
    boss->InitBulletTestRight(p_bullet, 1, g_screen, boss);
    boss->InitBullet4(g_screen, boss);


    while (!end) {

        Mix_PlayMusic(music, -1);

        while (!QuitMenu)
        {
            if (menu)
            {
                while (SDL_PollEvent(&g_event) != 0)
                {
                    if (g_event.type == SDL_QUIT)
                    {
                        QuitMenu = true;
                        end = true;

                    }
                    PlayButton.Play(g_event, g_screen, menu, play, QuitMenu, help);
                    ScoreButton.HighScore(g_event, g_screen, menu, score);
                    HelpButton.Help(g_event, g_screen, menu, help);
                    ExitButton.Exit(g_event, g_screen, QuitMenu, end);
                }
                PlayButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 + 40);
                ScoreButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 + 120);
                HelpButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 + 200);
                ExitButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 + 280);
                load_menu.Render2(g_screen, NULL);
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
                        end = true;
                    }
                    PlayButton.Play(g_event, g_screen, menu, play, QuitMenu, help);
                    BackButton.Back(g_event, g_screen, menu, help, score);
                    PlayButton.Play(g_event, g_screen, menu, play, QuitMenu, help);
                    BackButton.Back(g_event, g_screen, menu, help, score);
                }
                load_help.Render2(g_screen, NULL);
                BackButton.SetRect(30, SCREEN_HEIGHT - BackButton.get_height_frame() - 30);
                PlayButton.SetRect(SCREEN_WIDTH - PlayButton.get_width_frame() - 30, SCREEN_HEIGHT - BackButton.get_height_frame() - 30);
                PlayButton.Render2(g_screen, NULL);
                BackButton.Render2(g_screen, NULL);
                SDL_RenderPresent(g_screen);
            }
            if (score)
            {
                while (SDL_PollEvent(&g_event) != 0)
                {
                    if (g_event.type == SDL_QUIT)
                    {
                        QuitMenu = true;
                        end = true;
                    }

                    PlayButton.Play(g_event, g_screen, menu, play, QuitMenu, help);
                    BackButton.Back(g_event, g_screen, menu, help, score);
                }

                int score = SDLCommonFunction::FetchHighScore();
                std::string highscore = std::to_string(score * 100);

                load_score.Render2(g_screen, NULL);
                BackButton.SetRect(30, SCREEN_HEIGHT - BackButton.get_height_frame() - 30);
                BackButton.Render2(g_screen, NULL);
                PlayButton.SetRect(SCREEN_WIDTH - PlayButton.get_width_frame() - 30, SCREEN_HEIGHT - BackButton.get_height_frame() - 30);
                PlayButton.Render2(g_screen, NULL);
                game_score.settext(highscore);
                game_score.Loadfromrendertext(Gameover_font, g_screen);
                game_score.loadtexttoscreen(g_screen, SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT / 2 - 100);
                SDL_RenderPresent(g_screen);
            }
        }
        SDL_WarpMouseInWindow(g_window, SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT - 100);


        //player death counts
        int death_counts = 0;

        bool paused = false;
        bool GameOver = false;
        //main game loop
        while (play) {

            if (menu)
            {
                while (SDL_PollEvent(&g_event) != 0)
                {
                    if (g_event.type == SDL_QUIT)
                    {
                        QuitMenu = true;
                        end = true;
                    }
                    PlayButton.Play(g_event, g_screen, menu, play, QuitMenu, help);
                    ScoreButton.HighScore(g_event, g_screen, menu, score);
                    HelpButton.Help(g_event, g_screen, menu, help);
                    ExitButton.Exit(g_event, g_screen, QuitMenu, end);
                }
                PlayButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 + 40);
                ScoreButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 + 120);
                HelpButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 + 200);
                ExitButton.SetRect(SCREEN_WIDTH / 2 - PlayButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 + 280);
                load_menu.Render2(g_screen, NULL);
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
                        end = true;
                    }
                    PlayButton.Play(g_event, g_screen, menu, play, QuitMenu, help);
                    BackButton.Back(g_event, g_screen, menu, help, score);

                }
                load_help.Render2(g_screen, NULL);
                BackButton.SetRect(30, SCREEN_HEIGHT - BackButton.get_height_frame() - 30);
                PlayButton.SetRect(SCREEN_WIDTH - PlayButton.get_width_frame() - 30, SCREEN_HEIGHT - BackButton.get_height_frame() - 30);
                PlayButton.Render2(g_screen, NULL);
                BackButton.Render2(g_screen, NULL);
                SDL_RenderPresent(g_screen);
            }
            if (!GameOver)
            {
                if (paused)
                {
                    Mix_PauseMusic();
                    SDL_WarpMouseInWindow(g_window, p_player.GetRect().x, p_player.GetRect().y);
                    while (SDL_PollEvent(&g_event) != 0)
                    {
                        if (g_event.type == SDL_QUIT)
                        {
                            play = false;
                            end = true;
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
                                end = true;
                            }
                        }
                    }
                    load_pause.SetRect(0, SCREEN_HEIGHT / 3 - load_pause.GetRect().h);
                    load_pause.Render2(g_screen, NULL);
                    SDL_RenderPresent(g_screen);
                }
                else if (!paused)
                {
                    if (!win) {
                        fps_timer.start();

                        Mix_ResumeMusic();

                        while (SDL_PollEvent(&g_event) != 0)
                        {
                            if (g_event.type == SDL_QUIT)
                            {
                                play = false;
                                end = true;
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
                                    end = true;
                                }
                            }
                            p_player.HandleInputAction(g_event, g_screen, g_sound_fire);
                        }
                        SDL_RenderClear(g_screen);
                        SDL_ShowCursor(SDL_DISABLE);

                        //Main game functions
                        p_player.HandleMove();

                        //SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                        SDL_RenderClear(g_screen);

                        //Background Scrolling
                        bkgn_x += 1;
                        g_background.Render1(g_screen, NULL, 0, bkgn_x);
                        g_background.Render1(g_screen, NULL, 0, bkgn_x - SCREEN_HEIGHT);
                        if (bkgn_x >= SCREEN_HEIGHT)
                        {
                            bkgn_x = 0;
                        }

                        int exp_frame_width = exp_threat.get_fr_width();
                        int exp_frame_height = exp_threat.get_fr_height();
                        //spaceship threat create
                        if (player_score <= 40) {
                            for (int ii = 0; ii < NUM_THREAT; ii++) {
                                Enemy* p_threat = (p_threats + ii);
                                //if (p_threat) {
                                    if (p_threat->get_dir())
                                    {
                                        p_threat->HandleMoveLtoR(SCREEN_WIDTH, SCREEN_HEIGHT);
                                    }
                                    else
                                    {
                                        p_threat->HandleMoveRtoL(SCREEN_WIDTH, SCREEN_HEIGHT);
                                    }
                                    p_threat->Render(g_screen, NULL, 100, 100);
                                    p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

                                    //collision check

                                    if (!p_player.cheatsw())
                                    {
                                        //nguoi va cham voi quai
                                        bool is_col = SDLCommonFunction::CheckCollision(p_player.GetRect(), p_threat->GetRect());
                                        if (SDL_GetTicks() - invi_timer >= 1500)
                                        {
                                            if (is_col)
                                            {
                                                p_threat->Reset(-100);
                                                Mix_PlayChannel(-1, g_sound_explo[0], 0);
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

                                                    invi_timer = SDL_GetTicks();
                                                }
                                                else {
                                                    Mix_PlayChannel(-1, g_sound_explo[0], 0);
                                                    SDLCommonFunction::CheckHighScore(player_score);
                                                    GameOver = true;

                                                }
                                            }
                                        }
                                        //va cham nguoi va dan quai
                                        std::vector<Bullet*> bullet_list_threat = p_threat->GetBulletList();
                                        for (int iat = 0; iat < bullet_list_threat.size(); iat++)
                                        {
                                            Bullet* p_bullet_threat = bullet_list_threat.at(iat);
                                            if (p_bullet_threat != NULL)
                                            {
                                                if (SDL_GetTicks() - invi_timer >= 1500)
                                                {
                                                    bool ret_col_threat = SDLCommonFunction::CheckCollision(p_bullet_threat->GetRect(), p_player.GetRect());
                                                    if (ret_col_threat)
                                                    {
                                                        p_threat->ResetBullet(p_bullet_threat);
                                                        Mix_PlayChannel(-1, g_sound_explo[1], 0);
                                                        for (int ex = 0; ex < explosion_frame; ex++)
                                                        {
                                                            int x_pos = (p_player.GetRect().x + p_player.GetRect().w * 0.5) - exp_frame_width * 0.5;
                                                            int y_pos = (p_player.GetRect().y + p_player.GetRect().h * 0.5) - exp_frame_height * 0.5;

                                                            exp_threat.set_frame(ex);
                                                            exp_threat.SetRect(x_pos, y_pos);
                                                            exp_threat.render_explosion(g_screen);
                                                            SDL_RenderPresent(g_screen);
                                                        }
                                                        //p_threat->ResetBullet(p_bullet_threat);
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
                                                            invi_timer = SDL_GetTicks();
                                                        }
                                                        else
                                                        {
                                                            Mix_PlayChannel(-1, g_sound_explo[0], 0);
                                                            SDLCommonFunction::CheckHighScore(player_score);
                                                            GameOver = true;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    //nguoi ban trung quai

                                    std::vector<Bullet*> bullet_list = p_player.GetBulletList();
                                    for (int ia = 0; ia < bullet_list.size(); ia++)
                                    {
                                        Bullet* p_bullet = bullet_list.at(ia);
                                        if (p_bullet != NULL)
                                        {
                                            bool ret_col = SDLCommonFunction::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());
                                            if (ret_col)
                                            {
                                                Mix_PlayChannel(2, g_sound_explo[2], 0);
                                                for (int ex = 0; ex < explosion_frame; ex++)
                                                {
                                                    int x_pos = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5) - exp_frame_width * 0.5;
                                                    int y_pos = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5) - exp_frame_height * 0.5;

                                                    exp_threat.set_frame(ex);
                                                    exp_threat.SetRect(x_pos, y_pos);
                                                    exp_threat.render_explosion(g_screen);
                                                    SDL_RenderPresent(g_screen);
                                                    SDL_Delay(2);
                                                }

                                                p_player.DestroyBullet(ia);
                                                p_threat->Reset(-100);
                                                player_score++;
                                                break;
                                            }
                                        }
                                    }
                                //}
                                /*else
                                {
                                    p_threat->HandleMoveRtoL(SCREEN_WIDTH, SCREEN_HEIGHT);
                                }*/
                                p_threat->Render(g_screen, NULL, 100, 100);
                                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                                p_threat = NULL;
                                delete p_threat;
                            }
                        }

                        //meteor threat init & collision
                        if (player_score >= 15 && player_score < 40) {
                            for (int ii = 0; ii < NUM_THREAT - 1; ii++) {
                                Enemy* meteor = (meteors + ii);
                                if (meteor) {
                                    meteor->HandleMoveMeteor(SCREEN_WIDTH, SCREEN_HEIGHT);
                                    meteor->Render2(g_screen, NULL);
                                    if (!p_player.cheatsw()) {
                                        bool is_col = SDLCommonFunction::CheckCollision(p_player.GetRect(), meteor->GetRect());
                                        if (SDL_GetTicks() - invi_timer >= 1500)
                                        {
                                            if (is_col)
                                            {
                                                meteor->Reset(-100);
                                                Mix_PlayChannel(-1, g_sound_explo[0], 0);
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

                                                    invi_timer = SDL_GetTicks();
                                                }
                                                else {
                                                    Mix_PlayChannel(-1, g_sound_explo[0], 0);
                                                    SDLCommonFunction::CheckHighScore(player_score);
                                                    GameOver = true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        //boss 
                        if (player_score >= 40)
                        {
                            boss->HandleMoveBoss(SCREEN_WIDTH, SCREEN_HEIGHT);
                            boss->Render2(g_screen, NULL);
                            boss->MakeBulletMid(g_screen, boss);

                            //upgraded canon
                            p_player.SetBulletType(1);

                            if (!p_player.cheatsw()) {
                                //nguoi va cham voi boss
                                bool is_col = SDLCommonFunction::CheckCollision(p_player.GetRect(), boss->GetRect());
                                if (SDL_GetTicks() - invi_timer >= 1500)
                                {
                                    if (is_col)
                                    {
                                        Mix_PlayChannel(-1, g_sound_explo[0], 0);
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

                                            invi_timer = SDL_GetTicks();
                                        }
                                        else {
                                            Mix_PlayChannel(-1, g_sound_explo[0], 0);
                                            SDLCommonFunction::CheckHighScore(player_score);
                                            GameOver = true;
                                        }
                                    }
                                }

                                //nguoi va cham dan boss
                                std::vector<Bullet*> Bullet_list_boss = boss->GetBulletList();
                                for (int iat = 0; iat < Bullet_list_boss.size(); iat++)
                                {
                                    Bullet* p_bullet_boss = Bullet_list_boss.at(iat);
                                    if (p_bullet_boss != NULL)
                                    {
                                        if (SDL_GetTicks() - invi_timer >= 1500)
                                        {
                                            bool ret_col_threat = SDLCommonFunction::CheckCollision(p_bullet_boss->GetRect(), p_player.GetRect());
                                            if (ret_col_threat)
                                            {
                                                boss->ResetBullet(p_bullet_boss);
                                                Mix_PlayChannel(-1, g_sound_explo[1], 0);
                                                for (int ex = 0; ex < explosion_frame; ex++)
                                                {
                                                    int x_pos = (p_player.GetRect().x + p_player.GetRect().w * 0.5) - exp_frame_width * 0.5;
                                                    int y_pos = (p_player.GetRect().y + p_player.GetRect().h * 0.5) - exp_frame_height * 0.5;

                                                    exp_threat.set_frame(ex);
                                                    exp_threat.SetRect(x_pos, y_pos);
                                                    exp_threat.render_explosion(g_screen);
                                                    SDL_RenderPresent(g_screen);
                                                }
                                                SDL_Delay(500);
                                                death_counts++;
                                                if (death_counts <= 2)
                                                {
                                                    SDL_Delay(100);
                                                    p_player.reset_main_pos(START_XPOS_MAIN, START_YPOS_MAIN);
                                                    player_health.minus_health();
                                                    player_health.show_heart(g_screen);
                                                    invi_timer = SDL_GetTicks();
                                                }
                                                else
                                                {
                                                    Mix_PlayChannel(-1, g_sound_explo[0], 0);
                                                    SDLCommonFunction::CheckHighScore(player_score);
                                                    GameOver = true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            //nguoi ban trung boss
                            std::vector<Bullet*> Bullet_list_player = p_player.GetBulletList();
                            for (int ia = 0; ia < Bullet_list_player.size(); ia++)
                            {
                                Bullet* p_bullet_player = Bullet_list_player.at(ia);
                                if (p_bullet != NULL)
                                {
                                    bool ret_col = SDLCommonFunction::CheckCollision(p_bullet_player->GetRect(), boss->GetRect());
                                    if (ret_col)
                                    {
                                        boss_health --;

                                        Mix_PlayChannel(2, g_sound_explo[2], 0);
                                        /*for (int ex = 0; ex < explosion_frame; ex++)
                                        {
                                            int x_pos = (boss->GetRect().x + boss->GetRect().w * 0.5) - exp_frame_width * 0.5;
                                            int y_pos = (boss->GetRect().y + boss->GetRect().h * 0.5) - exp_frame_height * 0.5;

                                            exp_threat.set_frame(ex);
                                            exp_threat.SetRect(x_pos, y_pos);
                                            exp_threat.render_explosion(g_screen);
                                            SDL_RenderPresent(g_screen);
                                            SDL_Delay(1);
                                        }*/

                                        p_player.DestroyBullet(ia);
                                        if (boss_health == 0) 
                                        {

                                            Mix_PlayChannel(2, g_sound_explo[0], 0);
                                            Mix_PlayChannel(2, g_sound_explo[1], 0);
                                            Mix_PlayChannel(2, g_sound_explo[2], 0);
                                            
                                            for (int ex = 0; ex < explosion_frame; ex++)
                                            {
                                                int x_pos = (boss->GetRect().x + boss->GetRect().w * 0.5) - exp_frame_width * 0.5;
                                                int y_pos = (boss->GetRect().y + boss->GetRect().h * 0.5) - exp_frame_height * 0.5;

                                                exp_threat.set_frame(ex);
                                                exp_threat.SetRect(x_pos, y_pos);
                                                exp_threat.render_explosion(g_screen);
                                                SDL_RenderPresent(g_screen);
                                                SDL_Delay(1);
                                            }
                                            boss->Reset(-600);
                                            
                                            player_score += 40;
                                            SDL_Delay(500);
                                            win = true;
                                        }
                                        break;
                                    }
                                }
                            }
                        }

                        p_player.MakeBullet(g_screen);
                        p_player.Render(g_screen, NULL);

                        // render health
                        player_health.show_heart(g_screen);

                        //player score 
                        std::string string_score = "Score ";
                        std::string string_gameover = "Your Score";


                        //game score
                        std::string score_value = std::to_string(player_score * 100);
                        string_score += score_value;
                        game_mark.settext(string_score);
                        game_mark.Loadfromrendertext(g_font, g_screen);
                        game_mark.loadtexttoscreen(g_screen, 350, 0);
                        std::string score_gameover = std::to_string(player_score * 100);
                        game_over_mark.settext(score_gameover);
                        game_over_mark.Loadfromrendertext(Gameover_font, g_screen);
                        game_over.settext(string_gameover);
                        game_over.Loadfromrendertext(Gameover_font, g_screen);

                        //push game time to screen
                        std::string string_time = "Time ";
                        time_value = SDL_GetTicks() / 1000;
                        std::string string_value = std::to_string(time_value);
                        string_time += string_value;
                        game_time.settext(string_time);
                        game_time.Loadfromrendertext(g_font, g_screen);
                        game_time.loadtexttoscreen(g_screen, 150, 0);

                        SDL_RenderPresent(g_screen);

                        int real_time = fps_timer.get_ticks();
                        int time_one_frame = (1200 / 3) / FRAME_PER_SEC; //ms

                        if (real_time < time_one_frame) {
                            int delay_time = time_one_frame - real_time;
                            if (delay_time >= 0) {
                                SDL_Delay(delay_time - 1);
                            }
                        }
                    }
                    else if (win)
                    {
                        p_player.Reset(START_XPOS_MAIN, START_YPOS_MAIN);
                        std::vector<Bullet*> bullet_list_player = p_player.GetBulletList();
                        for (int ia = 0; ia < bullet_list_player.size(); ia++)
                        {
                            p_player.DestroyBullet(ia);
                        }
                        SDL_ShowCursor(SDL_ENABLE);
                        while (SDL_PollEvent(&g_event) != 0)
                        {
                            if (g_event.type == SDL_QUIT)
                            {
                                play = false;
                                win = true;
                                end = true;
                            }

                            ExitButton.Exit(g_event, g_screen, play, end);
                        }
                        load_win.Render2(g_screen, NULL);
                        ExitButton.SetRect(SCREEN_WIDTH / 2 - ExitButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 - ExitButton.get_height_frame() + 250);
                        ExitButton.Render2(g_screen, NULL);
                        SDL_RenderPresent(g_screen);

                    }
                }
            }
            else if (GameOver)
            {
                SDL_ShowCursor(SDL_ENABLE);
                while (SDL_PollEvent(&g_event) != 0)
                {
                    if (g_event.type == SDL_QUIT)
                    {
                        play = false;
                        end = false;
                    }
                    RestartButton.Menu(g_event,time_value, g_screen, player_score, menu, QuitMenu, play, end, win,player_health);
                    ExitButton.Exit(g_event, g_screen, play, end);
                }
                Gameover.Render2(g_screen, NULL);
                game_over.Loadfromrendertext(Gameover_font, g_screen);
                game_over.loadtexttoscreen(g_screen, SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT / 2 - 100);
                game_over_mark.Loadfromrendertext(Gameover_font, g_screen);
                game_over_mark.loadtexttoscreen(g_screen, SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 20);
                RestartButton.SetRect(SCREEN_WIDTH / 2 - RestartButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 - RestartButton.get_height_frame() + 150);
                RestartButton.Render2(g_screen, NULL);
                ExitButton.SetRect(SCREEN_WIDTH / 2 - ExitButton.get_width_frame() / 2, SCREEN_HEIGHT / 2 - ExitButton.get_height_frame() + 250);
                ExitButton.Render2(g_screen, NULL);
                SDL_RenderPresent(g_screen);
            }
        }
    }
    close();
    return 0;
}
