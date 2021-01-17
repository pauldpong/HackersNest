#include "EventRecordingComponent.h"
#include <GameEngine/GameEngineMain.h>


Game::EventRecordingComponent::EventRecordingComponent()
{
}

Game::EventRecordingComponent::~EventRecordingComponent()
{
}

void Game::EventRecordingComponent::Update()
{
	Component::Update();

    const float dt = GameEngine::GameEngineMain::GetTimeDelta();

    if (time >= samplingTime)
    {
        replay.push_back(std::make_pair<sf::Vector2f, float>(GetEntity()->GetPos(), GetEntity()->GetRot()));
        shotReplay.push_back(static_cast<Game::Player*>(GetEntity())->getFirePressed());
        time = 0.f;
    }
    else
    {
        time += dt;
    }
}

void Game::EventRecordingComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}

void Game::EventRecordingComponent::restartRecording() 
{
    time = 0.f;
    replay.clear();
    shotReplay.clear();
}