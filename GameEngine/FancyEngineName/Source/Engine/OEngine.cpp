#include "Engine.h"

namespace EngineConfig {
	OEngine g_FancyEngine;
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
