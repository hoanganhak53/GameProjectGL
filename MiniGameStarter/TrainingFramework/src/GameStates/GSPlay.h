#pragma once
#include "GameStateBase.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;
class Player;
class Trampoline;
class Coin;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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

	void	Restart();
    int m_Test;
	int m_PressKey;
	bool m_isPause;
private:
	std::shared_ptr<Sprite2D>	m_background;

	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Sprite2D>>	m_listObject;
	std::list<std::shared_ptr<GameButton>>	m_listButtonPause;

	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Player>	m_player;
	std::shared_ptr<Trampoline>	m_trampoline;	
	std::list<std::shared_ptr<Coin>>	m_listCoin;
};

