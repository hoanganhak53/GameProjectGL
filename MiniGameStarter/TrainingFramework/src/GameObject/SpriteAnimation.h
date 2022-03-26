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
	bool			m_isJump;
	GLint			m_vt;
public:
	SpriteAnimation(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime);
	~SpriteAnimation();

	SpriteAnimation()
		: m_Vec2DPos(2,1),m_iHeight(0),m_iWidth(0),m_dir(1), m_numFrames(0), m_currentFrame(0), m_frameTime(0), m_currentTime(0), m_numActions(0)
	, m_currentAction(0), m_isJump(false), m_vt(0){}

	void		Init() override;
	void		Draw();
	void		Update(GLfloat deltatime) override;

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);

	Vector2		Get2DPosition();
	GLint		GetDirect();
	void		SetDirect(GLint vh);
	void		SetSize(GLint width, GLint height);

	bool		CheckBound(std::shared_ptr<Sprite2D>  obj);//kiem tra va cham giua nhan vat va object

	bool		getJump();
	void		setJump(bool tt);
	GLint		getVt();
	void		setVt(GLint vt);
};

