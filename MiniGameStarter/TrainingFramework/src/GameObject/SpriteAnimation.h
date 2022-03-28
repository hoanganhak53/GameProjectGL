#pragma once
#include "BaseObject.h"
#include "Sprite2D.h"
class SpriteAnimation : public BaseObject
{
protected:
	GLint			m_iHeight;
	GLint			m_iWidth;
	GLint			m_dir;
	GLint			m_numFrames;
	GLint			m_currentFrame;
	GLfloat			m_frameTime;
	GLfloat			m_currentTime;
	GLint			m_numActions;
	GLint			m_currentAction;//index from 0 to m_numActions-1
	bool			m_isJump;
	GLint			m_vt;
public:
	SpriteAnimation(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~SpriteAnimation();

	void		Init() override;
	void		Draw();
	void		Update(GLfloat deltatime) override;

	void		Set2DPosition(GLint x, GLint y);
	void		SetRotation(Vector3 rotation);

	Vector3		Get2DPosition();
	GLint		GetDirect();
	void		SetDirect(GLint direct);
	void		SetSize(GLint width, GLint height);
	Vector2		getSize();

	bool		CheckBound(std::shared_ptr<Sprite2D>  obj);//kiem tra va cham giua nhan vat va object
	bool		CheckBound(std::shared_ptr<SpriteAnimation>  obj);


	bool		getJump();
	void		setJump(bool tt);
	GLint		getVt();
	void		setVt(GLint vt);
};