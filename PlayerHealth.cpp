#include "PlayerHealth.h"

PlayerHealth::PlayerHealth()
{

}

PlayerHealth::~PlayerHealth()
{

}

void PlayerHealth::set_heart_pos(const int& xpos)
{
	heart_pos_list.push_back(xpos);
}

void PlayerHealth::show_heart(SDL_Renderer* screen)
{
	if (lives_count_ == heart_pos_list.size()) {
		for (int i = 0; i < heart_pos_list.size(); i++) {
			health_pos = heart_pos_list.at(i);
			Render1(screen, NULL,health_pos,750);
		}
	}
}

void PlayerHealth::init_heart(SDL_Renderer* screen)
{
	lives_count_ = 3;
	if (heart_pos_list.size() > 0) {
		heart_pos_list.clear();
	}
	set_heart_pos(470);
	set_heart_pos(510);
	set_heart_pos(550);
}

void PlayerHealth::minus_health()
{
	lives_count_-=1;
	heart_pos_list.pop_back();
}
void PlayerHealth::Reset() {
	lives_count_ = 3;
	heart_pos_list.erase(heart_pos_list.begin(), heart_pos_list.begin() + heart_pos_list.size());
	health_pos = 0;
}