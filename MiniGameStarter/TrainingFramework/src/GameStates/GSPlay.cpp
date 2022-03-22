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


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	isPress = 0;
	m_Test = 1;
	isPause = false;
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
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	shader = ResourceManagers::GetInstance()->GetShader("Animation");

	if (Globals::character == 1) {
		texture = ResourceManagers::GetInstance()->GetTexture("char1.tga");
	}
	else if (Globals::character == 2) {
		texture = ResourceManagers::GetInstance()->GetTexture("char2.tga");
	}
	else if (Globals::character == 3) {
		texture = ResourceManagers::GetInstance()->GetTexture("char3.tga");
	}
	else if (Globals::character == 4) {
		texture = ResourceManagers::GetInstance()->GetTexture("char4.tga");
	}

	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	
	obj->Set2DPosition(240, 400);
	obj->SetSize(334, 223);
	std::shared_ptr<SpriteAnimation> obj1 = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);

	obj1->Set2DPosition(100, 700);
	obj1->SetSize(334, 223);
	//obj->SetRotation(Vector3(0.0f, 3.14f, 0.0f));
	m_listAnimation.push_back(obj);
	m_listAnimation.push_back(obj1);

	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	texture = ResourceManagers::GetInstance()->GetTexture("ground.tga");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Sprite2D>  m_object = std::make_shared<Sprite2D>(model, shader, texture);
	m_object->Set2DPosition(500, 100);
	m_object->SetSize(200, 80);
	m_listObject.push_back(m_object);

	std::shared_ptr<Sprite2D>  m_object1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_object1->Set2DPosition(1000, 230);
	m_object1->SetSize(200, 80);
	m_listObject.push_back(m_object1);

	std::shared_ptr<Sprite2D>  m_object2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_object2->Set2DPosition(0, 800);
	m_object2->SetSize(3300, 80);
	m_listObject.push_back(m_object2);
}

void GSPlay::Exit()
{
	printf("%d", m_Test);
}


void GSPlay::Pause()
{
	isPause = true;
}

void GSPlay::Resume()
{
	isPause = false;
}

void GSPlay::Restart()
{
	isPause = false;
}
void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed) {
		switch (key)
		{
		case KEY_MOVE_LEFT: {
			isPress = 1;
			break;
		}case KEY_MOVE_RIGHT: {
			isPress = 2;
			break;
		}case KEY_MOVE_FORWORD: {
			isPress = 3;
			break;
		}
		default:
			break;
		}
	}else
		isPress = 0;

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
	if (!isPause) {
		for (auto it : m_listAnimation)
		{

			switch (isPress) {
			case 1: {
				it->Set2DPosition(it->Get2DPosition().x - 2, it->Get2DPosition().y);
				break;
			}case 2: {
				it->Set2DPosition(it->Get2DPosition().x + 2, it->Get2DPosition().y);
				break;
			}case 3: {
				if (!it->getJump()) {
					it->setJump(true);
					it->setVt(20);
				}
				break;
			}
			default:
				break;
			}
			if (it->getJump()) {

				bool haveCrash = false;
				for (auto obj1 : m_listObject)
				{
					if (it->CheckBound(obj1)) {
						haveCrash = true;
					}

				}
				if (haveCrash && it->getVt() != 20) {
					it->setVt(0);
					it->setJump(false);
				}
				else {
					it->Set2DPosition(it->Get2DPosition().x, it->Get2DPosition().y - it->getVt());
					it->setVt(it->getVt() - 1);
				}
			}

			it->Update(deltaTime);
		}
		for (auto it : m_listObject)
		{
			it->Set2DPosition(it->Get2DPosition().x - 2, it->Get2DPosition().y);
			if (it->Get2DPosition().x < -150) {
				it->Set2DPosition(1400, it->Get2DPosition().y);
			}
			it->Update(deltaTime);
		}
	}

}

void GSPlay::Draw()
{
	m_background->Draw();
	for (auto it : m_listObject)
	{
		it->Draw();
	}
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	if (isPause) {
		for (auto it : m_listButtonPause)
		{
			it->Draw();
		}
	}
	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
}