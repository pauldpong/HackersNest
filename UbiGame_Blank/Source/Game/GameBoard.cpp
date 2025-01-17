#include "GameBoard.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/GameComponents/PlayerMovementComponent.h"
#include "Game/GameEntities/Text.h"
#include "Game/GameEntities/Wall.h"

#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>


using namespace Game;

GameBoard::GameBoard() : player1(nullptr), player2(nullptr), player1HealthGUI(nullptr), player2HealthGUI(nullptr),
countDownTimer(nullptr), roundTimer(nullptr), currentRoundGUI(nullptr), titleText(nullptr), startText(nullptr)
{
    buildMenuGUI();
}

GameBoard::~GameBoard()
{

}

void GameBoard::Update()
{
    //Listen for SPACE to change gameStarted
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !gameStarted){
        gameStarted = true;
        buildGame();
        buildRound(1);
        clearMenuGUIEntities();
        buildGameGUI();
        return;
    }

    if(gameStarted)
    {
        if (!roundEnded)
        {
            checkPlayersHealthState();    
        }
        else 
        {
            buildRound(currentRound);
        }

        updateRoundState();
        updateGUI();
    }

    if (gameOver) 
    {
        countDownTimer->setText("GAME OVER!");
        gameStarted = false;
    }
}

void GameBoard::updateRoundState()
{
  if(roundStartCountdown > 0){
      roundStartCountdown -= GameEngine::GameEngineMain::GetTimeDelta();
      return;
  }
  else 
  {
      player1->disableInput(false);
      player2->disableInput(false);
  }

  if(currentRoundTimer > 0){
      currentRoundTimer -= GameEngine::GameEngineMain::GetTimeDelta();
  } else {
      roundEnded = true;
      currentRound++;
  }
}

void Game::GameBoard::checkPlayersHealthState()
{
    if (player1->getPlayerHealth() <= 0 || player2->getPlayerHealth() <= 0)
    {
        gameOver = true;
    }
}

void Game::GameBoard::buildRound(int currentRound)
{
    //Initalize round states
    this->currentRound = currentRound;
    currentRoundTimer = ROUND_DURATION;
    roundStartCountdown = 4;
    roundEnded = false;

    resetPlayers();

    float screenHeight = 720.f;
    float screenWidth = 1280.f;

    switch (currentRound) 
    {
    case 1:
        break;
    case 2:
        clone1_1 = new Game::Clone(player1, player1->getReplay(), player1->getShotReplay());
        clone1_1->SetPos(sf::Vector2f(50.f, screenHeight / 2.f));
        GameEngine::GameEngineMain::GetInstance()->AddEntity(clone1_1);
        
        clone2_1 = new Game::Clone(player2, player2->getReplay(), player2->getShotReplay());
        clone2_1->SetPos(sf::Vector2f(screenWidth - 50.f, screenHeight / 2.f));
        GameEngine::GameEngineMain::GetInstance()->AddEntity(clone2_1);

        replay1 = player1->getReplay();
        replay2 = player2->getReplay();

        shotReplay1 = player1->getShotReplay();
        shotReplay2 = player2->getShotReplay();

        player1->restartRecording();
        player2->restartRecording();

        break;
    case 3:
        GameEngine::GameEngineMain::GetInstance()->RemoveEntity(clone1_1);
        GameEngine::GameEngineMain::GetInstance()->RemoveEntity(clone2_1);

        clone1_1 = new Game::Clone(player1, replay1, shotReplay1);
        clone1_1->SetPos(sf::Vector2f(50.f, screenHeight / 2.f));
        GameEngine::GameEngineMain::GetInstance()->AddEntity(clone1_1);
        
        clone2_1 = new Game::Clone(player2, replay2, shotReplay2);
        clone2_1->SetPos(sf::Vector2f(screenWidth - 50.f, screenHeight / 2.f));
        GameEngine::GameEngineMain::GetInstance()->AddEntity(clone2_1);

        clone1_2 = new Game::Clone(player1, player1->getReplay(), player1->getShotReplay());
        clone1_2->SetPos(sf::Vector2f(50.f, screenHeight / 2.f));
        GameEngine::GameEngineMain::GetInstance()->AddEntity(clone1_2);
        
        clone2_2 = new Game::Clone(player2, player2->getReplay(), player2->getShotReplay());
        clone2_2->SetPos(sf::Vector2f(screenWidth - 50.f, screenHeight / 2.f));
        GameEngine::GameEngineMain::GetInstance()->AddEntity(clone2_2);      

        break;
    default:
        break;
    }
}

void Game::GameBoard::resetPlayers()
{
    float screenHeight = 720.f;
    float screenWidth = 1280.f;

    player1->SetPos(sf::Vector2f(50.f, screenHeight / 2.f));
    player2->SetPos(sf::Vector2f(screenWidth - 50.f, screenHeight / 2.f));

    player1->clearBullets();
    player2->clearBullets();

    player1->disableInput(true);
    player2->disableInput(true);
}

void GameBoard::buildGame()
{
    //Boundary Walls
    Wall* wallTop = new Wall(sf::Vector2f(1280.0f, 40.0f), sf::Vector2f(640.0f, 20.0f));
    GameEngine::GameEngineMain::GetInstance()->AddEntity(wallTop);
    Wall* wallBot = new Wall(sf::Vector2f(1280.0f, 40.0f), sf::Vector2f(640.0f, 700.0f));
    GameEngine::GameEngineMain::GetInstance()->AddEntity(wallBot);
    Wall* wallLeft = new Wall(sf::Vector2f(40.0f, 720.0f), sf::Vector2f(20.0f, 360.0f));
    GameEngine::GameEngineMain::GetInstance()->AddEntity(wallLeft);
    Wall* wallRight = new Wall(sf::Vector2f(40.0f, 720.0f), sf::Vector2f(1260.0f, 360.0f));
    GameEngine::GameEngineMain::GetInstance()->AddEntity(wallRight);
    buildMap();

    int player1Controls[6] = { sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::Q, sf::Keyboard::E };
    int player2Controls[6] = { sf::Keyboard::Numpad1, sf::Keyboard::Numpad3, sf::Keyboard::Numpad5, sf::Keyboard::Numpad2, sf::Keyboard::Numpad4, sf::Keyboard::Numpad6 };

    player1 = new Game::Player(GameEngine::eTexture::Player1);
    player1->setControls(player1Controls);
    player1->setActionButton(sf::Keyboard::V);
    GameEngine::GameEngineMain::GetInstance()->AddEntity(player1);

    player2 = new Game::Player(GameEngine::eTexture::Player2);
    player2->SetRotation(180);
    player2->setControls(player2Controls);
    player2->setActionButton(sf::Keyboard::Enter);
    GameEngine::GameEngineMain::GetInstance()->AddEntity(player2);
}

void GameBoard::updateGUI()
{
    player1HealthGUI->setText("P1: " + std::to_string(player1->getPlayerHealth()));
    player2HealthGUI->setText("P2: " + std::to_string(player2->getPlayerHealth()));
  
    if((int)ceil(roundStartCountdown) == 1){
        countDownTimer->setText("Round Start!");
    } else if((int)ceil(roundStartCountdown) == 0) {
        //GameEngine::GameEngineMain::GetInstance()->RemoveEntity(countDownTimer);
    } else {
        countDownTimer->setText(std::to_string((int)ceil(roundStartCountdown - 1)));
    }

    roundTimer->setText(std::to_string((int)ceil(currentRoundTimer)));
    currentRoundGUI->setText("Round " + std::to_string(currentRound));
}


void GameBoard::buildMenuGUI()
{
    drawBackground();
  const std::string gameName = "BulletTime";
  const std::string startGameText = "Press Space to start!";
  float windowWidth = 1280.f;

  titleText = new Text(gameName, sf::Color::White, 75, sf::Vector2f(windowWidth/2, 50.0f));
  GameEngine::GameEngineMain::GetInstance()->AddEntity(titleText);
  startText = new Text(startGameText, sf::Color::White, 30, sf::Vector2f(windowWidth/2, 650.0f));
  GameEngine::GameEngineMain::GetInstance()->AddEntity(startText);

  
  htnText = new Text("Hack the North 2020++", sf::Color::White, 20, sf::Vector2f(windowWidth/2, 700.0f));
  GameEngine::GameEngineMain::GetInstance()->AddEntity(htnText);
  htnLogo = new GameEngine::Entity;
  GameEngine::GameEngineMain::GetInstance()->AddEntity(htnLogo);
  htnLogo -> SetPos(sf::Vector2f(windowWidth/2 - 225.0f, 700.0f));
  htnLogo -> SetSize(sf::Vector2f(30.0f, 30.0f));
  GameEngine::SpriteRenderComponent* renderhtn = htnLogo -> AddComponent<GameEngine::SpriteRenderComponent>();
  renderhtn -> SetTexture(GameEngine::eTexture::htn);
  renderhtn -> SetFillColor(sf::Color::Transparent);
}

void GameBoard::buildGameGUI() 
{
  float windowWidth = 1280.f;

  player1HealthGUI = new Text("P1: " + std::to_string(player1->getPlayerHealth()), sf::Color::White, 30, sf::Vector2f(0.0f + 3 * 30, 30.0f));
  GameEngine::GameEngineMain::GetInstance()->AddEntity(player1HealthGUI);
  player2HealthGUI = new Text("P2: " + std::to_string(player2->getPlayerHealth()), sf::Color::White, 30, sf::Vector2f(windowWidth - 3 * 30, 30.0f));
  GameEngine::GameEngineMain::GetInstance()->AddEntity(player2HealthGUI);

  countDownTimer = new Text(std::to_string((int)ceil(roundStartCountdown)), sf::Color::White, 50, sf::Vector2f(windowWidth/2, windowWidth/2));
  GameEngine::GameEngineMain::GetInstance()->AddEntity(countDownTimer);
  roundTimer = new Text(std::to_string((int)ceil(currentRoundTimer)), sf::Color::White, 50, sf::Vector2f(windowWidth/2, 150.0f));
  GameEngine::GameEngineMain::GetInstance()->AddEntity(roundTimer);
  currentRoundGUI = new Text("Round " + std::to_string(currentRound), sf::Color::White, 50, sf::Vector2f(windowWidth/2, 50.0f));
  GameEngine::GameEngineMain::GetInstance()->AddEntity(currentRoundGUI);
}

void GameBoard::clearMenuGUIEntities() 
{
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(titleText);
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(startText);
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(htnText);
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(htnLogo);
}

void GameBoard::clearGUIEntities()
{
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(player1HealthGUI);
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(player2HealthGUI);
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(countDownTimer);
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(roundTimer);
    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(currentRoundGUI);
}

void GameBoard::drawBackground()
{
  GameEngine::Entity* background = new GameEngine::Entity();
  GameEngine::GameEngineMain::GetInstance()->AddEntity(background);

  background -> SetPos(sf::Vector2f(640.0f, 360.0f));
  background -> SetSize(sf::Vector2f(1280.0f, 720.0f));

  GameEngine::SpriteRenderComponent* render = background -> AddComponent<GameEngine::SpriteRenderComponent>();
  render -> SetTexture(GameEngine::eTexture::Background);
  render -> SetFillColor(sf::Color::Transparent);
}

void GameBoard::buildMap()
{
  srand(time(0));
  const int maxBoxes = 25;
  const int xGrid = 23;
  const int yGrid = 12;

  for(int currBox = 0; currBox < maxBoxes; currBox++)
  {
    sf::Vector2f pos = sf::Vector2f((rand() % xGrid + 1) * 50.0f + 40, (rand() % yGrid + 1) * 50.0f + 40);
    Wall* mapBox = new Wall(GameEngine::eTexture::Box, sf::Vector2f(50.0f, 50.0f), pos);
    GameEngine::GameEngineMain::GetInstance()->AddEntity(mapBox);
    mapBoxes.push_back(mapBox);
  }
}

void GameBoard::setGameStarted(bool newState) {
    gameStarted = newState;
}

bool GameBoard::getGameStarted() {
    return gameStarted;
}
