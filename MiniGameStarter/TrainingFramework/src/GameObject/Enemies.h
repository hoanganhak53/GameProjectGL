#pragma once
#include "SpriteAnimation.h"
#include "Player.h"

#define MOVE_LENGTH 300

class Enemies :
    public SpriteAnimation
{
public:
    Enemies(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Enemies();
    void	    Update(GLfloat deltatime);

    void        UpdateAnimation(int id);
    void        Move(float deltaTime);
    void        Attack(std::shared_ptr<Player>  obj);
    void        SetPositionStart(Vector2 v);
    Vector2     GetPositionStart();
    int         m_direct;
    Vector2     m_start;
    int         m_id;
private:
};

class Bullet;

class Plant :
    public Enemies
{
public:
    Plant(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Plant();
    void        UpdateAnimation();
    void        UpdateBullet(float deltaTime, std::shared_ptr<Player> player);
    void        DrawBullet();
    std::shared_ptr<Bullet>	m_bullet;

};


class Bullet :
    public Enemies
{
public:
    Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Bullet();

    void        Move(float deltaTime);
    void        Attack(std::shared_ptr<Player>  obj);

};

class Ghost :
    public Enemies
{
public:
    Ghost(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Ghost();

    void        Attack(std::shared_ptr<Player>  obj);
    void        UpdateAnimation();
    void        Move(std::shared_ptr<Player> player, float deltaTime);
    GLint       m_dir;
};

