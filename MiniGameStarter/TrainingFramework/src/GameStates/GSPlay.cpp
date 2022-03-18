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
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
			GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button1 = std::make_shared<GameButton>(model, shader, texture);
	button1->Set2DPosition(Globals::screenWidth - 200, 50);
	button1->SetSize(50, 50);
	button1->SetOnClick([this]() {
		m_score->DeleteText();
		});
	m_listButton.push_back(button1);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("char.tga");
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
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	texture = ResourceManagers::GetInstance()->GetTexture("ground.tga");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Sprite2D>  m_object1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_object1->Set2DPosition(1000, 230);
	m_object1->SetSize(200, 80);
	m_listObject.push_back(m_object1);
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
		bool haveCrash = false;
		for (auto obj1 : m_listObject)
		{
			if (it->CheckBound(obj1)) {
				haveCrash = true;
			}
		}
		GLint vh;
		if (haveCrash)
			vh = 0;
		else{
			vh = it->GetDirect();
			if ((it->Get2DPosition().y >= 650 && vh > 0) || it->Get2DPosition().y <= 150 && vh < 0){
				vh = -vh;
				it->SetDirect(vh);
			}
		}

		it->Set2DPosition(it->Get2DPosition().x, it->Get2DPosition().y+vh);
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
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}

}