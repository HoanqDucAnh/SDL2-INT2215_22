#pragma once
#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_THREAT 72
#define HEIGHT_THREAT 62

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    void HandleMoveLtoR(const int& x_border, const int& y_border);
    void HandleMoveRtoL(const int& x_border, const int& y_border);
    void HandleInputAction(SDL_Event events);
    void HandleMove(const int& x_border, const int& y_border);
    void HandleMoveBoss(const int& x_border, const int& y_border);
    void HandleMoveMeteor(const int& x_border, const int& y_border);
    void InitAmo2( SDL_Renderer* des, ThreatsObject* object);
    void InitAmo3( SDL_Renderer* des, ThreatsObject* object);
    void InitAmo4( SDL_Renderer* des, ThreatsObject* object);
    void InitAmoTestLeft( SDL_Renderer* des, ThreatsObject* object);
    void InitAmoTestRight( SDL_Renderer* des, ThreatsObject* object);
    void InitAmoTestMid(AmoObject* p_amo, const int& speed, SDL_Renderer* des, ThreatsObject* object);
    void InitAmoTest1(AmoObject* p_amo, SDL_Renderer* des, ThreatsObject* object, int x);
    void InitAmoTest2( SDL_Renderer* des, ThreatsObject* object);
    void MakeAmo1(SDL_Renderer* des, ThreatsObject* boss);
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


    void InitAmo(AmoObject* p_amo, const int& speed, SDL_Renderer* des);
    void SetAmoList(std::vector<AmoObject*>& amo_list)
    {
        p_amo_list = amo_list;
    }
    std::vector<AmoObject*> GetAmoList() const
    {
        return p_amo_list;
    }
    void set_type_threat(const double type_) { type = type_; }
    int get_type_threat() const { return type; }
    bool LoadTexture(std::string path, SDL_Renderer* screen);
    void MakeAmo(SDL_Renderer* des, const int& x_limit, const int& y_limit);
    void Reset(const int& yborder);
    void ResetAmo(AmoObject* p_amo);
    void Reset1();
private:
    int x_val_;
    int y_val_;
    bool direction;

    int type;

    std::vector<AmoObject*> p_amo_list;
};

#endif // THREATS_OBJECT_H_