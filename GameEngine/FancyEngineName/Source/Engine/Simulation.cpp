#include "Engine.h"
#include "Simulation.h"
#include "SplashScreen.h"

namespace Engine {
	Simulation::Simulation()
		: Win32::Window(L"Main Application", NULL, Win32::WindowType::RESIZEABLE)
	{
	}

	Simulation::~Simulation()
	{
	}

	void Simulation::PreInitialize()
	{
		Logger::PrintDebugSeperator();
		Logger::Log(L"Initializing Application...\n");
		Logger::Log(L"Game Name: %s\n", PerGameSettings::GameName());
		Logger::Log(L"Boot Time: %s\n", Time::GetDateTime().c_str());
		Logger::Log(L"Engine Mode: %s\n", EngineConfig::EngineModeToString().c_str());
		Logger::PrintDebugSeperator();

		SplashScreen::Open();

		Win32::Window::RegisterNewClass();
		Win32::Window::Initialize();
	}

	LRESULT Simulation::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message) {

		}
		return Window::MessageHandler(hWnd, message, wParam, lParam);
	}
}