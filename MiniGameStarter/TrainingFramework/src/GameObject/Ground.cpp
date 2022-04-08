#include "Ground.h"
#include "ResourceManagers.h"

Ground::Ground(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime, int id) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_id = id;
	m_Time = 0;
	m_fall = false;
}

Ground::~Ground()
{
}

void Ground::UpdateAnimation()
{
	if (m_id == 1)
	{
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("Ground1.tga");
	}
	else if (m_id == 2)
	{
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("Ground2.tga");
	}
	else if (m_id == 3)
	{
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("Ground3.tga");
	}
}

void Ground::Falling(float deltaTime, std::shared_ptr<Player>  player)
{
	if (CheckBound(player))
		m_fall = true;
	if(m_fall)
	{
		m_Time += deltaTime;
		if (m_Time > 1.5)
		{
			if(GetPosition().y < 1400)
				Set2DPosition(GetPosition().x, GetPosition().y + 200 * deltaTime);
		}
	}
}
