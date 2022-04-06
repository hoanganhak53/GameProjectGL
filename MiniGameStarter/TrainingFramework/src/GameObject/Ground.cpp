#include "Ground.h"
#include "ResourceManagers.h"

Ground::Ground(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int id) : Sprite2D(model, shader, texture)
{
	m_id = id;
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
	else if (m_id == 4)
	{
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("Ground4.tga");
	}
}
