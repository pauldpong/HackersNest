#include "Clone.h"
#include <iostream>

using namespace Game;

Game::Clone::Clone(Game::Player* player)
{
	renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	renderComponent->SetTexture(GameEngine::eTexture::Player1);
	renderComponent->SetFillColor(sf::Color::Transparent);

	cloneMovementComponent = AddComponent<Game::CloneMovementComponent>();
	cloneMovementComponent->setReplay(player->getReplayVector());
	std::cout << player->getReplayVector().size() << std::endl;
	cloneMovementComponent->setSamplingTime(player->getSamplingTime());
}
