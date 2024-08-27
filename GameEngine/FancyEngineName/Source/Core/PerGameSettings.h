#pragma once

class FANCY_ENGINE_API PerGameSettings {
private:
	static PerGameSettings* instance;

	static PerGameSettings* Instance() { return instance; }

public:
	PerGameSettings();
	~PerGameSettings();

private:
	WCHAR m_GameName[MAX_NAME_STRING];
	WCHAR m_ShortName[MAX_NAME_STRING];
	HICON m_GameIcon;
	WCHAR m_BootTime[MAX_NAME_STRING];
	WCHAR m_splashUrl[MAX_NAME_STRING];

public:
	static WCHAR* GameName() { return instance->m_GameName; }
	static void SetGameName(UINT id) { LoadString(HInstance(), id, instance->m_GameName, MAX_NAME_STRING); }

	static WCHAR* ShortName() { return instance->m_ShortName; }
	static void SetShortName(UINT id) { LoadString(HInstance(), id, instance->m_ShortName, MAX_NAME_STRING); }

	static HICON GameIcon() { return instance->m_GameIcon; }
	static void SetGameIcon(UINT id) { LoadIcon(HInstance(), MAKEINTRESOURCE(id)); }

	static WCHAR* BootTime() { return instance->m_BootTime; }

	static WCHAR* GameSplashURL() { return instance->m_splashUrl; }
	static void SetSplashURL(UINT id) { LoadString(HInstance(), id, instance->m_splashUrl, MAX_NAME_STRING); }
};