#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace Game
{
class PlayerMovementComponent : public GameEngine::Component
    {
    public:
        virtual void Update();
        virtual void OnAddToWorld();

        void setPlayerControls(int playerControls[6]);
        void disableInput(bool disable);

        std::vector<std::pair<sf::Vector2f, float>> getReplayVector() const { return replay; }

        void setSamplingTime(float time) { samplingTime = time; }
        float getSamplingTime() const { return samplingTime; }

    private:
        bool inputDisabled = false;
        int controls[6];  //0 and 1 for left right. 2 and 3 for up and down. 4 and 5 for rotate left and right.

        float samplingTime; 
        std::vector<std::pair<sf::Vector2f, float>> replay;
        float time = 0.f;
    };
}