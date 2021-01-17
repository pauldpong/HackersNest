#include "PlayerActionComponent.h"
#include <SFML/Window/Keyboard.hpp>
#include "GameEngine/GameEngineMain.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML/Audio.hpp>
#include <iostream>


using namespace Game;

Game::PlayerActionComponent::PlayerActionComponent() : firePressed(false)
{

}

Game::PlayerActionComponent::~PlayerActionComponent()
{
}


void Game::PlayerActionComponent::Update()
{
	Component::Update();

	if (inputDisabled) return;

	if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(playerActionKey))) {
		firePressed = true;

	}
	else
	{
		if (firePressed)
		{
			spawnBullet();
		}
		firePressed = false;
	}
}

void Game::PlayerActionComponent::OnAddToWorld()
{

}

void Game::PlayerActionComponent::setPlayerAction(int action)
{
	this->playerActionKey = action;
}

void Game::PlayerActionComponent::disableInput(bool disable)
{
	inputDisabled = disable;
}

void Game::PlayerActionComponent::playPew()
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Resources/snd/pew.wav"))
		return;

	std::cout << "pew.wav:" << std::endl;
	std::cout << " " << buffer.getDuration().asSeconds() << " seconds" << std::endl;
	std::cout << " " << buffer.getSampleRate() << " samples / sec" << std::endl;
	std::cout << " " << buffer.getChannelCount() << " channels" << std::endl;


	sf::Sound sound(buffer);
	sound.play();
	while (sound.getStatus() == sf::Sound::Playing)
	{
		std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
		std::cout << std::flush;
	}
}

void PlayerActionComponent::spawnBullet()
{
	GameEngine::Entity* entity = GetEntity();
	if (entity->getEntityType() == GameEngine::EntityType::PLAYER)
	{
		playPew();
		Game::Player* player = static_cast<Game::Player*>(GetEntity());
		Game::Bullet* bullet = new Game::Bullet();

		player->addBullet(bullet);
		bullet->setOwner(player);

		float rotation = GetEntity()->GetRot();
		sf::Vector2f playerFacingUnitVector = sf::Vector2f(cos(rotation / 180 * M_PI), sin(rotation / 180 * M_PI));

		bullet->SetPos(player->GetPos() + sf::Vector2f(playerFacingUnitVector.x * player->GetSize().x, playerFacingUnitVector.y * player->GetSize().y));

		bullet->setDirectionVector(playerFacingUnitVector);
		GameEngine::GameEngineMain::GetInstance()->AddEntity(bullet);
	}


}
