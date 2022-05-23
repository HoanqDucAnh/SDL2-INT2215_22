#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatObject.h"


using namespace std;

class GameButton : public BaseObject
{
public:
	GameButton();
	~GameButton();
	virtual bool LoadTexture(string path,SDL_Renderer* screen);
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}
	// kiem tra bam vao nut
	bool Inside(SDL_Event event);
	//cac nut trong game
	void Menu(SDL_Event event, SDL_Renderer* screen, int& score, bool& menu, bool& QuitMenu, bool& Gameover, bool& end, bool& win);
	void Play(SDL_Event event,SDL_Renderer* des,bool &menu,bool &play,bool &QuitMenu, bool &help);
	void HighScore(SDL_Event event, SDL_Renderer* des, bool& menu, bool& score);
	void Help(SDL_Event event, SDL_Renderer* des, bool& menu, bool& help);
	void Back(SDL_Event event,SDL_Renderer* des,bool &menu,bool &help, bool &score);
	void Exit(SDL_Event event, SDL_Renderer* des, bool& QuitMenu, bool& end);
	
private:
    int width_frame;
    int height_frame;
};

#endif // BUTTON_H_INCLUDED
