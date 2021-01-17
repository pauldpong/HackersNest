#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include <Game/GameComponents/PlayerMovementComponent.h>
#include <Game/GameComponents/PlayerActionComponent.h>
#include <Game/GameComponents/EventRecordingComponent.h>

namespace Game 
{
	class Player : public GameEngine::Entity
	{
	public:
		Player(GameEngine::eTexture::type texture);
		virtual void OnAddToWorld();
		virtual void OnRemoveFromWorld();

		virtual void Update();

		void setControls(int controls[4]);
		void setActionButton(int actionButton);

		int getPlayerHealth() const { return playerHealth; }
		void setPlayerHealth(int health) { playerHealth = health; }

		void disableInput(bool disable);

		void addBullet(Game::Bullet* bullet);
		void removeBullet(Game::Bullet* bullet);
		void clearBullets();

		bool getFirePressed() const { return actionComponent->getFirePressed(); }

		float getSamplingTime() const { return recordingComponent->getSamplingTime(); }
		void restartRecording();
		std::vector<std::pair<sf::Vector2f, float>>& getReplay() { return recordingComponent->getReplay(); };
		std::vector<bool>& getShotReplay() { return recordingComponent->getShotReplay(); }

		GameEngine::eTexture::type getTexture()
		{
			return texture;
		};

	private:
		int playerHealth;

		std::vector<Game::Bullet*> bullets;
		GameEngine::eTexture::type texture;

		// Components 
		Game::PlayerMovementComponent* movementComponent;
		Game::PlayerActionComponent* actionComponent;
		Game::EventRecordingComponent* recordingComponent;
		GameEngine::SpriteRenderComponent* renderComponent;
	};
}
