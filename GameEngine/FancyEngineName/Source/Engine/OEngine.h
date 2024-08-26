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
}

using namespace EngineConfig;
class FANCY_ENGINE_API OEngine {
public:
	OEngine();
	~OEngine();

private: 
	EngineMode m_engineConfig;
};