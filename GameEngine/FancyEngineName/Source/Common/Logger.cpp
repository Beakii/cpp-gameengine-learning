#include "Engine.h"
#include <fstream>
#include <Shlobj.h>
#include <cstdio>
#include <tlhelp32.h>

Logger* Logger::instance;

Logger::Logger()
{
	instance = this;
}

Logger::~Logger()
{
}

void Logger::Log(const WCHAR* message, ...)
{
	va_list args;
	WCHAR buffer[4096];

	va_start(args, message);
	vswprintf_s(buffer, message, args);
	va_end(args);

	OutputDebugString(buffer);

	std::wfstream outfile;

	outfile.open(std::wstring(LogDirectory() + L"/" + LogFile()), std::ios_base::app);

	if (outfile.is_open()) {
		std::wstring s = buffer;
		outfile << L"[" << Time::GetDateTime() << L"]  " << s;
		outfile.close();
		OutputDebugString(s.c_str());
	}
	else {
		MessageBox(NULL, L"Unable to open log file...", L"Log Error", MB_OK);
	}

}

std::wstring Logger::LogDirectory()
{
	WCHAR path[1024] = { 0 };
	WCHAR* appData;
	
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &appData);
	wcscpy_s(path, appData);
	wcscat_s(path, L"\\");
	wcscat_s(path, PerGameSettings::GameName());
	CreateDirectory(path, NULL);
	wcscat_s(path, L"\\Log");
	CreateDirectory(path, NULL);
	return path;
}

std::wstring Logger::LogFile()
{
	WCHAR File[1024] = { 0 };
	wcscpy_s(File, PerGameSettings::GameName());
	wcscat_s(File, PerGameSettings::BootTime());
	wcscat_s(File, L".log");
	return File;
}

void Logger::PrintDebugSeperator()
{
	std::wstring s = L"\n----------------------------------------------------------\n\n";

#ifdef _DEBUG
	std::wfstream outfile;
	outfile.open(std::wstring(LogDirectory() + L"/" + LogFile()), std::ios_base::app);

	if (outfile.is_open())
	{
		outfile << s;
		outfile.close();
	}
	else {
		MessageBox(NULL, L"Unable to open log file...", L"Log Error", MB_OK);
	}
#endif
}

bool Logger::IsMTailRunning() {
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry)) {
		while (Process32Next(snapshot, &entry)) {
			if (!_wcsicmp(entry.szExeFile, L"mTAIL.exe")) {
				exists = true;
				break;
			}
		}
	}

	return exists;
}

void Logger::StartMTail() {
	if (IsMTailRunning()) {
		Logger::Log(L"--MTail Already Running--");
		return;
	}

	Logger::Log(L"--Starting MTail--");
	WCHAR path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path);
	std::wstring url = path + std::wstring(L"/mTAIL.exe");
	std::wstring params = L" \"" + LogDirectory() + L"/" + LogFile() + L"\" /start";
	ShellExecute(0, NULL, url.c_str(), params.c_str(), NULL, SW_SHOWDEFAULT);
}