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
	m_numMode = 1;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_play.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);


	//Sound
	std::string name = "MenuSound.wav";
	ResourceManagers::GetInstance()->PlaySound(name,true);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("b_play.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2,	660);
	button->SetSize(64, 64);
	button->SetOnClick([]() {
			ResourceManagers::GetInstance()->StopSound("MenuSound.wav");
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
			Globals::haveSound = false;
		}
		else
		{
			ResourceManagers::GetInstance()->PlaySound(name);
			buttonAudio->SetTexture(texture);
			m_audioOn = true;
			Globals::haveSound = true;
		}

		});
	m_listButton.push_back(buttonAudio);


	//left button
	texture = ResourceManagers::GetInstance()->GetTexture("b_left.tga");
	std::shared_ptr<GameButton> buttonL = std::make_shared<GameButton>(model, shader, texture);
	buttonL->Set2DPosition(Globals::screenWidth / 4 - 200, 500);
	buttonL->SetSize(50, 50);
	buttonL->SetOnClick([]() {
		if(Globals::character != 1)
			Globals::character = Globals::character - 1;
		});
	m_listButton.push_back(buttonL);

	std::shared_ptr<GameButton> buttonL1 = std::make_shared<GameButton>(model, shader, texture);
	buttonL1->Set2DPosition(Globals::screenWidth / 4 * 3 - 200, 500);
	buttonL1->SetSize(50, 50);
	buttonL1->SetOnClick([]() {
		if (Globals::mode != 1)
			Globals::mode = Globals::mode - 1;
		});
	m_listButton.push_back(buttonL1);
	//right button
	texture = ResourceManagers::GetInstance()->GetTexture("b_right.tga");
	std::shared_ptr<GameButton> buttonR = std::make_shared<GameButton>(model, shader, texture);
	buttonR->Set2DPosition(Globals::screenWidth / 4 + 200 ,500);
	buttonR->SetSize(50, 50);
	buttonR->SetOnClick([]() {
		if (Globals::character != 4)
			Globals::character = Globals::character + 1;
		});
	m_listButton.push_back(buttonR);

	std::shared_ptr<GameButton> buttonR1 = std::make_shared<GameButton>(model, shader, texture);
	buttonR1->Set2DPosition(Globals::screenWidth / 4 * 3 + 200, 500);
	buttonR1->SetSize(50, 50);
	buttonR1->SetOnClick([]() {
		if (Globals::mode != 3)
			Globals::mode = Globals::mode + 1;
		});
	m_listButton.push_back(buttonR1);
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
	// score	
	m_score = std::make_shared< Text>(shader, font, "Best score:", Vector4(0.0f, 1.0f, 1.0f, 1.0f), 1.0f);
	m_score->Set2DPosition(Vector2(900, 60));

	m_mode = std::make_shared< Text>(shader, font, " Normal", Vector4(0.0f, 1.0f, 1.0f, 1.0f), 1.5f);
	m_mode->Set2DPosition(Vector2(Globals::screenWidth / 4 * 3 - 70, 515));

	FILE* fptr;
	fptr = fopen("..\\Data\\TextData\\BestScore.txt", "r");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	GLint score = 0;
	while (fscanf(fptr, "%d", &score) != EOF)
	{
		m_score->SetText("Best score: " + std::to_string(score));
	}
	fclose(fptr);
	Globals::bestSocre = score;

	//character
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("char1_Run.tga");
	m_player = std::make_shared<Player>(model, shader, texture, 12, 1, 0, 0.07f);

	m_player->Set2DPosition(Globals::screenWidth / 4, 480);
	m_player->SetSize(96, 96);
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
		m_player->setIdCharacter(Globals::character);
		m_player->UpdateAnimation();
		m_numChar = Globals::character;
	}
	if (m_numMode != Globals::mode) {
		if(Globals::mode == 1)
			m_mode->SetText(" Normal");
		else if(Globals::mode == 2)
			m_mode->SetText("  Hard");
		else
			m_mode->SetText("Speed Run");

		m_numMode = Globals::mode;
	}
	m_player->Update(deltaTime);
	m_score->SetText("Best score: " + std::to_string(Globals::bestSocre));
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
	m_score->Draw();
	m_player->Draw();
	m_mode->Draw();
}

void GSMenu::setAudio(bool audio)
{
	m_audioOn = audio;
}

bool GSMenu::getAudio()
{
	return m_audioOn;
}

