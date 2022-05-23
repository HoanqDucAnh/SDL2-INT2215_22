#pragma once
#include "Enemy.h"

Enemy::Enemy()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;

    x_val_ = 0;
    y_val_ = 0;
}

// Hàm hủy quái
Enemy::~Enemy()
{
    if (p_bullet_list.size() > 0)
    {
        for (int i = 0; i < p_bullet_list.size(); i++)
        {
            Bullet* p_bullet = p_bullet_list.at(i);
            if (p_bullet != NULL)
            {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
        p_bullet_list.clear();
    }
}

void Enemy::InitBullet4(SDL_Renderer* des, Enemy* object)
{
    for (int i = 0; i < 12; i++) {
        Bullet* p_bullet = new Bullet();

        p_bullet->loadImg("img//dantim.png", des);
        p_bullet->SetWidthHeight(WIDTH_LAZER, HEIGHT_LAZER);
        p_bullet->set_is_move(true);
        p_bullet->set_angle(30 * i);
        p_bullet->Set_y_val(1);
        p_bullet->Set_x_val(1);
        p_bullet->set_pos(object->rect_.x + object->rect_.w / 2 + BOSS_WIDTH / 2 - 50, object->rect_.y + object->rect_.h / 2 - BOSS_HEIGHT / 4 + 25);
        p_bullet_list.push_back(p_bullet);
    }

}

void Enemy::InitBulletTestRight(Bullet* p_bullet, const int& speed, SDL_Renderer* des, Enemy* object)
{
    for (int j = 0; j < 24; j++)
    {
        Bullet* p_bullet = new Bullet();
        p_bullet->set_is_move(true);
        p_bullet->loadImg("img//danvang.png", des);
        p_bullet->set_angle(15 * j);
        p_bullet->Set_y_val(speed);
        p_bullet->Set_x_val(speed);
        p_bullet->set_pos(object->rect_.x + object->rect_.w / 2 + BOSS_WIDTH / 2 - 50, object->rect_.y + object->rect_.h / 2 + 10);
        p_bullet_list.push_back(p_bullet);

    }
}

void Enemy::MakeBulletMid(SDL_Renderer* des, Enemy* object)
{
    for (int i = 0; i < p_bullet_list.size(); i++)
    {
        Bullet* p_bullet = p_bullet_list.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMoveBoss(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des, NULL, this->rect_.x, this->rect_.y);
                //p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->set_pos(object->rect_.x + object->rect_.w / 2, object->rect_.y + object->rect_.h / 2 + 200);
            }
        }
    }
}

// Đạn của quái
void Enemy::InitBullet(Bullet* p_bullet, const int& speed, SDL_Renderer* des)
{
    if (p_bullet)
    {
        bool ret = p_bullet->loadImg("img//danxanhla.png", des);
        if (ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->SetWidthHeight(WIDTH_LAZER, HEIGHT_LAZER);
            p_bullet->SetRect(this->rect_.x + WIDTH_ENEMY / 2, this->rect_.y - HEIGHT_ENEMY / 2);
            p_bullet->Set_y_val(speed);
            p_bullet_list.push_back(p_bullet);
        }
    }
}

// Load đạn lên screen
void Enemy::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i < p_bullet_list.size(); i++)
    {
        Bullet* p_bullet = p_bullet_list.at(i);
        if (p_bullet)
        {
            if (p_bullet->get_is_move())
            {
                p_bullet->Render(des, NULL, rect_.x, rect_.y);
                p_bullet->HandleMoveOfThreat();
            }
            else

                // p_bullet->Render(des, NULL, rect_.x, rect_.y);
     //            p_bullet->HandleMoveOfThreat();

       //          if (!v->get_is_move())
            {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(rect_.x + rect_.h / 3, rect_.y + rect_.h);
            }
        }
    }
}

void Enemy::HandleInputAction(SDL_Event events)
{

}

// Di chuyển của quái
void Enemy::HandleMove(const int& x_border, const int& y_border)
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


void Enemy::HandleMoveRtoL(const int& x_border, const int& y_border)
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

void Enemy::HandleMoveLtoR(const int& x_border, const int& y_border)
{
    rect_.x += 1;
    //rect_.y -= 1;
    if (rect_.x > SCREEN_WIDTH)
    {
        rect_.x = -100;
        int rand_y = rand() % 1100;
        if (rand_y > SCREEN_HEIGHT / 2)
        {
            rand_y = SCREEN_HEIGHT * 0.3;
        }
        rect_.y = rand_y;
    }
}

// Reset quái sau khi chết
void Enemy::Reset(const int& xborder)
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
    if (rand_y > SCREEN_HEIGHT * 2 / 5)
    {
        rand_y *= 0.3;
    }
    rect_.y = rand_y;
    for (int i = 0; i < p_bullet_list.size(); i++)
    {
        Bullet* p_bullet = p_bullet_list.at(i);
        if (!p_bullet->get_is_move())
        {
            ResetBullet(p_bullet);
        }
    }

}

//void ThreatsObject::ResetMeteor(const int&)

void Enemy::ResetBullet(Bullet* p_bullet)
{
    p_bullet->SetRect(rect_.x + rect_.h, rect_.y + rect_.h);
}

void Enemy::HandleMoveBoss(const int& x_border, const int& y_border)
{
    //rect_.x = SCREEN_WIDTH / 2 - BOSS_WIDTH / 2;
    /*if (rect_.x > SCREEN_WIDTH / 2)
    {
        rect_.x -= 1;
        rect_.x = -100;
    }*/
    if (rect_.y < 10)
    {
        rect_.y++;
    }
    else
    {
        if (get_dir() == true)
        {
            rect_.x += 1;
            if (rect_.x > 200)
            {
                rect_.x -= 1;
                set_direction(false);
            }
        }

        if (get_dir() == false)
        {
            rect_.x -= 1;
            if (rect_.x < 0)
            {
                rect_.x += 1;
                set_direction(true);
            }
        }
    }
    /*rect_.x++;
    if (rect_.x = 800) {
        rect_.x -= 1;
    }
    else if (rect_.x = 100) {
        rect_.x += 1;
    }
    */
}

void Enemy::HandleMoveMeteor(const int& x_border, const int& y_border)
{
    rect_.y += 2;
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

void Enemy::Reset1() {
    direction = false;
    p_bullet_list.erase(p_bullet_list.begin(), p_bullet_list.begin() + p_bullet_list.size());
}