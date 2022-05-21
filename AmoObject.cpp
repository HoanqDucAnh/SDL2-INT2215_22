#include "AmoObject.h"

AmoObject::AmoObject()
{
    rect_.x = 0;
    rect_.y = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}

AmoObject::~AmoObject()
{
}

// Di chuyển đạn cuả nhân vật
void AmoObject::HandleMoveBoss(const int& x_border, const int& y_border)
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

void AmoObject::HandleMoveMain(const int& x_border, const int& y_border) {
    y_pos -= 2;
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
void AmoObject::HandleMoveOfThreat()
{
    rect_.y += y_val_;
    if (rect_.y > SCREEN_HEIGHT)  //Khi gặp khung hình hoặc vật cản
    {
        is_move_ = false;
    }
}
