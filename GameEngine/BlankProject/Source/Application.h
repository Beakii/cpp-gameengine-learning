#pragma once

#include "Engine/Simulation.h"

class Application : public Engine::Simulation {
public:
	Application();
	~Application();

public:
	void SetupGame();
	void Initialize();
	void Update();
	void Shutdown();
};