#pragma once
#include <cstdint>

struct Config
{
	constexpr static uint32_t WINDOW_WIDTH = 1080;
	constexpr static uint32_t WINDOW_HEIGHT = 1080;
	constexpr static uint32_t fps = 30;
	constexpr static float zoomFactor = 1.1f;
};