#pragma once

#include "Platform/Windows/IApplication.h"

namespace Engine {
	class FANCY_ENGINE_API Simulation : public Win32::IApplication {
	public:
		Simulation();
		~Simulation();
	
	};
}