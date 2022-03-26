#pragma once
#include "SpriteAnimation.h"
class Enemies :
    public SpriteAnimation
{
    Enemies(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
    ~Enemies();
};

