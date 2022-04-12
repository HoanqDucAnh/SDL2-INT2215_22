#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"

class MainObject : public BaseObject
{
public:
    static const int  DOT_WIDTH = 85;
    static const int DOT_HEIGHT = 51;

    static const int DOT_VEL = 2;

    MainObject(int x, int y);
    bool loadImg(std::string path, SDL_Renderer* screen);
    void HandleInputAction(SDL_Event events,SDL_Renderer* des);
    void HandleMove();
    void Render(SDL_Renderer* des, SDL_Rect* clip);
    // Đạn của nhân vật lưu trong vector
    
    void SetAmoList(std::vector<AmoObject*> amo_list)
    {
        p_amo_list = amo_list;
    }
    std::vector<AmoObject*> GetAmoList() const
    {
        return p_amo_list;
    }

    void MakeAmo(SDL_Renderer* des);
private:
    std::vector<AmoObject*> p_amo_list;
    //The X and Y offsets of the dot
    int x_pos_, y_pos_;

    //The velocity of the dot
    int x_val_, y_val_;
};


#endif // ! MAIN_OBJECT_H_
