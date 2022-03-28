#pragma once
#include "SpriteAnimation.h"
#include "BaseObject.h"
#include "Player.h"
class Trampoline :
    public SpriteAnimation
{
public:
    Trampoline(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Trampoline();
    void UpdateAnimation();
    void Jumping(std::shared_ptr<Player>  obj);
};




class Coin :
    public SpriteAnimation
{
public:
    Coin(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Coin();
    void UpdateAnimation();
    bool Collecting(std::shared_ptr<Player>  obj);
};
