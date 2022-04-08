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



class Spike :
    public SpriteAnimation
{
public:
    Spike(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Spike();
    bool		CheckBound(std::shared_ptr<SpriteAnimation>  obj);

    void UpdateAnimation();
    void Attack(std::shared_ptr<Player>  obj);
};


class Heart :
    public SpriteAnimation
{
public:
    Heart(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Heart();
    void UpdateAnimation();
    bool BuffHP(std::shared_ptr<Player>  obj);
};

class Cup :
    public SpriteAnimation
{
public:
    Cup(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Cup();
    void UpdateAnimation();
    bool Win(std::shared_ptr<Player>  obj);
};