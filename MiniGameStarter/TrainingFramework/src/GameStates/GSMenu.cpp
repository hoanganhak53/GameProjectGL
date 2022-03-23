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
	m_numChar = 1;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_play.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);


	//Sound
	std::string name = "Alarm01.wav";
	ResourceManagers::GetInstance()->PlaySound(name,true);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("b_play.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2,	660);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);
	
	// audio button

	texture = ResourceManagers::GetInstance()->GetTexture("b_audio.tga");
	auto texture2 = ResourceManagers::GetInstance()->GetTexture("b_muteAudio.tga");
	std::shared_ptr<GameButton> buttonAudio = std::make_shared<GameButton>(model, shader, texture);
	buttonAudio->Set2DPosition(Globals::screenWidth -150, 50);
	buttonAudio->SetSize(50, 50);
	buttonAudio->SetOnClick([=]() {
		if (m_audioOn) 
		{
			ResourceManagers::GetInstance()->StopSound(name);
			buttonAudio->SetTexture(texture2);
			m_audioOn = false;
		}
		else
		{
			ResourceManagers::GetInstance()->PlaySound(name);
			buttonAudio->SetTexture(texture);
			m_audioOn = true;
		}

		});
	m_listButton.push_back(buttonAudio);


	//left button
	texture = ResourceManagers::GetInstance()->GetTexture("b_left.tga");
	std::shared_ptr<GameButton> buttonL = std::make_shared<GameButton>(model, shader, texture);
	buttonL->Set2DPosition(350, 500);
	buttonL->SetSize(100, 100);
	buttonL->SetOnClick([]() {
		if(Globals::character != 1)
			Globals::character = Globals::character - 1;
		});
	m_listButton.push_back(buttonL);
	//right button
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
	texture = ResourceManagers::GetInstance()->GetTexture("b_quit.tga");
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
	m_textGameName = std::make_shared< Text>(shader, font, "Adventure Guy", Vector4(0.0f, 1.0f, 1.0f, 1.0f), 2.0f);
	m_textGameName->Set2DPosition(Vector2(40, 80));

	//character
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("char1_Run.tga");
	m_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 12, 1, 0, 0.07f);

	m_Animation->Set2DPosition(Globals::screenWidth / 2, 480);
	m_Animation->SetSize(450, 300);
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
		if (button->HandleTouchEvents(x, y, bIsPressed) && button->m_isDraw)
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
		if(it->m_isDraw)
			it->Update(deltaTime);
	}
	if (m_numChar != Globals::character) {
		GSMenu::UpdateAnimation();
		m_numChar = Globals::character;
	}
	m_Animation->Update(deltaTime);
}

void GSMenu::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		if(it->m_isDraw)
			it->Draw();
	}
	m_textGameName->Draw();
	m_Animation->Draw();
}
void GSMenu::UpdateAnimation() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("char1_Run.tga");
	if (Globals::character == 2) {
		texture = ResourceManagers::GetInstance()->GetTexture("char2.tga");
	}
	else if (Globals::character == 3) {
		texture = ResourceManagers::GetInstance()->GetTexture("char3_Run.tga");
	}
	else if (Globals::character == 4) {
		texture = ResourceManagers::GetInstance()->GetTexture("char4_Run.tga");
	}
	m_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 12, 1, 0, 0.07f);
	m_Animation->Set2DPosition(Globals::screenWidth / 2, 480);
	m_Animation->SetSize(450, 300);
}

void GSMenu::setAudio(bool audio)
{
	m_audioOn = audio;
}

bool GSMenu::getAudio()
{
	return m_audioOn;
}

