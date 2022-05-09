#include "GameButton.h"
using namespace std;
GameButton::GameButton()
{
	width_frame=0;
    height_frame=0;
}
GameButton::~GameButton()
{
}
bool GameButton::LoadTexture(string path, SDL_Renderer* screen)
{
    bool check_load=BaseObject::loadImg(path,screen);
    if(check_load==true)
    {
        width_frame=rect_.w;
        height_frame= rect_.h;
    }
    return check_load;
}
bool GameButton::Inside(SDL_Event event)
{
	if (event.type==SDL_MOUSEMOTION || event.type==SDL_MOUSEBUTTONDOWN || event.type==SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside=true;
		if (x<rect_.x)
		{
			inside=false;
		}
		else if (x> rect_.x+width_frame)
		{
			inside=false;
		}
		else if (y< rect_.y)
		{
			inside=false;
		}
		else if (y> rect_.y+height_frame)
		{
			inside=false;
		}
		return inside;
	}
	return 0;
}
void GameButton::PlayButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &play,bool &QuitMenu)
{
	if(Inside(event))
	{
	    LoadTexture("PlayButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    play=true;
		    QuitMenu=true;
			menu=false;
		}
	}
	else
	{
		LoadTexture("PlayButton.png",screen);
	}
}
void GameButton::HelpButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help)
{
	if(Inside(event))
	{
	    LoadTexture("HelpButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    help=true;
            menu=false;
		}
	}
	else
	{
		LoadTexture("HelpButton.png",screen);
	}
}
void GameButton::ExitButton(SDL_Event event,SDL_Renderer* screen,bool &QuitMenu)
{
    if(Inside(event))
	{
	    LoadTexture("ExitButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    QuitMenu=!QuitMenu;
		}
	}
	else
	{
		LoadTexture("ExitButton.png",screen);
	}
}
void GameButton::BackButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help)
{
    if(Inside(event))
	{
	    LoadTexture("BackButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    menu=true;
		    help=false;
		}
	}
	else
	{
		LoadTexture("BackButton.png",screen);
	}
}

void GameButton::HighScoreButton(SDL_Event event, SDL_Renderer* screen, bool& menu, bool& score)
{
	if (Inside(event))
	{
		LoadTexture("Score2.png", screen);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			score = true;
			menu = false;
		}
	}
	else
	{
		LoadTexture("Score.png", screen);
	}
}
