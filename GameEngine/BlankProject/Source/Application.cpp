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

void Application::Initialize()
{
	MessageBox(NULL, L"Hello World!", L"Hello", MB_OK);
}

void Application::Update()
{
	MessageBox(NULL, L"Loop", L"Hello", MB_OK);
}

void Application::Shutdown()
{
}
