#include "MainObject.h"

bool MainObject::loadImg(std::string path, SDL_Renderer* screen) {
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }

    p_object_ = new_texture;

    return p_object_ != NULL;
}

MainObject::MainObject(int x, int y)
{
	x_pos_ = x;
	y_pos_ = y;
	rect_.w = DOT_WIDTH;
	rect_.h = DOT_HEIGHT;
	x_val_ = 0;
	y_val_ = 0;
}

void MainObject::HandleInputAction(SDL_Event e, SDL_Renderer* des, Mix_Chunk* fire_sound[2]) 
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: y_val_ -= DOT_VEL; break;
			case SDLK_DOWN: y_val_ += DOT_VEL; break;
			case SDLK_LEFT: x_val_ -= DOT_VEL; break;
			case SDLK_RIGHT: x_val_ += DOT_VEL; break;
			case SDLK_SLASH:
				if (!cheat_sw)
				{
					cheat_sw = true;
					std::cout << "cheat is on boiii!!! U R GOD!\n";
				}
				else
				{
					cheat_sw = false;
					std::cout << "no mor cheet for u boi\n";
				}
				break;
			case SDLK_SPACE:
				if (ammo_type == 0)
				{
					Bullet* p_bullet = new Bullet();

					Mix_PlayChannel(-1, fire_sound[0], 0);

					p_bullet->loadImg("img//bullet.png", des);
					p_bullet->SetWidthHeight(WIDTH_LAZER, HEIGHT_LAZER);
					
					p_bullet->set_is_move(true);
					p_bullet->set_angle(90);
					p_bullet->Set_y_val(2);
					p_bullet->Set_x_val(2);

					p_bullet->set_pos(x_pos_ + DOT_WIDTH / 2 - (p_bullet->GetRect().w) / 2, y_pos_ + DOT_HEIGHT / 2);
					p_bullet_list.push_back(p_bullet);
				}
				if (ammo_type == 1)
				{
					Mix_PlayChannel(-1, fire_sound[0], 0);

					Mix_PlayChannel(-1, fire_sound[1], 0);
					for (int i = 0; i < 5; i++) {
				  		Bullet* p_bullet = new Bullet();
						p_bullet->loadImg("img//bulletr.png", des);
						p_bullet->SetWidthHeight(WIDTH_LAZER, HEIGHT_LAZER);

						p_bullet->set_angle(80 + 5 * i);
						p_bullet->Set_y_val(2);
						p_bullet->Set_x_val(2);
						p_bullet->set_is_move(true);

						p_bullet->set_pos(x_pos_ + DOT_WIDTH / 2 - (p_bullet->GetRect().w) / 2, y_pos_ + DOT_HEIGHT / 2);
						p_bullet_list.push_back(p_bullet);
					}
				}
				break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: y_val_ += DOT_VEL; break;
			case SDLK_DOWN: y_val_ -= DOT_VEL; break;
			case SDLK_LEFT: x_val_ += DOT_VEL; break;
			case SDLK_RIGHT: x_val_ -= DOT_VEL; break;
		}
	}
}



void MainObject::MakeBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		Bullet* p_bullet = p_bullet_list.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->Render(des, NULL, this->rect_.x, this->rect_.y);

				if (ammo_type == 0)
				{
					p_bullet->HandleMoveMain(SCREEN_WIDTH, SCREEN_HEIGHT);
				}
				else if (ammo_type == 1)
				{
					p_bullet->HandleMoveBoss(SCREEN_WIDTH, SCREEN_HEIGHT);
				}				
			}
			else
			{
				p_bullet_list.erase(p_bullet_list.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}


void MainObject::SetBulletType(int type)
{
	ammo_type = type;
}


void MainObject::HandleMove()
{
	x_pos_ += x_val_;

	//If the dot collided or went too far to the left or right
	if ((x_pos_ < 0) || (x_pos_ + 81 > SCREEN_WIDTH))
	{
		//Move back
		x_pos_ -= x_val_;
	}

	//Move the dot up or down
	y_pos_ += y_val_;

	//If the dot collided or went too far up or down
	if ((y_pos_ < 0) || (y_pos_ + 53 > SCREEN_HEIGHT))
	{
		//Move back
		y_pos_ -= y_val_;
	}
}
void MainObject::Render(SDL_Renderer* des, SDL_Rect* clip)
{	
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { rect_.x, rect_.y, DOT_WIDTH, DOT_HEIGHT };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(des, p_object_, clip, &renderQuad);
}

void MainObject::DestroyBullet(const int& idx)
{
	//for (int i = 0; i < p_bullet_list.size(); i++)
	//{
		if (idx < p_bullet_list.size())
		{
			Bullet* p_bullet = p_bullet_list.at(idx);
			p_bullet_list.erase(p_bullet_list.begin() + idx);

			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	//}
}

void MainObject::reset_main_pos(int x, int y)
{
	x_pos_ = x;
	y_pos_ = y;
	//.w = DOT_WIDTH;
	//rect_.h = DOT_HEIGHT;
}

int MainObject::fetchScore()
{
	return score;
}

bool MainObject::cheatsw()
{
	return cheat_sw;
}

void MainObject::incScore()
{
	score++;
}
void MainObject::Reset(int x, int y) {
	x_pos_ = x;
	y_pos_ = y;
	//rect_.w = DOT_WIDTH;
	//rect_.h = DOT_HEIGHT;
}