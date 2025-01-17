#include "Player.h"
#include "GameEngine/EntitySystem/Components/RenderComponent.h"
#include <Game/GameComponents/PlayerActionComponent.h>
#include <GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h>
#include <GameEngine/GameEngineMain.h>

#include <algorithm>

Game::Player::Player(GameEngine::eTexture::type texture) : playerHealth(100), texture(texture)
{
	setEntityType(GameEngine::EntityType::PLAYER);
	SetSize(sf::Vector2f(50.0f, 50.0f));

	//Render Sprite
	renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	renderComponent -> SetTexture(texture);
	renderComponent -> SetFillColor(sf::Color::Transparent);

	AddComponent<GameEngine::CollidablePhysicsComponent>();
	actionComponent = AddComponent<Game::PlayerActionComponent>();
	movementComponent = AddComponent<Game::PlayerMovementComponent>();

	recordingComponent = AddComponent<Game::EventRecordingComponent>();
	recordingComponent->setSamplingTime(1.f / 60.f);
}

void Game::Player::setControls(int controls[4]) 
{
	movementComponent->setPlayerControls(controls);
}

void Game::Player::setActionButton(int actionButton)
{
	actionComponent->setPlayerAction(actionButton);
}

void Game::Player::disableInput(bool disable)
{
	actionComponent->disableInput(disable);
	movementComponent->disableInput(disable);
}

void Game::Player::addBullet(Game::Bullet* bullet)
{
	bullets.push_back(bullet);
}

void Game::Player::removeBullet(Game::Bullet* bullet)
{
	auto it = std::find(bullets.begin(), bullets.end(), bullet);

	if (it != bullets.end())
	{
		bullets.erase(it);
	}
}

void Game::Player::clearBullets()
{
	for (auto it = bullets.begin(); it != bullets.end(); it++)
	{
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(*it);
	}

	bullets.clear();
}

void Game::Player::restartRecording()
{
	recordingComponent->restartRecording();
}

void Game::Player::OnAddToWorld() 
{
	Entity::OnAddToWorld();
}

void Game::Player::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}

void Game::Player::Update()
{
	Entity::Update();
}