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

void Enemies::UpdateAnimation(int id)
{	
	if(id == 1)
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("E_chicken.tga");
	else
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("E_blueBird.tga");

}
void Enemies::Move(float deltaTime)
{
	if (m_direct == 1)
	{
		Set2DPosition(m_position.x + deltaTime * 200, m_position.y);
		SetRotation(Vector3(0.0f, PI, 0.0f));
		if (m_position.x >= m_start.x + MOVE_LENGTH)
			m_direct = -1;
	}
	else
	{
		Set2DPosition(m_position.x - deltaTime * 200, m_position.y);
		SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		if (m_position.x <= m_start.x - MOVE_LENGTH)
			m_direct = 1;
	}
}
void Enemies::Attack(std::shared_ptr<Player> obj)
{
	if (CheckBound(obj) && obj->getActive())
	{
		if(m_position.y - m_iHeight / 2 >= obj->Get2DPosition().y + obj->getSize().y / 2 - 5)
		{
			setActive(false);
		}
		else
		{
			if (obj->GetHp() > 1)
			{
				obj->Set2DPosition(obj->GetCheckPoint().x, obj->GetCheckPoint().y);
			}
			obj->SetHp(obj->GetHp() - 1);
		}
	}
}

void Enemies::SetPositionStart(Vector2 v)
{
	m_start.x = v.x;
	m_start.y = v.y;
}

//plant

Plant::Plant(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime): Enemies(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	auto b_texture = ResourceManagers::GetInstance()->GetTexture("E_bullet.tga");
	m_bullet = std::make_shared<Bullet>(model, shader, b_texture, 1, 1, 0, 0.1f);
	m_bullet->SetSize(32, 32);
}

Plant::~Plant()
{
}

void Plant::UpdateAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("E_plant.tga");
}

void Plant::UpdateBullet(float deltaTime, std::shared_ptr<Player> player)
{
	m_bullet->Attack(player);
	m_bullet->Move(deltaTime);
	m_bullet->Update(deltaTime);
}

void Plant::DrawBullet()
{
	m_bullet->Draw();
}


//bullet
Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :Enemies(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
}

Bullet::~Bullet()
{
}

void Bullet::Move(float deltaTime)
{
	Set2DPosition(m_position.x - deltaTime * 100, m_position.y);
	if (m_position.x <= m_start.x - MOVE_LENGTH)
		Set2DPosition(m_start.x, m_start.y);
}

void Bullet::Attack(std::shared_ptr<Player> obj)
{

	if (CheckBound(obj) && obj->getActive())
	{
		if (obj->GetHp() > 1)
		{
			obj->Set2DPosition(obj->GetCheckPoint().x, obj->GetCheckPoint().y);
		}
		obj->SetHp(obj->GetHp() - 1);
	}
}
