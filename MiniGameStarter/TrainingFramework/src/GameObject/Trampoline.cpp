#include "Trampoline.h"
#include "Texture.h"
#include "ResourceManagers.h"

Trampoline::Trampoline(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_isJump = false;
	m_velocity = 0;
}

Trampoline::~Trampoline()
{
}
void Trampoline::UpdateAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("trampoline.tga");
}

void Trampoline::Jumping(std::shared_ptr<Player>  obj)
{
	if (Trampoline::CheckBound(obj))
	{
		obj->setV(30);
		obj->setJump(true);
	}
}
//coin
Coin::Coin(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_isJump = false;
	m_velocity = 0;
}

Coin::~Coin()
{
}
void Coin::UpdateAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("I_coin.tga");
}
bool Coin::Collecting(std::shared_ptr<Player>  obj) {
	if (!m_isActive)
		return false;
	if (Coin::CheckBound(obj))
	{
		obj->SetScore(obj->GetScore()+1);
		return true;
	}
	return false;
}