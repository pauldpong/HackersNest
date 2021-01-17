#include "Clone.h"
#include <iostream>

using namespace Game;

Game::Clone::Clone(Game::Player* player, std::vector<std::pair<sf::Vector2f, float>> replay)
{
	renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	renderComponent->SetTexture(GameEngine::eTexture::Player1);
	renderComponent->SetFillColor(sf::Color::Transparent);

	cloneMovementComponent = AddComponent<Game::CloneMovementComponent>();
	cloneMovementComponent->setReplay(replay);
	std::cout << player->getReplayVector().size() << std::endl;
	cloneMovementComponent->setSamplingTime(player->getSamplingTime());
}
