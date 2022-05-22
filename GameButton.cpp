#include "GameButton.h"
#include "Common_Function.h"
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
    bool check_load = BaseObject::loadImg(path,screen);
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
void GameButton::Play(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &play,bool &QuitMenu, bool &help)
{
	if(Inside(event))
	{
	    LoadTexture("img//PlayButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
			play = true;
			QuitMenu = true;
			menu = false;
			help = false;
		}
	}
	else
	{
		LoadTexture("img//PlayButton.png",screen);
	}
}
void GameButton::Help(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help)
{
	if(Inside(event))
	{
	    LoadTexture("img//HelpButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    help=true;
            menu=false;
		}
	}
	else
	{
		LoadTexture("img//HelpButton.png",screen);
	}
}
void GameButton::Exit(SDL_Event event,SDL_Renderer* screen,bool &QuitMenu, bool &end)
{
    if(Inside(event))
	{
	    LoadTexture("img//ExitButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    QuitMenu=!QuitMenu;
			end = true;
		}
	}
	else
	{
		LoadTexture("img//ExitButton.png",screen);
	}
}
void GameButton::Back(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help, bool& score)
{
    if(Inside(event))
	{
	    LoadTexture("img//BackButton2.png",screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    menu=true;
		    help=false;
			score = false;
		}
	}
	else
	{
		LoadTexture("img//BackButton.png",screen);
	}
}

void GameButton::HighScore(SDL_Event event, SDL_Renderer* screen, bool& menu, bool& score)
{
	if (Inside(event))
	{
		LoadTexture("img//Score2.png", screen);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			score = true;
			menu = false;
		}
	}
	else
	{
		LoadTexture("img//Score.png", screen);
	}
}
void GameButton::Menu(SDL_Event event, SDL_Renderer* screen,int &score, bool &menu, bool& QuitMenu, bool &play,bool &end) {
	if (Inside(event))
	{
		LoadTexture("img//MainMenu2.png", screen);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			play = false;
			QuitMenu = false;
			menu = true;
			end = false;
			score = 0;
		}
	}
	else
	{
		LoadTexture("img//MainMenu.png", screen);
	}
}