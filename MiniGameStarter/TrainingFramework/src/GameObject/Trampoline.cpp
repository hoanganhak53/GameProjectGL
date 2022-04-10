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
		if (Globals::haveSound)
			ResourceManagers::GetInstance()->PlaySound("Jump.wav");
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
		if (Globals::haveSound)
			ResourceManagers::GetInstance()->PlaySound("Collect.wav");
		return true;
	}
	return false;
}


//spike

Spike::Spike(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
}

Spike::~Spike()
{
}

bool Spike::CheckBound(std::shared_ptr<SpriteAnimation> obj)
{
	int a_x1 = m_position.x - m_iWidth / 2, a_x2 = m_position.x + m_iWidth / 2;
	int a_y1 = m_position.y - m_iHeight / 2 + 20, a_y2 = m_position.y + m_iHeight / 2;
	int b_x1 = obj->Get2DPosition().x - obj->getSize().x / 2 + 10, b_x2 = obj->Get2DPosition().x + obj->getSize().x / 2 - 10;
	int b_y1 = obj->Get2DPosition().y - obj->getSize().y / 2, b_y2 = obj->Get2DPosition().y + obj->getSize().y / 2;
	if (a_x1 < b_x2 && b_x1 < a_x2 && a_y1 < b_y2 && b_y1 < a_y2)
		return true;
	return false;
}

void Spike::UpdateAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("E_spike.tga");
}

void Spike::Attack(std::shared_ptr<Player>  obj)
{
	if (CheckBound(obj) && obj->getActive())
	{
		obj->SetHp(obj->GetHp() - 1);
		if(obj->Get2DPosition().x <= m_position.x)
			obj->Set2DPosition(m_position.x - m_iWidth - 50, obj->Get2DPosition().y);
		else
			obj->Set2DPosition(m_position.x + m_iHeight + 50, obj->Get2DPosition().y);

		obj->setActive(false);
	}
}



Heart::Heart(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
}

Heart::~Heart()
{
}

void Heart::UpdateAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("I_heart.tga");
}

bool Heart::BuffHP(std::shared_ptr<Player> obj)
{
	if (!m_isActive)
		return false;
	if (CheckBound(obj))
	{
		if(obj->GetHp() > 0)
			obj->SetHp(obj->GetHp() + 1);
		if (Globals::haveSound)
			ResourceManagers::GetInstance()->PlaySound("Collect.wav");
		return true;
	}
	return false;
}

Cup::Cup(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
}

Cup::~Cup()
{
}

void Cup::UpdateAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("cup.tga");
}

bool Cup::Win(std::shared_ptr<Player> obj)
{
	if (CheckBound(obj))
	{
		return true;
	}
	return false;
}
