#include "ProjectilePhysicsComponent.h"
#include <iostream>
#include <GameEngine/GameEngineMain.h>

using namespace Game;

ProjectilePhysicsComponent::ProjectilePhysicsComponent()
{

}

ProjectilePhysicsComponent::~ProjectilePhysicsComponent()
{

}

void ProjectilePhysicsComponent::Update()
{
	__super::Update();

	const float dt = GameEngine::GameEngineMain::GetTimeDelta();
	sf::Vector2f displacement{ 0.0f, 0.0f };
	const float speedAmount = 300.0f;

	displacement.x += directionVector.x * speedAmount * dt;
	displacement.y += directionVector.y * speedAmount * dt;

	GetEntity()->SetPos(GetEntity()->GetPos() + displacement);

	updateProjectileHit();
}

void ProjectilePhysicsComponent::updateProjectileHit() 
{
	GameEngine::CollidablePhysicsComponent* colPhys = GetEntity()->GetComponent<GameEngine::CollidablePhysicsComponent>();
	if (!colPhys)
	{
		return;
	}

	if (colPhys->didCollide() && colPhys->getCollidedEntity() != nullptr)
	{
		//Remove self
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(GetEntity());
		//Remove hit entity
		GameEngine::Entity* collidedEntity = colPhys->getCollidedEntity();

		if (collidedEntity->getEntityType() == GameEngine::EntityType::PLAYER) 
		{
			Game::Player* hitPlayer = static_cast<Game::Player*>(collidedEntity);
			Game::Bullet* bullet = static_cast<Game::Bullet*>(GetEntity());

			Game::Player* bulletOwner = static_cast<Game::Player*>(bullet->getOwner());
			bulletOwner->removeBullet(bullet);

			hitPlayer->setPlayerHealth(hitPlayer->getPlayerHealth() - 20);
		}
		else if (collidedEntity->getEntityType() == GameEngine::EntityType::CLONE)
		{
			Game::Clone* clone = static_cast<Game::Clone*>(collidedEntity);
			Game::Player* hitPlayer = clone->getParent();
			Game::Bullet* bullet = static_cast<Game::Bullet*>(GetEntity());

			Game::Player* bulletOwner = static_cast<Game::Player*>(bullet->getOwner());
			bulletOwner->removeBullet(bullet);

			hitPlayer->setPlayerHealth(hitPlayer->getPlayerHealth() - 20);
		} 
		else if (collidedEntity->getEntityType() == GameEngine::EntityType::WALL)
		{
			Game::Bullet* bullet = static_cast<Game::Bullet*>(GetEntity());

			Game::Player* bulletOwner = static_cast<Game::Player*>(bullet->getOwner());
			bulletOwner->removeBullet(bullet);
		}
	}
}

void Game::ProjectilePhysicsComponent::setDirectionVector(sf::Vector2f vector)
{
	directionVector = vector;
}
