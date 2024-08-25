#pragma once

#include <string>

namespace Time {
	std::wstring FANCY_ENGINE_API GetTime(bool stripped = false);

	std::wstring FANCY_ENGINE_API GetDate(bool stripped = false);

	std::wstring FANCY_ENGINE_API GetDateTime(bool stripped = false);
}