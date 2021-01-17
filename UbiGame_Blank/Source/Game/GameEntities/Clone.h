#pragma once
#include <Game/GameComponents/EventPlaybackComponent.h>
#include <Game/GameEntities/Player.h>

namespace Game
{
	class Clone : public GameEngine::Entity
	{
	public:
		Clone(Game::Player* player, std::vector<std::pair<sf::Vector2f, float>>& replay, std::vector<bool>& shotReplay);

		Game::Player* getParent() const { return parent; }
	private:
		Clone() = default;

		std::vector<std::pair<sf::Vector2f, float>> replay;
		std::vector<bool> shotReplay;
		Game::Player* parent;
		Game::EventPlaybackComponent* eventPlaybackComponent;
		GameEngine::SpriteRenderComponent* renderComponent;
	};

}

