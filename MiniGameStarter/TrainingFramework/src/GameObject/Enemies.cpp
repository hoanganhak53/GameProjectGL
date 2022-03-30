#include "Enemies.h"


Enemies::Enemies(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime):SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_isJump = false;
	m_velocity = 0;
}

Enemies::~Enemies() {

}