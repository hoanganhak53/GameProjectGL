#pragma once
#include "SpriteAnimation.h"
#include "Player.h"

#define MOVE_LENGTH 250

class Enemies :
    public SpriteAnimation
{
public:
    Enemies(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Enemies();

    void UpdateAnimation();
    void Move(float deltaTime);
    void Attack(std::shared_ptr<Player>  obj);
    void SetPositionStart(Vector2 v);
    int m_direct;
    Vector2 m_start;

private:
};

class Bullet;

class Plant :
    public Enemies
{
public:
    Plant(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Plant();
    void UpdateAnimation();
    void UpdateBullet(float deltaTime, std::shared_ptr<Player> player);
    void DrawBullet();
    std::shared_ptr<Bullet>	m_bullet;

};


class Bullet :
    public Enemies
{
public:
    Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Bullet();

    void Move(float deltaTime);
    void Attack(std::shared_ptr<Player>  obj);

};

