#include "Trampoline.h"
#include "ResourceManagers.h"
#include "Texture.h"

Trampoline::Trampoline(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	/*m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;
	m_numFrames = numFrames;
	m_numActions = numActions;
	m_frameTime = frameTime;
	m_currentFrame = 0;
	m_currentAction = 0;
	m_currentTime = 0.0f;
	m_currentAction = currentAction;

	m_position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_scale = Vector3((float)m_iWidth / Globals::screenWidth, (float)m_iHeight / Globals::screenHeight, 1);*/
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
void Trampoline::Jumping(std::shared_ptr<SpriteAnimation>  obj)
{
	if (Trampoline::CheckBound(obj)) 
	{
		obj->setVt(30);
	}
}