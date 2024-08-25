#pragma once

#include "Platform/Windows/IApplication.h"

class Application : public IApplication {
public:
	Application();
	~Application();

public:
	void SetupGame();
	void Initialize();
	void Update();
	void Shutdown();
};