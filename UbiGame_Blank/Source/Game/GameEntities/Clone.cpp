#include "Clone.h"
#include <iostream>

using namespace Game;

Game::Clone::Clone(Game::Player* player, std::vector<std::pair<sf::Vector2f, float>>& replay, std::vector<bool>& shotReplay) : parent(player), replay(replay), shotReplay(shotReplay)
{
	setEntityType(GameEngine::EntityType::CLONE);
	SetSize(sf::Vector2f(50.0f, 50.0f));
	renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	renderComponent->SetTexture(player->getTexture());
	renderComponent->SetFillColor(sf::Color::Color(255, 255, 255, 40));

	eventPlaybackComponent = AddComponent<Game::EventPlaybackComponent>();
	eventPlaybackComponent->setReplay(replay);
	eventPlaybackComponent->setShotReplay(shotReplay);
	eventPlaybackComponent->setSamplingTime(player->getSamplingTime());
}