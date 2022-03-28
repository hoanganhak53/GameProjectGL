#include "Player.h"
#include "Texture.h"
#include "ResourceManagers.h"


Player::Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
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

