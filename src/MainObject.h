#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "Common_Function.h"
#include "BaseObject.h"
#include "Bullet.h"

class MainObject : public BaseObject
{
public:
    static const int  DOT_WIDTH = 85;
    static const int DOT_HEIGHT = 51;

    static const int DOT_VEL = 2;

    MainObject(int x, int y);
    bool loadImg(std::string path, SDL_Renderer* screen);
    void HandleInputAction(SDL_Event events,SDL_Renderer* des, Mix_Chunk* fire_sound[2]);
    void HandleMove();
    void Render(SDL_Renderer* des, SDL_Rect* clip);
    // Đạn của nhân vật lưu trong vector
    
    void SetBulletList(std::vector<Bullet*> bullet_list)
    {
        p_bullet_list = bullet_list;
    }
    std::vector<Bullet*> GetBulletList() const
    {
        return p_bullet_list;
    }
    void SetBulletType(int type);

    bool cheatsw();
    int fetchScore();
    void incScore();

    void MakeBullet(SDL_Renderer* des);
    void DestroyBullet(const int& idx);
    void reset_main_pos(int x, int y);
    void Reset(int x, int y);
private:
    std::vector<Bullet*> p_bullet_list;
    //The X and Y offsets of the dot
    int x_pos_, y_pos_;

    //The velocity of the dot
    int x_val_, y_val_;

    //Player's score
    int score = 0;
    
    int ammo_type = 0;
    bool cheat_sw = false;
};


#endif // ! MAIN_OBJECT_H_
