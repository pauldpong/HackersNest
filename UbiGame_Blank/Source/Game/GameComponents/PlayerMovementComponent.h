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
    private:
        bool inputDisabled = false;
        int controls[6];  //0 and 1 for left right. 2 and 3 for up and down. 4 and 5 for rotate left and right.
    };
}