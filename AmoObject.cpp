#include "AmoObject.h"

//constructor
AmoObject::AmoObject()
{
    rect_.x = 0;
    rect_.y = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}
//deconstructor
AmoObject::~AmoObject()
{
}

//player's bullets
void AmoObject::HandleMove(const int& x_border, const int& y_border)
{
    rect_.y -= 3;
    if (rect_.y > y_border)
    {
        is_move_ = false;
    } 
}
void AmoObject::HandleMoveOfThreat()
{
    rect_.y += y_val_;
    if (rect_.y > SCREEN_HEIGHT)  //Khi gặp khung hình hoặc vật cản
    {
        is_move_ = false;
    }
}



