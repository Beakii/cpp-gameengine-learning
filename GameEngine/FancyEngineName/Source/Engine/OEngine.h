#pragma once

class FANCY_ENGINE_API OEngine;
namespace EngineConfig {
	enum EngineMode : int {
		NONE,
		DEBUG,
		RELEASE,
		EDITOR,
		SERVER
	};

	extern OEngine g_FancyEngine;

	void FANCY_ENGINE_API SetMode(EngineMode mode);
	EngineMode FANCY_ENGINE_API GetMode();

	std::wstring FANCY_ENGINE_API EngineModeToString();
}

using namespace EngineConfig;
class FANCY_ENGINE_API OEngine {
public:
	OEngine();
	~OEngine();

private: 
	EngineMode m_engineConfig;

public:
	EngineMode GetEngineMode();
	void SetEngineMode(EngineMode mode);
};