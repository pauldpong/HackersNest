#pragma once
#include "Player.h"
#include <Game/GameComponents/CloneMovementComponent.h>

namespace Game
{
	class Clone : public GameEngine::Entity
	{
	public:
		Clone(Game::Player* player, std::vector<std::pair<sf::Vector2f, float>> replay);

		void setReplay(std::vector<std::pair<sf::Vector2f, float>> replay) { cloneMovementComponent->setReplay(replay); }

	private:
		Clone() = default;

		std::vector<std::pair<sf::Vector2f, float>> replay;
		Game::Player* parent;
		Game::CloneMovementComponent* cloneMovementComponent;
		GameEngine::SpriteRenderComponent* renderComponent;
	};

}

