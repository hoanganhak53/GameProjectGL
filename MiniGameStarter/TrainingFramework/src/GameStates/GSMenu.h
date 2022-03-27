#pragma once
#include "GameStateBase.h"
#include "GameButton.h"
#include "SpriteAnimation.h"
#include "Player.h"


class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

	void	setAudio(bool audio);
	bool	getAudio();
private:
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameName;
	std::shared_ptr<Player>					m_player;
	GLint									m_numChar;
	bool									m_audioOn = true;
};

