#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Windows/WinEntry.h"
#include <iostream>

class BlankProject : public Engine::Simulation {
public:
	BlankProject() {}
	~BlankProject() {}

public:
	void SetupGame();
	void Initialize();
	void Update();
	void Shutdown();
};


ENTRYAPP(BlankProject)

void BlankProject::SetupGame()
{
	PerGameSettings::SetGameName(IDS_PERGAMENAME);
	PerGameSettings::SetShortName(IDS_SHORTNAME);
	PerGameSettings::SetGameIcon(IDI_MAIN_ICON);
	PerGameSettings::SetSplashURL(IDS_SPLASHURL);
}

void BlankProject::Initialize()
{
	std::cout << "Initializing Game..." << std::endl;
}

void BlankProject::Update() 
{
	std::cout << "Run every game frame?" << std::endl;
}

void BlankProject::Shutdown()
{
	std::cout << "Shutting down game..." << std::endl;
}

