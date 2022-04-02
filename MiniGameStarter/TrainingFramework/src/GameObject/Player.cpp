#include "Player.h"
#include "Texture.h"
#include "ResourceManagers.h"


Player::Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime)
{
	m_isJump = false;
	m_velocity = 0;
	m_idCharacter = 1;
	m_score = 0;
	m_hp = 3;
}

Player::~Player() {

}

void Player::setIdCharacter(GLint id)
{
	m_idCharacter = id;
}

void Player::UpdateAnimation()
{
	if (m_isJump) {
		SetNumFrame(6);
		if (m_idCharacter == 1)
		{
			m_pTexture = ResourceManagers::GetInstance()->GetTexture("char1_Jump.tga");
		}
		else if (m_idCharacter == 2)
		{
			m_pTexture = ResourceManagers::GetInstance()->GetTexture("char2_Jump.tga");
		}
		else if (m_idCharacter == 3)
		{
			m_pTexture = ResourceManagers::GetInstance()->GetTexture("char3_Jump.tga");
		}
		else if (m_idCharacter == 4)
		{
			m_pTexture = ResourceManagers::GetInstance()->GetTexture("char4_Jump.tga");
		}
	}
	else {
		SetNumFrame(12);
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
}

GLint Player::GetScore()
{
	return m_score;
}

void Player::SetScore(GLint s)
{
	m_score = s;
}

void Player::SetNumFrame(int num)
{
	m_numFrames = num;
}

void Player::SetHp(int hp)
{
	m_hp = hp;
}

GLint Player::GetHp()
{
	return m_hp;
}

Vector2 Player::GetCheckPoint()
{
	return m_checkPoint;
}

void Player::SetCheckPoint(int x, int y)
{
	m_checkPoint.x = x;
	m_checkPoint.y = y;
}

void Player::Move(float deltaTime, int pressKey)
{
	switch (pressKey)
	{
	case 1: //sang trai
	{
		if (m_isJump)
			SetRotation(Vector3(0.0f, 0.0, 0.0f));
		else
			SetRotation(Vector3(0.0f, PI, 0.0f));
		Set2DPosition(m_position.x - deltaTime * 200, m_position.y);
		break;
	}
	case 1 << 1: //sang phai
	{
		if (m_isJump)
			SetRotation(Vector3(0.0f, PI, 0.0f));
		else
			SetRotation(Vector3(0.0f, 0.0, 0.0f));
		Set2DPosition(m_position.x + deltaTime * 200, m_position.y);
		break;
	}
	case 1 << 2: // nhay
	{
		if (!m_isJump)
		{
			setJump(true);
			setV(20);
		}
		break;
	}
	case 1 << 2 | 1: // nhay va sang trai
	{
		UpdateAnimation();
		SetRotation(Vector3(0.0f, 0.0f, 0.0f));

		Set2DPosition(m_position.x - deltaTime * 200, m_position.y);
		if (!m_isJump)
		{
			setJump(true);
			setV(20);
		}
		break;
	}
	case 1 << 2 | 1 << 1: // nhau va sang phai
	{
		UpdateAnimation();
		SetRotation(Vector3(0.0f, PI, 0.0f));
		Set2DPosition(m_position.x + deltaTime * 200, m_position.y);
		if (!m_isJump) // dang khong nhay moi duoc nhay
		{
			setJump(true);
			setV(20);
		}
		break;
	}
	default:
		break;
	}
}

