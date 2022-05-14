#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "PlayerHealth.h"

using namespace std;

class GameButton : public BaseObject
{
public:
	GameButton();
	~GameButton();
	virtual bool LoadTexture(string path,SDL_Renderer* screen);
    int get_frame_width() const {return width_frame;}
    int get_frame_height() const {return height_frame;}
	bool Inside(SDL_Event event);
	void PlayButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &play,bool &QuitMenu);
	void HelpButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help);
	void ExitButton(SDL_Event event,SDL_Renderer* screen,bool &QuitMenu);
	void BackButton(SDL_Event event,SDL_Renderer* screen,bool &menu,bool &help);
	void HighScoreButton(SDL_Event event, SDL_Renderer* screen, bool& menu, bool& score);
	void RestartButton(SDL_Event event, SDL_Renderer* screen, MainObject &p_player, ThreatsObject* &threat, PlayerHealth &health, int &player_score,bool &GameOver, int &time_value);
private:
    int width_frame;
    int height_frame;
};

#endif // BUTTON_H_INCLUDED
