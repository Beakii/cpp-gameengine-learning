#include "Engine.h"

namespace EngineConfig {
	OEngine g_FancyEngine;

	void SetMode(EngineMode mode)
	{
		g_FancyEngine.SetEngineMode(mode);
	}

	EngineMode GetMode() {
		return g_FancyEngine.GetEngineMode();
	}

	std::wstring EngineModeToString()
	{
		switch (g_FancyEngine.GetEngineMode())
		{
		case EngineMode::DEBUG:
			return L"DEBUG";
		case EngineMode::RELEASE:
			return L"RELEASE";
		case EngineMode::EDITOR:
			return L"EDITOR";
		case EngineMode::SERVER:
			return L"SERVER";
		default:
			return L"NONE";
		}
	}
}

OEngine::OEngine()
{
#ifdef _DEBUG
	m_engineConfig = EngineConfig::EngineMode::DEBUG;
#else
	m_engineConfig = EngineConfig::EngineMode::RELEASE;
#endif
}

OEngine::~OEngine()
{
}

EngineMode OEngine::GetEngineMode()
{
	return m_engineConfig;
}

void OEngine::SetEngineMode(EngineMode mode)
{
	m_engineConfig = mode;
}
