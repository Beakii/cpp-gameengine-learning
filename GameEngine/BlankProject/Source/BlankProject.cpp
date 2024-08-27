#include "BlankProject.h"
#include "Engine/Simulation.h"
#include "Platform/Windows/WinEntry.h"

class BlankProject : public Engine::Simulation {
public:
	BlankProject() {}
	~BlankProject() {}

public:
	void SetupGame();
	void Initialize() {}
	void Update() {}
	void Shutdown() {}
};


ENTRYAPP(BlankProject)

void BlankProject::SetupGame()
{
	PerGameSettings::SetGameName(IDS_PERGAMENAME);
	PerGameSettings::SetShortName(IDS_SHORTNAME);
	PerGameSettings::SetGameIcon(IDI_MAIN_ICON);
	PerGameSettings::SetSplashURL(IDS_SPLASHURL);
}

