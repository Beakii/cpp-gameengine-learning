#include "pch.h"
#include "Application.h"
#include "Platform/Windows/WinEntry.h"

ENTRYAPP(Application)

Application::Application()
{
}

Application::~Application()
{
}

void Application::SetupGame()
{
	PerGameSettings::SetGameName(IDS_PERGAMENAME);
	PerGameSettings::SetShortName(IDS_SHORTNAME);
	PerGameSettings::SetGameIcon(IDI_MAIN_ICON);
}

void Application::Initialize()
{

}

void Application::Update()
{
}

void Application::Shutdown()
{
}
