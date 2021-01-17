#include "CloneMovementComponent.h"
#include <GameEngine/GameEngineMain.h>

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

    GameEngine::Entity* entity = GetEntity();

    // MOVEMENT
    sf::Vector2f currentPosition = entity->GetPos();

    for (auto it = replay.begin(); it != replay.end(); it++) 
    {
        if (currentPosition == it->first && time >= samplingTime)
        {
            time = 0;
            currentReplayIndex++;
            break;
        }
    }

    if (currentReplayIndex >= replay.size()) return;

    sf::Vector2f start = currentPosition;
    sf::Vector2f end = replay[currentReplayIndex].first;
    time += dt;
    float x = lerp(start.x, end.x, time / samplingTime);
    float y = lerp(start.y, end.y, time / samplingTime);
   
    GetEntity()->SetPos(sf::Vector2f(x, y));

    // ROTATION
    float currentRotation = entity->GetRot();
    float rotation = lerp(currentRotation, replay[currentReplayIndex].second, time);
    GetEntity()->SetRotation(rotation);
}

void CloneMovementComponent::OnAddToWorld()
{
    __super::OnAddToWorld();
}