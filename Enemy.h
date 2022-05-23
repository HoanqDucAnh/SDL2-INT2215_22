#pragma once
#ifndef ENEMY_H_
#define ENEMY_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "Bullet.h"
#include <vector>

#define WIDTH_ENEMY 72
#define HEIGHT_ENEMY 62

class Enemy : public BaseObject
{
public:
   Enemy();
    ~Enemy();

    void HandleMoveLtoR(const int& x_border, const int& y_border);
    void HandleMoveRtoL(const int& x_border, const int& y_border);
    void HandleInputAction(SDL_Event events);
    void HandleMove(const int& x_border, const int& y_border);
    void HandleMoveBoss(const int& x_border, const int& y_border);
    void HandleMoveMeteor(const int& x_border, const int& y_border);
    void InitBullet4(SDL_Renderer* des, Enemy* object);
    void InitBulletTestRight(Bullet* p_bullet, const int& speed, SDL_Renderer* des, Enemy* object);
    void InitBulletTestMid(Bullet* p_bullet, const int& speed, SDL_Renderer* des, Enemy* object);
    void MakeBulletMid(SDL_Renderer* des, Enemy* object);
    void set_x_val(const int& val)
    {
        x_val_ = val;
    }
    void set_y_val(const int& val)
    {
        y_val_ = val;
    }
    int get_x_val() const
    {
        return x_val_;
    }
    int get_y_val() const
    {
        return y_val_;
    }

    bool get_dir() const
    {
        return direction;
    }

    void set_direction(const bool& direct)
    {
        direction = direct;
    }


    void InitBullet(Bullet* p_bullet, const int& speed, SDL_Renderer* des);
    void SetBulletList(std::vector<Bullet*>& p_bullet_list)
    {
        p_bullet_list = p_bullet_list;
    }
    std::vector<Bullet*> GetBulletList() const
    {
        return p_bullet_list;
    }
    void set_type_threat(const double type_) { type = type_; }
    int get_type_threat() const { return type; }
    void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);
    void Reset(const int& yborder);
    void ResetBullet(Bullet* p_bullet);
    void Reset1();
private:
    int x_val_;
    int y_val_;
    bool direction;

    int type;

    std::vector<Bullet*> p_bullet_list;
};

#endif // THREATS_OBJECT_H_