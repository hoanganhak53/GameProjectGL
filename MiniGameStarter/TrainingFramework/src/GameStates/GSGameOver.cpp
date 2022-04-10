#include "GSGameOver.h"
#include "Camera.h"

GSGameOver::GSGameOver() : GameStateBase(StateType::STATE_OVER),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{})
{
}

GSGameOver::~GSGameOver()
{
}

void GSGameOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("win.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// background
	std::string song;
	if(Globals::isWin)
	{
		song = "Win.wav";
		m_background = std::make_shared<Sprite2D>(model, shader, texture);
		m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
		m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	}
	else
	{
		song = "Lose.wav";
		auto texture = ResourceManagers::GetInstance()->GetTexture("lose.tga");
		m_background = std::make_shared<Sprite2D>(model, shader, texture);
		m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
		m_background->SetSize(Globals::screenWidth, Globals::screenHeight);
	}
	if(Globals::haveSound)
		ResourceManagers::GetInstance()->PlaySound(song);

	
	//home button
	texture = ResourceManagers::GetInstance()->GetTexture("b_home.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 5 * 4 + 100);
	button->SetSize(64, 64);
	button->SetOnClick([this]() {
		if (Globals::haveSound)
		{
			if(Globals::isWin)
				ResourceManagers::GetInstance()->StopSound("Win.wav");
			else
				ResourceManagers::GetInstance()->StopSound("Lose.wav");

		ResourceManagers::GetInstance()->PlaySound("MenuSound.wav");
		}

		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//restart button
	texture = ResourceManagers::GetInstance()->GetTexture("b_restart.tga");
	std::shared_ptr<GameButton>  buttonRestart = std::make_shared<GameButton>(model, shader, texture);
	buttonRestart->Set2DPosition(Globals::screenWidth / 2 - 100, Globals::screenHeight / 5 * 4 + 100);
	buttonRestart->SetSize(64, 64);
	buttonRestart->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		if (Globals::haveSound)
		{
			if (Globals::isWin)
				ResourceManagers::GetInstance()->StopSound("Win.wav");
			else
				ResourceManagers::GetInstance()->StopSound("Lose.wav");

			ResourceManagers::GetInstance()->PlaySound("MenuSound.wav");
		}
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(buttonRestart);

}

void GSGameOver::Exit()
{
}

void GSGameOver::Pause()
{
}

void GSGameOver::Resume()
{
}

void GSGameOver::HandleEvents()
{
}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed) && button->m_isDraw)
		{
			break;
		}
	}
}

void GSGameOver::HandleMouseMoveEvents(int x, int y)
{
}

void GSGameOver::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSGameOver::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
