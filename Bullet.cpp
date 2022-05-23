#include "Bullet.h"

Bullet::Bullet()
{
    rect_.x = 0;
    rect_.y = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}

Bullet::~Bullet()
{

}
bool Bullet::LoadTexture(std::string path, SDL_Renderer* screen) {
    bool ret = BaseObject::loadImg(path, screen);
    return ret;
}

void Bullet::HandleMoveBoss(const int& x_border, const int& y_border)
{

    x_pos -= x_val_ * cos(angle * PI / 180);
    y_pos -= y_val_ * sin(angle * PI / 180);
    if (y_pos<0 || y_pos>y_border)
    {
        is_move_ = false;
    }
    if (x_pos<0 || x_pos>x_border)
    {
        is_move_ = false;
    }
    rect_.x = x_pos;
    rect_.y = y_pos;
}

// Di chuyển đạn cuả nhân vật
void Bullet::HandleMoveMain(const int& x_border, const int& y_border) {
    y_pos -= 4;
    if (y_pos<0 || y_pos>y_border)
    {
        is_move_ = false;
    }
    if (x_pos<0 || x_pos>x_border)
    {
        is_move_ = false;
    }
    rect_.x = x_pos;
    rect_.y = y_pos;
}


// Di chuyển đạn của quái
void Bullet::HandleMoveOfThreat()
{
    rect_.y += y_val_;
    if (rect_.y > SCREEN_HEIGHT)  //Khi gặp khung hình hoặc vật cản
    {
        is_move_ = false;
    }
}
