#pragma once

#define ENTRYAPP(x) Win32::IApplication* CreateApplication() { return new x(); }

namespace Win32 {
	class FANCY_ENGINE_API IApplication {
	public:
		IApplication();
		virtual ~IApplication() {};

	public:
		virtual void SetupGame() = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;
	};

	IApplication* CreateApplication();
}

