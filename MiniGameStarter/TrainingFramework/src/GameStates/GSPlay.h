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
class Enemies;
class CheckPoint;
class Plant;
class Bullet;
class Ground;
class Spike;
class Heart;
class Ghost;
class Cup;

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
	void	Attacked(float deltaTime);
	void	CreateButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	void	CreateBackground(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

	void	CreateMap(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	void	UpdateScore();

private:
	std::list<std::shared_ptr<Sprite2D>>		m_listBackground;

	std::list<std::shared_ptr<GameButton>>		m_listButton;
	std::list<std::shared_ptr<Ground>>			m_listGround;
	std::list<std::shared_ptr<GameButton>>		m_listButtonPause;
	std::list<std::shared_ptr<Sprite2D>>		m_listImage;
	std::list<std::shared_ptr<Enemies>>			m_listEnemies;
	std::list<std::shared_ptr<Plant>>			m_listPlant;
	std::list<std::shared_ptr<Ghost>>			m_listGhost;
	std::list<std::shared_ptr<Spike>>			m_listSpike;
	std::list<std::shared_ptr<Trampoline>>		m_listTrampoline;

	std::shared_ptr<Text>						m_score;
	std::shared_ptr<Text>						m_hp;
	std::shared_ptr<Cup>						m_cup;


	std::shared_ptr<Player>						m_player;
	std::list<std::shared_ptr<Coin>>			m_listCoin;
	std::list<std::shared_ptr<Heart>>			m_listHeart;


    float										m_Time;
	bool										m_isPause;
	int											m_PressKey;
};

