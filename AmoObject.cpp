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
void AmoObject::HandleMove(const int& x_border, const int& y_border)
{
    rect_.y -= 3;
    if (rect_.y > y_border)
    {
        is_move_ = false;
    }
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
