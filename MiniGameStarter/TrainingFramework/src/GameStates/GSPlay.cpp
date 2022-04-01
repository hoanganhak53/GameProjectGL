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

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_PressKey = 0;
	m_Test = 1;
	m_isPause = false;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_play.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button home
	texture = ResourceManagers::GetInstance()->GetTexture("b_home.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2 + 100 , Globals::screenHeight/2);
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

	texture = ResourceManagers::GetInstance()->GetTexture("image_heart.tga");
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


	//player
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("trampoline.tga");
	m_player = std::make_shared<Player>(model, shader, texture, 12, 1, 0, 0.07f);
	m_player->setIdCharacter(Globals::character);
	m_player->UpdateAnimation();
	m_player->Set2DPosition(600, 400);
	m_player->SetSize(100, 100);
	//trampoline
	m_trampoline = std::make_shared<Trampoline>(model, shader, texture, 8, 1, 0, 0.15f);
	m_trampoline->UpdateAnimation();
	m_trampoline->Set2DPosition(400, 680);
	m_trampoline->SetSize(50, 50);
	//coin
	std::shared_ptr<Coin> coin1 = std::make_shared<Coin>(model, shader, texture, 6, 1, 0, 0.1f);
	coin1->UpdateAnimation();
	coin1->Set2DPosition(700, 700);
	coin1->SetSize(30, 30);
	m_listCoin.push_back(coin1);

	std::shared_ptr<Coin> coin2 = std::make_shared<Coin>(model, shader, texture, 6, 1, 0, 0.1f);
	coin2->UpdateAnimation();
	coin2->Set2DPosition(300, 200);
	coin2->SetSize(30, 30);
	m_listCoin.push_back(coin2);

	std::shared_ptr<Coin> coin3 = std::make_shared<Coin>(model, shader, texture, 6, 1, 0, 0.1f);
	coin3->UpdateAnimation();
	coin3->Set2DPosition(950, 500);
	coin3->SetSize(30, 30);
	m_listCoin.push_back(coin3);
	//ground
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	texture = ResourceManagers::GetInstance()->GetTexture("ground.tga");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Sprite2D>  m_object = std::make_shared<Sprite2D>(model, shader, texture);
	m_object->Set2DPosition(500, 400);
	m_object->SetSize(200, 20);
	m_listObject.push_back(m_object);

	std::shared_ptr<Sprite2D>  m_object1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_object1->Set2DPosition(1000, 530);
	m_object1->SetSize(200, 20);
	m_listObject.push_back(m_object1);

	std::shared_ptr<Sprite2D>  m_object2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_object2->Set2DPosition(0, 760);
	m_object2->SetSize(3300, 80);
	m_listObject.push_back(m_object2);

}

void GSPlay::Exit()
{
	printf("%d", m_Test);
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
		switch (m_PressKey) 
		{
		case 1: //sang trai
		{
			if(m_player->getJump())
				m_player->SetRotation(Vector3(0.0f, 0.0, 0.0f));
			else
				m_player->SetRotation(Vector3(0.0f, PI, 0.0f));	
			m_player->Set2DPosition(m_player->Get2DPosition().x - deltaTime * 150, m_player->Get2DPosition().y);
			break;
		}
		case 1 << 1: //sang phai
		{
			if (m_player->getJump())
				m_player->SetRotation(Vector3(0.0f, PI, 0.0f));
			else
				m_player->SetRotation(Vector3(0.0f, 0.0, 0.0f));
			m_player->Set2DPosition(m_player->Get2DPosition().x + deltaTime * 150, m_player->Get2DPosition().y);
			break;
		}
		case 1 << 2: // nhay
		{
			if (!m_player->getJump())
			{
				m_player->setJump(true);
				m_player->setV(20);
			}
			break;
		}
		case 1 << 2 | 1: // nhay va sang trai
		{
			m_player->UpdateAnimation();
			m_player->SetRotation(Vector3(0.0f, 0.0f, 0.0f));

			m_player->Set2DPosition(m_player->Get2DPosition().x - deltaTime * 150, m_player->Get2DPosition().y);
			if (!m_player->getJump())
			{
				m_player->setJump(true);
				m_player->setV(20);
			}
			break;
		}
		case 1 << 2 | 1 << 1: // nhau va sang phai
		{
			m_player->UpdateAnimation();
			m_player->SetRotation(Vector3(0.0f, PI, 0.0f));
			m_player->Set2DPosition(m_player->Get2DPosition().x + deltaTime * 150, m_player->Get2DPosition().y);
			if (!m_player->getJump()) // dang khong nhay moi duoc nhay
			{
				m_player->setJump(true);
				m_player->setV(20);
			}
			break;
		}
		default:
			break;
		}

		bool haveCrash = false;
		for (auto obj : m_listObject)
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
		m_player->UpdateAnimation();
		m_player->Update(deltaTime);

		for (auto it : m_listObject)
		{
			it->Set2DPosition(it->Get2DPosition().x - deltaTime * 100, it->Get2DPosition().y);
			if (it->Get2DPosition().x < -150) 
			{
				it->Set2DPosition(1400, it->Get2DPosition().y);
			}
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
		m_score->SetText(std::to_string(m_player->GetScore()));
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_player->Draw();
	m_trampoline->Draw();
	m_score->Draw();
	m_hp->Draw();
	for (auto it : m_listObject)
	{
		it->Draw();
	}
	for (auto it : m_listCoin)
	{
		if(it->getActive())
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