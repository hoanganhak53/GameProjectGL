#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"
#include "Player.h"
#include "Trampoline.h"
#include "Enemies.h"
#include "Ground.h"


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_PressKey = 0;
	m_Time = 0;
	m_isPause = false;

	// background
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_layer_1.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	CreateBackground(model, shader, texture);
	CreateButton(model, shader, texture);

	texture = ResourceManagers::GetInstance()->GetTexture("I_heart.tga");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Sprite2D>  heart = std::make_shared<Sprite2D>(model, shader, texture);
	heart->Set2DPosition(160, 32);
	heart->SetSize(40, 40);
	m_listImage.push_back(heart);

	texture = ResourceManagers::GetInstance()->GetTexture("image_coin.tga");
	std::shared_ptr<Sprite2D>  coin = std::make_shared<Sprite2D>(model, shader, texture);
	coin->Set2DPosition(60, 32);
	coin->SetSize(40, 40);
	m_listImage.push_back(coin);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "10", TextColor::CYAN, 1.3);
	m_score->Set2DPosition(Vector2(20, 45));
	m_score->SetText("0");
	//hp
	m_hp = std::make_shared< Text>(shader, font, "10", TextColor::CYAN, 1.3);
	m_hp->Set2DPosition(Vector2(110, 45));
	m_hp->SetText("3");

	//player
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("trampoline.tga");
	m_player = std::make_shared<Player>(model, shader, texture, 12, 1, 0, 0.07f);
	m_player->setIdCharacter(Globals::character);
	m_player->UpdateAnimation();
	m_player->Set2DPosition(600, 400);
	m_player->SetSize(96, 96);

	CreateEnemies(model, shader, texture);
	//trampoline
	m_trampoline = std::make_shared<Trampoline>(model, shader, texture, 14, 1, 0, 0.07f);
	m_trampoline->UpdateAnimation();
	m_trampoline->Set2DPosition(400, 680);
	m_trampoline->SetSize(96, 96);

	//coin
	std::shared_ptr<Coin> coin1 = std::make_shared<Coin>(model, shader, texture, 6, 1, 0, 0.1f);
	coin1->UpdateAnimation();
	coin1->Set2DPosition(700, 700);
	coin1->SetSize(32, 32);
	m_listCoin.push_back(coin1);

	std::shared_ptr<Coin> coin2 = std::make_shared<Coin>(model, shader, texture, 6, 1, 0, 0.1f);
	coin2->UpdateAnimation();
	coin2->Set2DPosition(300, 200);
	coin2->SetSize(32, 32);
	m_listCoin.push_back(coin2);

	std::shared_ptr<Coin> coin3 = std::make_shared<Coin>(model, shader, texture, 6, 1, 0, 0.1f);
	coin3->UpdateAnimation();
	coin3->Set2DPosition(950, 500);
	coin3->SetSize(32, 32);
	m_listCoin.push_back(coin3);
	//
	std::shared_ptr<Heart> h = std::make_shared<Heart>(model, shader, texture, 1, 1, 0, 0.1f);
	h->UpdateAnimation();
	h->Set2DPosition(950, 500);
	h->SetSize(32, 32);
	m_listHeart.push_back(h);

	//ground
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	texture = ResourceManagers::GetInstance()->GetTexture("Ground3.tga");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Ground>  m_object = std::make_shared<Ground>(model, shader, texture, 3);
	m_object->Set2DPosition(500, 400);
	m_object->UpdateAnimation();
	m_object->SetSize(128, 32);
	m_listGround.push_back(m_object);

	std::shared_ptr<Ground>  m_object1 = std::make_shared<Ground>(model, shader, texture, 3);
	m_object1->Set2DPosition(1000, 530);
	m_object1->SetSize(128, 32);
	m_object1->UpdateAnimation();
	m_listGround.push_back(m_object1);

	std::shared_ptr<Ground>  m_object2 = std::make_shared<Ground>(model, shader, texture, 1);
	m_object2->Set2DPosition(0, 760);
	m_object2->SetSize(8300, 80);
	m_object2->UpdateAnimation();
	m_listGround.push_back(m_object2);
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
	m_isPause = true;
}

void GSPlay::Resume()
{
	m_isPause = false;
}

void GSPlay::Restart()
{
	m_isPause = false;
}

void GSPlay::Attacked(float deltaTime)
{
	if (!m_player->getActive())
	{			
		Globals::moveCam = 0;
		if (m_player->GetHp() == 0 || m_player->Get2DPosition().y > Globals::screenHeight)
		{
			m_player->setActive(false);
			m_player->UpdateAnimation();
			m_Time += deltaTime;
			if (m_Time > 2.5f)
			{
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OVER);
			}
		}
		else
		{
			m_Time += deltaTime;
			if (m_Time > 0.84)
			{
				m_player->setActive(true);
				m_player->UpdateAnimation();
				m_Time = 0;
			}
		}
	}
}

void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed) 
	{
		switch (key)
		{
		case KEY_MOVE_LEFT: 
		{
			m_PressKey |= 1;
			break;
		}
		case KEY_MOVE_RIGHT: 
		{
			m_PressKey |= 1<<1;
			break;
		}
		case KEY_SPACE: 
		{
			m_PressKey |= 1<<2;
			break;
		}
		default:
			break;
		}
	}
	else {
		switch (key)
		{
		case KEY_MOVE_LEFT:
		{
			m_PressKey ^= 1;
			break;
		}
		case KEY_MOVE_RIGHT:
		{
			m_PressKey ^= 1 << 1;
			break;
		}
		case KEY_SPACE:
		{
			m_PressKey ^= 1 << 2;
			break;
		}
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
	for (auto button : m_listButtonPause)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if (!m_isPause) 
	{
		bool haveCrash = false;
		for (auto obj : m_listGround)
		{
			if (m_player->CheckBound(obj)) {
				haveCrash = true;
			}
		}
		if (haveCrash && m_player->getV() != 20)
		{
			m_player->setV(0);
			m_player->setJump(false);
		}
		else 
		{
			m_player->Set2DPosition(m_player->Get2DPosition().x, m_player->Get2DPosition().y - m_player->getV() * deltaTime * 70);
			m_player->setV(m_player->getV() - deltaTime * 90);
		}
		if(m_player->getActive())
			m_player->Move(deltaTime, m_PressKey);
		m_player->UpdateAnimation();
		m_player->Update(deltaTime);


		for (auto it : m_listEnemies)
		{
			if (!it->getActive())
				continue;
			it->Move(deltaTime);
			it->Attack(m_player);
			it->Update(deltaTime);
		}

		for (auto it : m_listPlant)
		{
			if (!it->getActive())
				continue;

			it->m_bullet->Attack(m_player);
			it->m_bullet->Move(deltaTime);
			it->m_bullet->Update(deltaTime);
			it->Attack(m_player);
			it->Update(deltaTime);
		}		

		for (auto it : m_listGround)
		{
			it->Set2DPosition(it->Get2DPosition().x - Globals::moveCam, it->Get2DPosition().y);
			it->Update(deltaTime);
		}

		m_trampoline->Jumping(m_player);
		m_trampoline->Update(deltaTime);

		for (auto it : m_listCoin)
		{
			if (it->Collecting(m_player)) {
				it->setActive(false);
			}else
				it->Update(deltaTime);
		}
		for (auto it : m_listHeart)
		{
			if (it->BuffHP(m_player)) {
				it->setActive(false);
			}
			else
				it->Update(deltaTime);
		}
		m_score->SetText(std::to_string(m_player->GetScore()));
		m_hp->SetText(std::to_string(m_player->GetHp()));
	}

	for (auto it : m_listSpike)
	{
		it->Attack(m_player);
		it->Update(deltaTime);
	}

	for (auto it : m_listBackground)
	{
		if(it->Get2DPosition().x < -Globals::screenWidth / 2)
			it->Set2DPosition(Globals::screenWidth / 2 * 3 - 15, it->Get2DPosition().y);
		if(it->Get2DPosition().x > Globals::screenWidth / 2 * 3)
			it->Set2DPosition( -Globals::screenWidth / 2 + 15, it->Get2DPosition().y);

		it->Set2DPosition(it->Get2DPosition().x - Globals::moveCam, it->Get2DPosition().y);
		it->Update(deltaTime);
	}
	Attacked(deltaTime);
}

void GSPlay::Draw()
{
	for (auto it : m_listBackground)
	{
		it->Draw();
	}
	m_trampoline->Draw();
	m_score->Draw();
	m_hp->Draw();
	for (auto it : m_listGround)
	{
		it->Draw();
	}
	for (auto it : m_listSpike)
	{
		it->Draw();
	}

	for (auto it : m_listEnemies)
	{
		if(it->getActive())
			it->Draw();
	}
	for (auto it : m_listPlant)
	{
		if (it->getActive()) {
			it->DrawBullet();
			it->Draw();
		}

	}
	m_player->Draw();

	for (auto it : m_listCoin)
	{
		if(it->getActive())
			it->Draw();
	}
	for (auto it : m_listHeart)
	{
		if (it->getActive())
			it->Draw();
	}
	for (auto it : m_listImage)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	if (m_isPause) {
		for (auto it : m_listButtonPause)
		{
			it->Draw();
		}
	}
}


void GSPlay::CreateEnemies(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
{
	//enemies
	std::shared_ptr<Enemies>  chicken = std::make_shared<Enemies>(model, shader, texture, 14, 1, 0, 0.07f);
	chicken->UpdateAnimation(1);
	chicken->Set2DPosition(900, 680);
	chicken->SetPositionStart(Vector2(900, 680));
	chicken->SetSize(96, 96);
	m_listEnemies.push_back(chicken);

	std::shared_ptr<Enemies>  bird = std::make_shared<Enemies>(model, shader, texture, 9, 1, 0, 0.07f);
	bird->UpdateAnimation(2);
	bird->Set2DPosition(700, 280);
	bird->SetPositionStart(Vector2(900, 680));
	bird->SetSize(96, 96);
	m_listEnemies.push_back(bird);

	std::shared_ptr<Plant>  plant = std::make_shared<Plant>(model, shader, texture, 8, 1, 0, 0.1f);
	plant->UpdateAnimation();
	plant->Set2DPosition(1000, 680);
	plant->SetPositionStart(Vector2(900, 680));
	plant->SetSize(96, 96);

	plant->m_bullet->Set2DPosition(plant->Get2DPosition().x, plant->Get2DPosition().y - 5);
	plant->m_bullet->SetPositionStart(Vector2(plant->Get2DPosition().x, plant->Get2DPosition().y - 5));
	m_listPlant.push_back(plant);
	// spike
	std::shared_ptr<Spike>  spike1 = std::make_shared<Spike>(model, shader, texture, 1, 1, 0, 0.1f);
	spike1->UpdateAnimation();
	spike1->Set2DPosition(1700, 700);
	spike1->SetSize(32, 32);
	m_listSpike.push_back(spike1);
	//
	std::shared_ptr<Enemies>  bun = std::make_shared<Enemies>(model, shader, texture, 10, 1, 0, 0.1f);
	bun->UpdateAnimation(3);
	bun->Set2DPosition(1300, 680);
	bun->SetPositionStart(Vector2(-300, 680));
	bun->SetSize(96, 96);
	m_listEnemies.push_back(bun);
}

void GSPlay::CreateBackground(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
{

	std::shared_ptr<Sprite2D> bg1 = std::make_shared<Sprite2D>(model, shader, texture);
	bg1->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	bg1->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_listBackground.push_back(bg1);

	std::shared_ptr<Sprite2D> bg4 = std::make_shared<Sprite2D>(model, shader, texture);
	bg4->Set2DPosition((float)Globals::screenWidth / 2 + Globals::screenWidth, (float)Globals::screenHeight / 2);
	bg4->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_listBackground.push_back(bg4);

	std::shared_ptr<Sprite2D> bg7 = std::make_shared<Sprite2D>(model, shader, texture);
	bg7->Set2DPosition(-(float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	bg7->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_listBackground.push_back(bg7);

	texture = ResourceManagers::GetInstance()->GetTexture("background_layer_2.tga");
	std::shared_ptr<Sprite2D> bg2 = std::make_shared<Sprite2D>(model, shader, texture);
	bg2->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	bg2->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_listBackground.push_back(bg2);

	std::shared_ptr<Sprite2D> bg5 = std::make_shared<Sprite2D>(model, shader, texture);
	bg5->Set2DPosition((float)Globals::screenWidth / 2 + Globals::screenWidth, (float)Globals::screenHeight / 2);
	bg5->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_listBackground.push_back(bg5);

	std::shared_ptr<Sprite2D> bg8 = std::make_shared<Sprite2D>(model, shader, texture);
	bg8->Set2DPosition(-(float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	bg8->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_listBackground.push_back(bg8);

	texture = ResourceManagers::GetInstance()->GetTexture("background_layer_3.tga");
	std::shared_ptr<Sprite2D> bg3 = std::make_shared<Sprite2D>(model, shader, texture);
	bg3->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	bg3->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_listBackground.push_back(bg3);

	std::shared_ptr<Sprite2D> bg6 = std::make_shared<Sprite2D>(model, shader, texture);
	bg6->Set2DPosition((float)Globals::screenWidth / 2 + Globals::screenWidth, (float)Globals::screenHeight / 2);
	bg6->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_listBackground.push_back(bg6);

	std::shared_ptr<Sprite2D> bg9 = std::make_shared<Sprite2D>(model, shader, texture);
	bg9->Set2DPosition(-(float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	bg9->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_listBackground.push_back(bg9);
}




void GSPlay::CreateButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
{
	// button home
	texture = ResourceManagers::GetInstance()->GetTexture("b_home.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 2);
	button->SetSize(70, 70);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButtonPause.push_back(button);

	// button resume
	texture = ResourceManagers::GetInstance()->GetTexture("b_play.tga");
	std::shared_ptr<GameButton>  buttonResume = std::make_shared<GameButton>(model, shader, texture);
	buttonResume->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	buttonResume->SetSize(70, 70);
	buttonResume->SetOnClick([this]() {
		Resume();
		});
	m_listButtonPause.push_back(buttonResume);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("b_pause.tga");
	std::shared_ptr<GameButton>  buttonPause = std::make_shared<GameButton>(model, shader, texture);
	buttonPause->Set2DPosition(Globals::screenWidth - 50, 50);
	buttonPause->SetSize(70, 70);
	buttonPause->SetOnClick([this]() {
		Globals::moveCam = 0;
		Pause();
		});
	m_listButton.push_back(buttonPause);

	// button restart
	texture = ResourceManagers::GetInstance()->GetTexture("b_restart.tga");
	std::shared_ptr<GameButton>  buttonRestart = std::make_shared<GameButton>(model, shader, texture);
	buttonRestart->Set2DPosition(Globals::screenWidth / 2 - 100, Globals::screenHeight / 2);
	buttonRestart->SetSize(70, 70);
	buttonRestart->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButtonPause.push_back(buttonRestart);
}
