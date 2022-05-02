#include "explosion.h"

ExplosionObj::ExplosionObj()
{
	frame_width = 0;
	frame_height = 0;
	frame = 0;
}

ExplosionObj::~ExplosionObj()
{

}

bool ExplosionObj::loadImg(std::string path, SDL_Renderer* screen)
{
	bool success = BaseObject::loadImg(path, screen);

	if (success) {
		frame_width = rect_.w / explosion_frame;
		frame_height = rect_.h;
	}

	return success;
}
void ExplosionObj::set_clip()
{
	if (frame_width > 0 && frame_height > 0) {
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = frame_width;
		frame_clip[0].h = frame_height;

		frame_clip[1].x = frame_width;
		frame_clip[1].y = 0;
		frame_clip[1].w = frame_width;
		frame_clip[1].h = frame_height;

		frame_clip[2].x = frame_width * 2;
		frame_clip[2].y = 0;
		frame_clip[2].w = frame_width;
		frame_clip[2].h = frame_height;

		frame_clip[3].x = frame_width * 3;
		frame_clip[3].y = 0;
		frame_clip[3].w = frame_width;
		frame_clip[3].h = frame_height;

		frame_clip[4].x = frame_width * 4;
		frame_clip[4].y = 0;
		frame_clip[4].w = frame_width;
		frame_clip[4].h = frame_height;

		frame_clip[5].x = frame_width * 5;
		frame_clip[5].y = 0;
		frame_clip[5].w = frame_width;
		frame_clip[5].h = frame_height;

		frame_clip[6].x = frame_width * 6;
		frame_clip[6].y = 0;
		frame_clip[6].w = frame_width;
		frame_clip[6].h = frame_height;

		frame_clip[7].x = frame_width * 7;
		frame_clip[7].y = 0;
		frame_clip[7].w = frame_width;
		frame_clip[7].h = frame_height;

		
		/*
		frame_clip[8].x = frame_width * 8;
		frame_clip[8].y = 0;
		frame_clip[8].w = frame_width;
		frame_clip[8].h = frame_height;

		frame_clip[9].x = frame_width * 9;
		frame_clip[9].y = 0;
		frame_clip[9].w = frame_width;
		frame_clip[9].h = frame_height;

		frame_clip[10].x = frame_width * 10;
		frame_clip[10].y = 0;
		frame_clip[10].w = frame_width;
		frame_clip[10].h = frame_height;

		frame_clip[11].x = frame_width * 11;
		frame_clip[11].y = 0;
		frame_clip[11].w = frame_width;
		frame_clip[11].h = frame_height;

		frame_clip[12].x = frame_width * 12;
		frame_clip[12].y = 0;
		frame_clip[12].w = frame_width;
		frame_clip[12].h = frame_height;

		frame_clip[13].x = frame_width * 13;
		frame_clip[13].y = 0;
		frame_clip[13].w = frame_width;
		frame_clip[13].h = frame_height;

		frame_clip[14].x = frame_width * 14;
		frame_clip[14].y = 0;
		frame_clip[14].w = frame_width;
		frame_clip[14].h = frame_height;

		frame_clip[15].x = frame_width * 15;
		frame_clip[15].y = 0;
		frame_clip[15].w = frame_width;
		frame_clip[15].h = frame_height;

		frame_clip[16].x = frame_width * 16;
		frame_clip[16].y = 0;
		frame_clip[16].w = frame_width;
		frame_clip[16].h = frame_height;

		frame_clip[17].x = frame_width * 17;
		frame_clip[17].y = 0;
		frame_clip[17].w = frame_width;
		frame_clip[17].h = frame_height;

		frame_clip[18].x = frame_width * 18;
		frame_clip[18].y = 0;
		frame_clip[18].w = frame_width;
		frame_clip[18].h = frame_height;

		frame_clip[19].x = frame_width * 19;
		frame_clip[19].y = 0;
		frame_clip[19].w = frame_width;
		frame_clip[19].h = frame_height;

		frame_clip[20].x = frame_width * 20;
		frame_clip[20].y = 0;
		frame_clip[20].w = frame_width;
		frame_clip[20].h = frame_height;

		frame_clip[21].x = frame_width * 21;
		frame_clip[21].y = 0;
		frame_clip[21].w = frame_width;
		frame_clip[21].h = frame_height;

		frame_clip[22].x = frame_width * 22;
		frame_clip[22].y = 0;
		frame_clip[22].w = frame_width;
		frame_clip[22].h = frame_height;

		frame_clip[23].x = frame_width * 23;
		frame_clip[23].y = 0;
		frame_clip[23].w = frame_width;
		frame_clip[23].h = frame_height;

		*/
	}
}

void ExplosionObj::render_explosion(SDL_Renderer* screen)
{
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect render_quad = { rect_.x,rect_.y,frame_width,frame_height };
	if (current_clip)
	{
		render_quad.w = current_clip->w;
		render_quad.h = current_clip->h;
	}

	SDL_RenderCopy(screen, p_object_, current_clip, &render_quad);
}