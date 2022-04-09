#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "BaseObject.h"
#include "Common_Function.h"


const int WIDTH_LAZER = 20;
const int HEIGHT_LAZER = 24;


class AmoObject : public BaseObject
{
public:
    AmoObject();
    ~AmoObject();
  
    void HandleMove(const int& x_border, const int& y_border);

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
    int x_val_;
    int y_val_;
    bool is_move_;
};
#endif // AMO_OBJECT_H_