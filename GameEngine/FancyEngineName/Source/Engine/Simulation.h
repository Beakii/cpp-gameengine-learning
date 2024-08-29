#pragma once

namespace Engine {
	class FANCY_ENGINE_API Simulation : public Win32::IApplication, public Win32::Window {
	public:
		Simulation();
		~Simulation();

		virtual void PreInitialize() override;

		virtual LRESULT MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	
	};
}