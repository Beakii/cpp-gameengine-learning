#include "Engine.h"
#include "w32Caption.h"

namespace Win32 {
	void Caption::AddButton(CaptionButton* button) {
		m_Buttons.push_back(button);
	}
}