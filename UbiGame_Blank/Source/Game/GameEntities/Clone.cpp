#include "Clone.h"
#include <iostream>

using namespace Game;

Game::Clone::Clone(Game::Player* player, std::vector<std::pair<sf::Vector2f, float>>& replay) : parent(player), replay(replay)
{
	setEntityType(GameEngine::EntityType::CLONE);
	SetSize(sf::Vector2f(50.0f, 50.0f));
	renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	renderComponent->SetTexture(GameEngine::eTexture::Player1);
	renderComponent->SetFillColor(sf::Color::Transparent);

	eventPlaybackComponent = AddComponent<Game::EventPlaybackComponent>();
	eventPlaybackComponent->setReplay(replay);
	eventPlaybackComponent->setShotReplay(player->getShotReplay());
	eventPlaybackComponent->setSamplingTime(player->getSamplingTime());
}