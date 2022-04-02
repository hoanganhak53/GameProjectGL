#include "Enemies.h"
#include "ResourceManagers.h"

Enemies::Enemies(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime):SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_isJump = false;
	m_velocity = 0;
	m_start = Vector2(0, 0);
	m_direct = 1;
}

Enemies::~Enemies() 
{
}

void Enemies::UpdateAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("E_slime.tga");
}
void Enemies::Move(float deltaTime)
{
	if (m_direct == 1)
	{
		Set2DPosition(m_position.x + deltaTime * 100, m_position.y);
		SetRotation(Vector3(0.0f, PI, 0.0f));
		if (m_position.x >= m_start.x + MOVE_LENGTH)
			m_direct = -1;
	}
	else
	{
		Set2DPosition(m_position.x - deltaTime * 100, m_position.y);
		SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		if (m_position.x <= m_start.x - MOVE_LENGTH)
			m_direct = 1;
	}
}
void Enemies::Attack(std::shared_ptr<Player> obj)
{
	if (CheckBound(obj))
	{
		if(m_position.y - m_iHeight / 2 >= obj->Get2DPosition().y + obj->getSize().y / 2 - 5)
		{
			setActive(false);
		}
		else
		{
			if(obj->GetHp() >= 1)
			obj->SetHp(obj->GetHp() - 1);
			obj->Set2DPosition(obj->GetCheckPoint().x, obj->GetCheckPoint().y);
		}
	}
}

void Enemies::SetPositionStart(Vector2 v)
{
	m_start.x = v.x;
	m_start.y = v.y;
}
