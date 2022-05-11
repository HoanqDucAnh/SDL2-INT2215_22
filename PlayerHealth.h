#pragma once
#include "BaseObject.h"
#include <vector>

class PlayerHealth : public BaseObject
{
public:
	PlayerHealth();
	~PlayerHealth();
	void set_number_of_lives(const int& lives_count) { lives_count_ = lives_count; };
	void set_heart_pos(const int& xpos);
	void show_heart(SDL_Renderer* screen);
	void init_heart(SDL_Renderer* screen);
	void minus_health();

private:
	int lives_count_;
	std::vector <int> heart_pos_list;
	int health_pos;
};