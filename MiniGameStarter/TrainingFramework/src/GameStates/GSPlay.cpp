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
	//Sound
	std::string name = "MenuSound.wav";
	ResourceManagers::GetInstance()->PlaySound(name, true);

	// background
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_layer_1.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	CreateBackground(model, shader, texture);
	CreateButton(model, shader, texture);

	texture = ResourceManagers::GetInstance()->GetTexture("I_heart.tga");
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
	m_score->Set2DPosition(Vector2(15, 45));
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
	//cup
	m_cup = std::make_shared<Cup>(model, shader, texture, 8, 1, 0, 0.07f);
	m_cup->UpdateAnimation();
	m_cup->Set2DPosition(-400, 600);
	m_cup->SetSize(64, 64);

	CreateMap(model, shader, texture);


	//ground

	std::shared_ptr<Ground>  g1 = std::make_shared<Ground>(model, shader, texture, 1, 1, 0, 0.5f, 1);
	g1->Set2DPosition(700, 750);
	g1->SetSize(1000, 100);
	g1->UpdateAnimation();
	m_listGround.push_back(g1);

	std::shared_ptr<Ground>  g2 = std::make_shared<Ground>(model, shader, texture, 1, 1, 0, 0.5f, 1);
	g2->Set2DPosition(2800, 750);
	g2->SetSize(800, 100);
	g2->UpdateAnimation();
	m_listGround.push_back(g2);

	std::shared_ptr<Ground>  g3 = std::make_shared<Ground>(model, shader, texture, 1, 1, 0, 0.5f, 1);
	g3->Set2DPosition(4800, 750);
	g3->SetSize(1300, 100);
	g3->UpdateAnimation();
	m_listGround.push_back(g3);

	std::shared_ptr<Ground>  g4 = std::make_shared<Ground>(model, shader, texture, 1, 1, 0, 0.5f, 1);
	g4->Set2DPosition(6500, 750);
	g4->SetSize(1800, 100);
	g4->UpdateAnimation();
	m_listGround.push_back(g4);

	std::shared_ptr<Ground>  g5 = std::make_shared<Ground>(model, shader, texture, 1, 1, 0, 0.5f, 1);
	g5->Set2DPosition(8800, 750);
	g5->SetSize(1000, 100);
	g5->UpdateAnimation();
	m_listGround.push_back(g5);
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
	if (!m_player->getActive() || m_player->Get2DPosition().y > Globals::screenHeight)
	{			
		Globals::moveCam = 0;
		if (m_player->GetHp() == 0 || m_player->Get2DPosition().y > Globals::screenHeight)
		{
			m_player->setActive(false);
			m_player->UpdateAnimation();
			m_Time += deltaTime;
			if (m_Time > 2.0f)
			{
				Globals::isWin = false;
				UpdateScore();
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
			if (m_player->CheckBound(obj, 1)) {
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
		for (auto it : m_listGhost)
		{
			if (!it->getActive())
				continue;
			it->Move(m_player, deltaTime);
			it->Attack(m_player);
			it->Update(deltaTime);
		}
		for (auto it : m_listGround)
		{
			if(it->m_id == 2)
				it->Falling(deltaTime, m_player);
			it->Update(deltaTime);
		}


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
	for (auto it : m_listTrampoline)
	{
		it->Jumping(m_player);
		it->Update(deltaTime);
	}

	for (auto it : m_listSpike)
	{
		it->Attack(m_player);
		it->Update(deltaTime);
	}
	if (m_cup->Win(m_player))
	{
		Globals::isWin = true;
		UpdateScore();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_OVER);
	}
	m_cup->Update(deltaTime);
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
	for (auto it : m_listTrampoline)
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
	for (auto it : m_listGhost)
	{
		if (it->getActive()) {
			it->Draw();
		}

	}
	m_cup->Draw();
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

void GSPlay::CreateMap(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
{
	int id = 0, xPosition = 0, yPosition = 0;
	FILE* fptr;
	fptr = fopen("C:\\Users\\Hoang\\Documents\\GitHub\\GameProjectGL\\MiniGameStarter\\TrainingFramework\\src\\GameStates\\DataMap.txt", "r");
	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	//id  xPosition  yPosition
	while (fscanf(fptr, "%d %d %d", &id, &xPosition, &yPosition) != EOF)
	{
		if(id == 1)
		{
			std::shared_ptr<Enemies>  chicken = std::make_shared<Enemies>(model, shader, texture, 14, 1, 0, 0.07f);
			chicken->UpdateAnimation(1);
			chicken->Set2DPosition(xPosition, yPosition);
			chicken->SetPositionStart(Vector2(xPosition, yPosition));
			chicken->SetSize(96, 96);
			m_listEnemies.push_back(chicken);
		}
		else if (id == 2)
		{
			std::shared_ptr<Enemies>  bird = std::make_shared<Enemies>(model, shader, texture, 9, 1, 0, 0.07f);
			bird->UpdateAnimation(2);
			bird->Set2DPosition(xPosition, yPosition);
			bird->SetPositionStart(Vector2(xPosition, yPosition));
			bird->SetSize(96, 96);
			m_listEnemies.push_back(bird);

		}
		else if (id == 3)
		{
			std::shared_ptr<Plant>  plant = std::make_shared<Plant>(model, shader, texture, 8, 1, 0, 0.1f);
			plant->UpdateAnimation();
			plant->Set2DPosition(xPosition, yPosition);
			plant->SetPositionStart(Vector2(xPosition, yPosition));
			plant->SetSize(96, 96);

			plant->m_bullet->Set2DPosition(plant->Get2DPosition().x, plant->Get2DPosition().y - 5);
			plant->m_bullet->SetPositionStart(Vector2(plant->Get2DPosition().x, plant->Get2DPosition().y - 5));
			m_listPlant.push_back(plant);
		}
		else if (id == 4)
		{
			std::shared_ptr<Enemies>  bun = std::make_shared<Enemies>(model, shader, texture, 12, 1, 0, 0.1f);
			bun->UpdateAnimation(3);
			bun->Set2DPosition(xPosition, yPosition);
			bun->SetPositionStart(Vector2(xPosition, yPosition));
			bun->SetSize(96, 96);
			m_listEnemies.push_back(bun);
		}
		else if (id == 5)
		{
			std::shared_ptr<Ghost>  ghost = std::make_shared<Ghost>(model, shader, texture, 10, 1, 0, 0.07f);
			ghost->UpdateAnimation();
			ghost->Set2DPosition(xPosition, yPosition);
			ghost->SetSize(96, 96);
			m_listGhost.push_back(ghost);
		}
		else if (id == 6)
		{
			std::shared_ptr<Spike>  spike = std::make_shared<Spike>(model, shader, texture, 1, 1, 0, 0.1f);
			spike->UpdateAnimation();
			spike->Set2DPosition(xPosition, yPosition);
			spike->SetSize(32, 32);
			m_listSpike.push_back(spike);
		}
		else if (id == 7)
		{
			std::shared_ptr<Heart> heart = std::make_shared<Heart>(model, shader, texture, 1, 1, 0, 0.1f);
			heart->UpdateAnimation();
			heart->Set2DPosition(xPosition, yPosition);
			heart->SetSize(32, 32);
			m_listHeart.push_back(heart);
		}
		else if (id == 8)
		{
			std::shared_ptr<Coin> coin = std::make_shared<Coin>(model, shader, texture, 6, 1, 0, 0.1f);
			coin->UpdateAnimation();
			coin->Set2DPosition(xPosition, yPosition);
			coin->SetSize(32, 32);
			m_listCoin.push_back(coin);
		}
		else if (id == 9)
		{
			std::shared_ptr<Trampoline > trampoline= std::make_shared<Trampoline>(model, shader, texture, 14, 1, 0, 0.07f);
			trampoline->UpdateAnimation();
			trampoline->Set2DPosition(xPosition, yPosition);
			trampoline->SetSize(96, 96);
			m_listTrampoline.push_back(trampoline);
		}
		else if (id == 10)
		{
			std::shared_ptr<Ground>  ground3 = std::make_shared<Ground>(model, shader, texture, 1, 1, 0, 0.7f, 3);
			ground3->Set2DPosition(xPosition, yPosition);
			ground3->SetSize(128, 32);
			ground3->UpdateAnimation();
			m_listGround.push_back(ground3);
		}
		else if (id == 11)
		{
			std::shared_ptr<Ground>  ground2 = std::make_shared<Ground>(model, shader, texture, 4, 1, 0, 0.1f, 2);
			ground2->Set2DPosition(xPosition, yPosition);
			ground2->SetSize(128, 32);
			ground2->UpdateAnimation();
			m_listGround.push_back(ground2);
		}
	}
	fclose(fptr);
}

void GSPlay::UpdateScore()
{
	if(m_player->GetScore() > Globals::bestSocre)
	{
		FILE* fptr;
		fptr = fopen("C:\\Users\\Hoang\\Documents\\GitHub\\GameProjectGL\\MiniGameStarter\\TrainingFramework\\src\\GameStates\\BestScore.txt", "r+");
		if (fptr == NULL)
		{
			printf("Error!");
			exit(1);
		}
		fprintf(fptr, "%d", m_player->GetScore());
		fclose(fptr);
		Globals::bestSocre = m_player->GetScore();
	}
	//Sound
	ResourceManagers::GetInstance()->StopSound("MenuSound.wav");
}




void GSPlay::CreateButton(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
{
	// button home
	texture = ResourceManagers::GetInstance()->GetTexture("b_home.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2 + 100, Globals::screenHeight / 2);
	button->SetSize(70, 70);
	button->SetOnClick([this]() {
		ResourceManagers::GetInstance()->StopSound("MenuSound.wav");
		ResourceManagers::GetInstance()->PlaySound("MenuSound.wav", true);
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
		ResourceManagers::GetInstance()->StopSound("MenuSound.wav");
		ResourceManagers::GetInstance()->PlaySound("MenuSound.wav", true);
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButtonPause.push_back(buttonRestart);
}

