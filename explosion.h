#pragma once
#include "Common_Function.h"
#include "BaseObject.h"

#define explosion_frame 8

class ExplosionObj : public BaseObject
{
public:
	ExplosionObj();
	~ExplosionObj();

public:
	void set_clip();
	void set_frame(const int& fr) { frame = fr; }
	virtual bool loadImg(std::string path, SDL_Renderer* screen);
	void render_explosion(SDL_Renderer* screen);
	int get_fr_width() const { return frame_width; }
	int get_fr_height() const { return frame_height; }
private:
	int frame_width;
	int frame_height;
	unsigned int frame;
	SDL_Rect frame_clip[8];
};

