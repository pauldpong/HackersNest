#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <utility>

namespace Game
{
	class EventRecordingComponent : public GameEngine::Component
	{
	public:
		EventRecordingComponent();
		virtual ~EventRecordingComponent();

		virtual void Update();
		virtual void OnAddToWorld();

		void setSamplingTime(float time) { samplingTime = time; }
		float getSamplingTime() const { return samplingTime; }

		std::vector<std::pair<sf::Vector2f, float>>& getReplay() { return replay; }
		std::vector<bool>& getShotReplay() { return shotReplay; }

		void restartRecording();

	private:
		std::vector<std::pair<sf::Vector2f, float>> replay;
		std::vector<bool> shotReplay;

		float samplingTime = 1.f / 60.f;
		float time = 0.f;
	};
}