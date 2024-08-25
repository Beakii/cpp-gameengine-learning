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
	Logger::PrintDebugSeperator();
	Logger::Log(L"Initializing Application...\n");
	Logger::Log(L"Game Name: %s\n", PerGameSettings::GameName());
	Logger::Log(L"Boot Time: %s\n", Time::GetDateTime().c_str());
	Logger::PrintDebugSeperator();

	Logger::StartMTail();
}

void Application::Update()
{
}

void Application::Shutdown()
{
}
