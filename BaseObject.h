#ifndef BASEOBJECT_H
#define BASEOBJECT_H



#include "Common_Function.h"

class BaseObject //Lớp cơ sở
{
public:
    BaseObject(); //Constructer
    ~BaseObject(); //Hàm hủy
    void SetRect(const int& x, const int& y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect GetRect() const
    {
        return rect_;
    }
    SDL_Texture* GetObject()
    {
        return p_object_;
    }

    bool loadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip , int x, int y);
    void Render1(SDL_Renderer* des, const SDL_Rect* clip, int x, int y);
    void Free();
protected:
    SDL_Rect rect_;
    SDL_Texture* p_object_; //Surface nguồn
};

#endif