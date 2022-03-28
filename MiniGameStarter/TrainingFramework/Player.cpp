#include "Player.h"
#include "Texture.h"
#include "ResourceManagers.h"


Player::Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	//SpriteAnimation::SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime);
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
	m_idCharacter = 1;
	m_score = 0;
}

Player::~Player() {

}

void Player::setIdCharacter(GLint id)
{
	m_idCharacter = id;
}

void Player::UpdateAnimation()
{
	if (m_idCharacter == 1)
	{
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("char1_Run.tga");
	}
	else if (m_idCharacter == 2)
	{
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("char2_Run.tga");
	}
	else if (m_idCharacter == 3)
	{
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("char3_Run.tga");
	}
	else if (m_idCharacter == 4)
	{
		m_pTexture = ResourceManagers::GetInstance()->GetTexture("char4_Run.tga");
	}
}

GLint Player::GetScore()
{
	return m_score;
}

void Player::SetScore(GLint s)
{
	m_score = s;
}

