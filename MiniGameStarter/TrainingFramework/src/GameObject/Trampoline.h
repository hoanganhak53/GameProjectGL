#pragma once
#include "SpriteAnimation.h"
#include "BaseObject.h"
class Trampoline :
    public SpriteAnimation
{
public:
    Trampoline(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Trampoline();
    void UpdateAnimation();
    void Jumping(std::shared_ptr<SpriteAnimation>  obj);
};
