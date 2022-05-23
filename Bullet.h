#ifndef BULLET_H_
#define BULLET_H_
#include "BaseObject.h"
#include "Common_Function.h"


const int WIDTH_LAZER = 20;
const int HEIGHT_LAZER = 24;


class Bullet : public BaseObject
{
public:
    Bullet();
    ~Bullet();
    bool LoadTexture(std::string path, SDL_Renderer* screen);
    void set_type_amo(const double type_) { type = type_; }
    int get_type_amo() const { return type; }
    void SetType(SDL_Renderer* des);
    void HandleMoveTest(const int& x_border, const int& y_border);
    void HandleMoveMain(const int& x_border, const int& y_border);
    void HandleMoveBoss(const int& x_border, const int& y_border);
    void HandleMoveOfThreat();

    bool get_is_move() const
    {
        return is_move_;
    }
    void set_is_move(bool is_move)
    {
        is_move_ = is_move;
    }
    void Set_x_val(const int& val)
    {
        x_val_ = val;
    }
    void Set_y_val(const int& val)
    {
        y_val_ = val;
    }

    void set_angle(const double& angle_) { angle = angle_; }
    void set_starting_point(const double& start) { starting_point = start; }

    void set_pos(const double& xPos, const double& yPos)
    {
        x_pos = xPos;
        y_pos = yPos;
    }

    int Get_x_val() const
    {
        return x_val_;
    }
    int Get_y_val() const
    {
        return y_val_;
    }
    void SetWidthHeight(const int& width, const int& height)
    {
        rect_.w = width;
        rect_.h = height;
    }
private:
    double x_pos;
    double y_pos;

    int x_val_;
    int y_val_;

    double angle;
    double starting_point;

    int type;

    bool is_move_;
};
#endif // AMO_OBJECT_H_