#include "Trampoline.h"
#include "Texture.h"
#include "ResourceManagers.h"

Trampoline::Trampoline(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_dir = 1;
	m_isJump = false;
	m_vt = 0;
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
		obj->setVt(30);
	}
}
//coin
Coin::Coin(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_dir = 1;
	m_isJump = false;
	m_vt = 0;
}

Coin::~Coin()
{
}
void Coin::UpdateAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("I_coin.tga");
}
bool Coin::Collecting(std::shared_ptr<Player>  obj) {
	if (Coin::CheckBound(obj))
	{
		obj->SetScore(obj->GetScore()+1);
		return true;
	}
	return false;
}