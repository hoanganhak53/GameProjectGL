#include "GSMenu.h"
#include "Camera.h"
GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU), 
	m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	numChar = 1;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_play.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("b_play.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2,	660);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("b_left.tga");
	std::shared_ptr<GameButton> buttonL = std::make_shared<GameButton>(model, shader, texture);
	buttonL->Set2DPosition(350, 500);
	buttonL->SetSize(100, 100);
	buttonL->SetOnClick([]() {
		if(Globals::character != 1)
			Globals::character = Globals::character - 1;
		});
	m_listButton.push_back(buttonL);

	texture = ResourceManagers::GetInstance()->GetTexture("b_right.tga");
	std::shared_ptr<GameButton> buttonR = std::make_shared<GameButton>(model, shader, texture);
	buttonR->Set2DPosition(950,500);
	buttonR->SetSize(100, 100);
	buttonR->SetOnClick([]() {
		if (Globals::character != 4)
			Globals::character = Globals::character + 1;
		});
	m_listButton.push_back(buttonR);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("b_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);


	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textGameName = std::make_shared< Text>(shader, font, "HA Game", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_textGameName->Set2DPosition(Vector2(60, 200));

	std::string name = "Alarm01.wav";
	ResourceManagers::GetInstance()->PlaySound(name);
	//character
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("char1.tga");
	m_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);

	m_Animation->Set2DPosition(Globals::screenWidth / 2, 500);
	m_Animation->SetSize(334, 223);
}

void GSMenu::Exit()
{
	ResourceManagers::FreeInstance();
}


void GSMenu::Pause()
{
}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if (numChar != Globals::character) {
		GSMenu::UpdateAnimation();
		numChar = Globals::character;
	}
	m_Animation->Update(deltaTime);
}

void GSMenu::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
	m_Animation->Draw();
}
void GSMenu::UpdateAnimation() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("char1.tga");
	if (Globals::character == 2) {
		texture = ResourceManagers::GetInstance()->GetTexture("char2.tga");
	}
	else if (Globals::character == 3) {
		texture = ResourceManagers::GetInstance()->GetTexture("char3.tga");
	}
	else if (Globals::character == 4) {
		texture = ResourceManagers::GetInstance()->GetTexture("char4.tga");
	}
	m_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 1, 0, 0.1f);
	m_Animation->Set2DPosition(Globals::screenWidth / 2, 500);
	m_Animation->SetSize(334, 223);
}