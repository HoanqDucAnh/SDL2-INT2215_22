#pragma once
#include "ThreatObject.h"

ThreatsObject::ThreatsObject()
{
    rect_.x = SCREEN_WIDTH * 0.5 ;
    rect_.y = SCREEN_HEIGHT;
    rect_.w = WIDTH_THREAT;
    rect_.h = HEIGHT_THREAT;

    x_val_ = 0;
    y_val_ = 0;

}

// Hàm hủy quái
ThreatsObject::~ThreatsObject()
{
    if (p_amo_list.size() > 0)
    {
        for (int i = 0; i < p_amo_list.size(); i++)
        {
            AmoObject* p_amo = p_amo_list.at(i);
            if (p_amo != NULL)
            {
                delete p_amo;
                p_amo = NULL;
            }
        }
        p_amo_list.clear();
    }
}

// Đạn của quái
void ThreatsObject::InitAmo(AmoObject* p_amo, const int& speed, SDL_Renderer* des)
{
    if (p_amo)
    {
        bool ret = p_amo->loadImg("egg.png", des);
        if (ret)
        {
           
            p_amo->set_is_move(true);
            p_amo->SetWidthHeight(WIDTH_LAZER, HEIGHT_LAZER);
            p_amo->SetRect(this->rect_.x + WIDTH_THREAT / 2 , this->rect_.y - HEIGHT_THREAT / 2 );
            p_amo->Set_y_val(speed);
            p_amo_list.push_back(p_amo);
        }
    }
}

// Load đạn lên screen
void ThreatsObject::MakeAmo(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i < p_amo_list.size(); i++)
    {
        AmoObject* p_amo = p_amo_list.at(i);
        if (p_amo)
        {
            if (p_amo->get_is_move())
            {
                p_amo->Render(des, NULL, rect_.x, rect_.y);
                p_amo->HandleMoveOfThreat();
            }
            else 

           // p_amo->Render(des, NULL, rect_.x, rect_.y);
//            p_amo->HandleMoveOfThreat();

  //          if (!p_amo->get_is_move())
            {
                p_amo->set_is_move(true);
                p_amo->SetRect(rect_.x + rect_.h / 3, rect_.y + rect_.h);
            }
        }
    }
}

void ThreatsObject::HandleInputAction(SDL_Event events)
{

}

// Di chuyển của quái
void ThreatsObject::HandleMove(const int& x_border, const int& y_border)
{
    rect_.y -= 2;
    if (rect_.y > SCREEN_HEIGHT)
    {
        rect_.y = 0;
        int rand_x = rand() % 1100;
        if (rand_x > SCREEN_WIDTH)
        {
            rand_x = SCREEN_WIDTH * 0.3;
        }
        rect_.x = rand_x;
    }
}


void ThreatsObject::HandleMoveRtoL(const int& x_border, const int& y_border)
{
    rect_.x -= 1;
    //rect_.y -= 1;
    if (rect_.x > SCREEN_WIDTH)
    {
        rect_.x = 700;
        int rand_y = rand() % 1100;
        if (rand_y > SCREEN_HEIGHT / 2)
        {
            rand_y = SCREEN_HEIGHT * 0.3;
        }
        rect_.y = rand_y;
    }
}

void ThreatsObject::HandleMoveLtoR(const int& x_border, const int& y_border)
{
    rect_.x += 1;
    //rect_.y -= 1;
    if (rect_.x > SCREEN_WIDTH)
    {
        rect_.x = -100;
        int rand_y = rand() % 1100;
        if (rand_y > SCREEN_HEIGHT/2)
        {
            rand_y = SCREEN_HEIGHT * 0.3;
        }
        rect_.y = rand_y;
    }
}

// Reset quái sau khi chết
void ThreatsObject::Reset(const int& xborder)
{
    int rand_x = rand() % 2;
    if (rand_x)
    {
        rect_.x = xborder;
        set_direction(true); //true là từ Left to Right
    }
    else
    {
        rect_.x = 600;
        set_direction(false); //false là từ right to left
    }
    int rand_y = rand() % 400;
    if (rand_y > SCREEN_HEIGHT*2/5)
    {
        rand_y *= 0.3;
    }
    rect_.y = rand_y;
    for (int i = 0; i < p_amo_list.size(); i++)
    {
        AmoObject* p_amo = p_amo_list.at(i);
        if (!p_amo->get_is_move())
        {
            ResetAmo(p_amo);
        }
    }
    
}

void ThreatsObject::ResetAmo(AmoObject* p_amo)
{
    p_amo->SetRect(rect_.x + rect_.h, rect_.y + rect_.h);
}

void ThreatsObject::HandleMoveBoss(const int& x_border, const int& y_border)
{
    rect_.x += x_val_;
    if (rect_.x > SCREEN_WIDTH - 400)
        rect_.x = 300;
    else if (rect_.x < 300)
        rect_.x = 300;
}

void ThreatsObject::HandleMoveMeteor(const int& x_border, const int& y_border)
{
    rect_.y -= 2;
    if (rect_.y > SCREEN_HEIGHT)
    {
        rect_.y = 0;
        int rand_x = rand() % 1100;
        if (rand_x > SCREEN_WIDTH)
        {
            rand_x = SCREEN_WIDTH * 0.3;
        }
        rect_.x = rand_x;
    }
}

void ThreatsObject::Reset1() {
    direction = false;
    p_amo_list.erase(p_amo_list.begin(), p_amo_list.begin() + p_amo_list.size());
}