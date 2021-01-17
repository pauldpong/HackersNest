#include "CloneMovementComponent.h"
#include <GameEngine/GameEngineMain.h>
#include <iostream>
#include <cassert>

using namespace Game;

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

void CloneMovementComponent::setReplay(std::vector<std::pair<sf::Vector2f, float>> replay)
{
	this->replay = replay;
}

void CloneMovementComponent::Update()
{
    __super::Update();

    const float dt = GameEngine::GameEngineMain::GetTimeDelta();

    sf::Vector2f displacement{ 0.0f, 0.0f };
    const float speedAmount = 250.0f;

    GameEngine::Entity* entity = GetEntity();
    sf::Vector2f currentPosition = entity->GetPos();

    for (auto it = replay.begin(); it != replay.end(); it++) 
    {
        if (currentPosition == it->first)
        {
            currentReplayIndex++;
            break;
        }
    }

    sf::Vector2f start = currentPosition;
    sf::Vector2f end = replay[currentReplayIndex].first;
    time += dt;
    float x = lerp(start.x, end.x - start.x, time);
    float y = lerp(start.y, end.y - start.y, time);
    

    std::cout << x << " " << y << " " << time << std::endl;
    GetEntity()->SetPos(sf::Vector2f(x, y));
   
    //GetEntity()->SetRotation(GetEntity()->GetRot() + rotation);
}

void CloneMovementComponent::OnAddToWorld()
{
    __super::OnAddToWorld();
}