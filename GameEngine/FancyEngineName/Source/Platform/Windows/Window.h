#pragma once

#include "SubObject.h"

namespace Win32 {
	class FANCY_ENGINE_API Window : public Win32::SubObject {
	public:
		Window(std::wstring className, std::wstring classTitle, HICON icon, INT width, INT height);
		~Window();

		virtual void Initialize() override;

	protected:
		INT		m_Height;
		INT		m_Width;
	};
}