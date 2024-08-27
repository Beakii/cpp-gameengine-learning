#include "Engine.h"
#include "Simulation.h"
#include "SplashScreen.h"

Engine::Simulation::Simulation()
{
}

Engine::Simulation::~Simulation()
{
}

void Engine::Simulation::PreInitialize()
{
	Logger::PrintDebugSeperator();
	Logger::Log(L"Initializing Application...\n");
	Logger::Log(L"Game Name: %s\n", PerGameSettings::GameName());
	Logger::Log(L"Boot Time: %s\n", Time::GetDateTime().c_str());
	Logger::Log(L"Engine Mode: %s\n", EngineConfig::EngineModeToString().c_str());
	Logger::PrintDebugSeperator();

	SplashScreen::Open();
}
