#pragma once
#include "SpriteAnimation.h"
#include "BaseObject.h"

class Player :
	public SpriteAnimation
{
public:
	Player(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~Player();
	void	setIdCharacter(GLint id);
	void	UpdateAnimation();
	GLint	GetScore();
	void	SetScore(GLint s);
	void	SetNumFrame(int num);
	void	SetHp(int hp);
	GLint	GetHp();
	void	Move(float deltaTime, int pressKey);
	void	Update(GLfloat deltatime);


protected:
	GLint	m_idCharacter;
	GLint	m_score;
	GLint	m_hp;
};