#include "EventPlaybackComponent.h"
#include <GameEngine/GameEngineMain.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Game;

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

void EventPlaybackComponent::Update()
{
    Component::Update();

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

    // PLAYER ACTION
    bool didPlayerShoot = shotReplay[currentReplayIndex];

    if (didPlayerShoot)
    {
        firePressed = true;
    }
    else 
    {
        shotshot = false;
    }

    if (firePressed && !shotshot)
    {
        shootBullet();
        shotshot = true;
    }

    firePressed = false;
}

void EventPlaybackComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}

void Game::EventPlaybackComponent::shootBullet()
{
    GameEngine::Entity* entity = GetEntity();
    if (entity->getEntityType() == GameEngine::EntityType::CLONE)
    {
        Game::Clone* clone = static_cast<Game::Clone*>(GetEntity());
        Game::Player* player = clone->getParent();
        Game::Bullet* bullet = new Game::Bullet();

        player->addBullet(bullet);
        bullet->setOwner(player);

        float rotation = GetEntity()->GetRot();
        sf::Vector2f playerFacingUnitVector = sf::Vector2f(cos(rotation / 180 * M_PI), sin(rotation / 180 * M_PI));

        bullet->SetPos(clone->GetPos() + sf::Vector2f(playerFacingUnitVector.x * clone->GetSize().x, playerFacingUnitVector.y * clone->GetSize().y));

        bullet->setDirectionVector(playerFacingUnitVector);
        GameEngine::GameEngineMain::GetInstance()->AddEntity(bullet);
    }
}

