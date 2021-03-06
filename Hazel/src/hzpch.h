#pragma once

#define HZ_ENABLE_ASSERTS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <array>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Hazel/Core/Log.h"

#ifdef HZ_PLATFORM_WINDOWS
#include <Windows.h>
#endif