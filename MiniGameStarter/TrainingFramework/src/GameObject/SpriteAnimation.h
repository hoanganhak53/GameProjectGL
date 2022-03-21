#pragma once
#include "BaseObject.h"
#include "Sprite2D.h"
class SpriteAnimation : public BaseObject
{
private:
	std::string		m_Text;
	void			CaculateWorldMatrix();
protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
	GLint			m_dir;
	GLint			m_numFrames;
	GLint			m_currentFrame;
	GLfloat			m_frameTime;
	GLfloat			m_currentTime;
	GLint			m_numActions;
	GLint			m_currentAction;//index from 0 to m_numActions-1
	bool			isJump;
	bool			isContinueCrash;
	GLint			m_vt;
public:
	SpriteAnimation(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~SpriteAnimation();

	void		Init() override;
	void		Draw() final;
	void		Update(GLfloat deltatime) override;

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);

	Vector2		Get2DPosition();
	GLint		GetDirect();
	void		SetDirect(GLint vh);
	void		SetSize(GLint width, GLint height);

	bool		CheckBound(std::shared_ptr<Sprite2D>  obj);

	bool		getJump();
	void		setJump(bool tt);
	GLint		getVt();
	void		setVt(GLint vt);
	bool		getContinueCrash();
	void		setContinueCrash(bool tt);
};

