#pragma once
#include <chrono>

#include "Singleton.h"


class PerformanceMonitor: public Singleton<PerformanceMonitor>
{

public:
	void Initialise()
	{
		ComputeFrameTime();
	}


	void ComputeFrameTime()
	{
		auto astFrameUpdateTime = std::chrono::high_resolution_clock::now();

		m_deltaTime = std::chrono::duration<float, std::milli>(astFrameUpdateTime - m_lastFrameUpdateTime).count() / 1000.0f;

		m_lastFrameUpdateTime = astFrameUpdateTime;
	}


	float GetFPS()
	{
		return 1.0f / m_deltaTime;
	}

	float GetDeltaTime()
	{
		return m_deltaTime;
	}


private:
	float m_deltaTime = 0.0f;

	std::chrono::steady_clock::time_point m_lastFrameUpdateTime;
};

