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
	m_Test = 1;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_play.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("b_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
			GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


	texture = ResourceManagers::GetInstance()->GetTexture("b_right.tga");
	std::shared_ptr<GameButton>  button1 = std::make_shared<GameButton>(model, shader, texture);
	button1->Set2DPosition(Globals::screenWidth - 200, 50);
	button1->SetSize(50, 50);
	button1->SetOnClick([this]() {
		for (auto it : m_listAnimation)
		{
			it->Set2DPosition(it->Get2DPosition().x + 20, it->Get2DPosition().y );
		}
		});
	m_listButton.push_back(button1);

	texture = ResourceManagers::GetInstance()->GetTexture("b_left.tga");
	std::shared_ptr<GameButton>  button2 = std::make_shared<GameButton>(model, shader, texture);
	button2->Set2DPosition(Globals::screenWidth - 300, 50);
	button2->SetSize(50, 50);
	button2->SetOnClick([this]() {
		for (auto it : m_listAnimation)
		{
			it->Set2DPosition(it->Get2DPosition().x - 20, it->Get2DPosition().y);
		}
		});
	m_listButton.push_back(button2);


	std::shared_ptr<GameButton>  button3 = std::make_shared<GameButton>(model, shader, texture);
	button3->Set2DPosition(Globals::screenWidth - 400, 50);
	button3->SetSize(50, 50);
	button3->SetOnClick([this]() {
		for (auto it : m_listAnimation)
		{
			it->setJump(true);
			it->setVt(20);
		}
		});
	m_listButton.push_back(button3);
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
	m_object->Set2DPosition(500, 400);
	m_object->SetSize(200, 80);
	m_listObject.push_back(m_object);

	std::shared_ptr<Sprite2D>  m_object1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_object1->Set2DPosition(1000, 530);
	m_object1->SetSize(200, 80);
	m_listObject.push_back(m_object1);

	std::shared_ptr<Sprite2D>  m_object2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_object2->Set2DPosition(0, 800);
	m_object2->SetSize(3300, 80);
	m_listObject.push_back(m_object2);

	//cell
	std::shared_ptr<Sprite2D>  m_object3 = std::make_shared<Sprite2D>(model, shader, texture);
	m_object3->Set2DPosition(0, 0);
	m_object3->SetSize(3300, 80);
	m_listObject.push_back(m_object3);
}

void GSPlay::Exit()
{
	printf("%d", m_Test);
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	switch (key)
	{
	case 32: {

		break;
	}
	default:
		break;
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
	for (auto it : m_listAnimation)
	{	
		if (1) {
			bool haveCrash = false;
			for (auto obj1 : m_listObject)
			{
				if (it->CheckBound(obj1)) {
					haveCrash = true;
					if (it->getContinueCrash() == false) {
						it->Set2DPosition(it->Get2DPosition().x, it->Get2DPosition().y + 10);
					}
					it->setContinueCrash(true);
				}
				
			}
			if (haveCrash && it->getVt() != 20) {
				it->setVt(0);
				it->setJump(false);
				
			}
			else {

				//			vh = it->GetDirect();
				//			if ((it->Get2DPosition().y >= 650 && vh > 0) || it->Get2DPosition().y <= 150 && vh < 0){
				//				vh = -vh;
				//				it->SetDirect(vh);
				//			}

				it->Set2DPosition(it->Get2DPosition().x, it->Get2DPosition().y - it->getVt());
				it->setVt(it->getVt() - 1);
				it->setContinueCrash(false);
			}
		}
		it->Update(deltaTime);
	}
	for (auto it : m_listObject)
	{
		it->Set2DPosition(it->Get2DPosition().x - 2, it->Get2DPosition().y );
		if (it->Get2DPosition().x < -150) {
			it->Set2DPosition(1400, it->Get2DPosition().y);
		}
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	for (auto it : m_listObject)
	{
		it->Draw();
	}
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}

}