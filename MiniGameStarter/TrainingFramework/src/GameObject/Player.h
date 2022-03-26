#pragma once
#include "SpriteAnimation.h"
#include "BaseObject.h"
class Player :
    public SpriteAnimation
{
public:
	Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~Player();

};