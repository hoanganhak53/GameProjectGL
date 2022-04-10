#include "Enemies.h"
#include "ResourceManagers.h"

Enemies::Enemies(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime):SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_isJump = false;
	m_velocity = 0;
	m_start = Vector2(0, 0);
	m_direct = 1;
	m_id = 1;
}

Enemies::~Enemies() 
{
}

void Enemies::Update(GLfloat deltatime)
{
	m_currentTime += deltatime;
	if (m_currentTime >= m_frameTime)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_numFrames)
			m_currentFrame = 0;
		m_currentTime -= m_frameTime;
	}
	Set2DPosition(Get2DPosition().x - Globals::moveCam, Get2DPosition().y);
	SetPositionStart(Vector2(GetPositionStart().x - Globals::moveCam, GetPositionStart().y));
}

void Enemies::UpdateAnimation(int id)
{	
	m_id = id;
	if(id == 1)
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("E_chicken.tga");
	else if(id == 2)
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("E_blueBird.tga");
	else
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("E_bunny.tga");

}

void Enemies::Move(float deltaTime)
{
	if (m_direct == 1)
	{
		Set2DPosition(m_position.x + deltaTime * 200, m_position.y);
		SetRotation(Vector3(0.0f, PI, 0.0f));
		if (Get2DPosition().x >= GetPositionStart().x + MOVE_LENGTH)
			m_direct = -1;
	}
	else
	{
		Set2DPosition(m_position.x - deltaTime * 200, m_position.y);
		SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		if (Get2DPosition().x <= GetPositionStart().x - MOVE_LENGTH)
			m_direct = 1;
	}
	if (m_id == 3)
	{	
		if(m_position.y >= m_start.y - 1)
			setV(30);
	Set2DPosition(Get2DPosition().x, Get2DPosition().y - getV() * deltaTime * 70);
	setV(getV() - deltaTime * 90);
	}
}

void Enemies::Attack(std::shared_ptr<Player> obj)
{
	if (CheckBound(obj) && obj->getActive())
	{
		if(m_position.y - m_iHeight / 2 >= obj->Get2DPosition().y + obj->getSize().y / 2 - 10)
		{
			obj->setV(15);
			setActive(false);
		}
		else
		{
			obj->SetHp(obj->GetHp() - 1);
			obj->Set2DPosition(obj->Get2DPosition().x - 50, obj->Get2DPosition().y);
			obj->setActive(false);
		}
	}
}

void Enemies::SetPositionStart(Vector2 v)
{
	m_start.x = v.x;
	m_start.y = v.y;
}

Vector2 Enemies::GetPositionStart()
{
	return m_start;
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
	Set2DPosition(m_position.x - deltaTime * 200, m_position.y);
	if (m_position.x <= m_start.x - MOVE_LENGTH * 2)
		Set2DPosition(m_start.x, m_start.y);
}

void Bullet::Attack(std::shared_ptr<Player> obj)
{
	if (CheckBound(obj) && obj->getActive())
	{
		obj->SetHp(obj->GetHp() - 1);
		obj->Set2DPosition(obj->Get2DPosition().x - 50, obj->Get2DPosition().y);
		obj->setActive(false);
	}
}

Ghost::Ghost(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :Enemies(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_dir = -1;
}

Ghost::~Ghost()
{
}

void Ghost::Attack(std::shared_ptr<Player> obj)
{
	if (CheckBound(obj) && obj->getActive())
	{
		if (m_position.y - m_iHeight / 2 >= obj->Get2DPosition().y + obj->getSize().y / 2 - 10)
		{
			obj->setV(15);
			setActive(false);
		}
		else
		{
			obj->SetHp(obj->GetHp() - 1);
			obj->Set2DPosition(obj->Get2DPosition().x - 50, obj->Get2DPosition().y);
			obj->setActive(false);
			setActive(false);
		}
	}
}

void Ghost::UpdateAnimation()
{
	m_pTexture = ResourceManagers::GetInstance()->GetTexture("E_ghost.tga");
}

void Ghost::Move(std::shared_ptr<Player> player, float deltaTime)
{
	if (m_dir != player->GetDirect() && std::abs(player->Get2DPosition().x - m_position.x) < 700)
	{
		if (m_position.x > player->Get2DPosition().x)
		{
			SetRotation(Vector3(0.0f, 0.0, 0.0f));
			Set2DPosition(m_position.x - 200 * deltaTime, m_position.y);
		}
		else
		{
			SetRotation(Vector3(0.0f, PI, 0.0f));
			Set2DPosition(m_position.x + 200 * deltaTime, m_position.y);
		}
		if (m_position.y > player->Get2DPosition().y)
		{
			Set2DPosition(m_position.x , m_position.y- 100 * deltaTime);
		}
		else
		{
			Set2DPosition(m_position.x, m_position.y + 100 * deltaTime);
		}
	}
}
