#include "Engine.h"
#include <ctime>
#include <sstream>
#include <iomanip>

// Get time in format 00:00:00
// Stripped = 000000
std::wstring Time::GetTime(bool stripped) {
	time_t timeNow = time(0);
	tm localTime;
	localtime_s(&localTime, &timeNow);
	std::wstringstream ss;
	ss << std::put_time(&localTime, L"%T");

	std::wstring timeString = ss.str();

	if (stripped) {
		std::wstring chars = L":";
		for (WCHAR c : chars) {
			timeString.erase(std::remove(timeString.begin(), timeString.end(), c), timeString.end());
		}
	}
	return timeString;
}

// Get date in format 00/00/00
// Stripped = 000000
std::wstring Time::GetDate(bool stripped) {
	time_t timeNow = time(0);
	tm localTime;
	localtime_s(&localTime, &timeNow);
	std::wstringstream ss;
	ss << std::put_time(&localTime, L"%d/%m/%y");

	std::wstring timeString = ss.str();

	if (stripped) {
		std::wstring chars = L"/";
		for (WCHAR c : chars) {
			timeString.erase(std::remove(timeString.begin(), timeString.end(), c), timeString.end());
		}
	}
	return timeString;
}

// Get date and time in format 00/00/00 00:00:00
// Stripped = 000000000000
std::wstring Time::GetDateTime(bool stripped) {
	std::wstring timeString = GetDate(stripped) + L" " + GetTime(stripped);

	if (stripped) {
		std::wstring chars = L" ";
		for (WCHAR c : chars) {
			timeString.erase(std::remove(timeString.begin(), timeString.end(), c), timeString.end());
		}
	}

	return timeString;
}

