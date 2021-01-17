#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <utility>

namespace Game 
{
	class CloneMovementComponent : public GameEngine::Component
	{
	public:
		virtual void Update();
		virtual void OnAddToWorld();

		void setSamplingTime(float time) { samplingTime = time; }
		void setReplay(std::vector<std::pair<sf::Vector2f, float>> replay);

	private:
		std::vector<std::pair<sf::Vector2f, float>> replay;

		float samplingTime;
		int currentReplayIndex = 0;
		float time = 0.f;
	};
}


