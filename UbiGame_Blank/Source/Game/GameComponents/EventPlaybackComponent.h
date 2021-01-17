#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <utility>

namespace Game 
{
	class EventPlaybackComponent : public GameEngine::Component
	{
	public:
		virtual void Update();
		virtual void OnAddToWorld();

		void setSamplingTime(float time) { samplingTime = time; }

		void setReplay(std::vector<std::pair<sf::Vector2f, float>>& replay) { this->replay = replay; }
		void setShotReplay(std::vector<bool>& replay) { shotReplay = replay;  }

		void restartReplay() { currentReplayIndex = 0; }

	private:
		std::vector<std::pair<sf::Vector2f, float>> replay;
		std::vector<bool> shotReplay;

		bool firePressed = false;
		bool shotshot = false;
		float samplingTime;
		int currentReplayIndex = 0;
		float time = 0.f;

		void shootBullet();
	};
}


