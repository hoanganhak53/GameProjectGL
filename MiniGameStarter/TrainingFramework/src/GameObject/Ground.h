#pragma once
#include "SpriteAnimation.h"
#include "Player.h"

class Ground :
    public SpriteAnimation
{
public:
    Ground(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, int id);
    ~Ground();
    
    void    UpdateAnimation(); 
    void    Falling(float deltaTime, std::shared_ptr<Player> player);
    int     m_id;
    float   m_Time;
    bool    m_fall;
};