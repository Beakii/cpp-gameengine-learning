#pragma once

#define CB_CLOSE	0
#define CB_MINIMIZE 1
#define CB_MAXIMIZE 2

namespace Win32 {
	class Caption
	{
	public:
		struct CaptionButton {
			std::wstring Text = L"";
			int Command = -1;
			int Width = 50;
			RECT Rect;

			CaptionButton(std::wstring text,int command, int width = 50) {
				Text = text;
				Width = width;
				Command = command;
			}
		};

	private:
		bool m_ShowTitle = true;
		std::list<CaptionButton*> m_Buttons;

	public:
		bool ShowTitle() const { return m_ShowTitle; }
		std::list<CaptionButton*> CaptionButtons() const { return m_Buttons; }

	public:
		void SetShowTitle(bool showTitle) { m_ShowTitle = showTitle; }
		
	public:
		void AddButton(CaptionButton* button);
	};
}


