#pragma once
#include <chrono>


class Event
{
public:
	// The trigger function called when the event is executed
	virtual void Update() = 0;

	void SetID(int id)
	{
		m_id = id;
	}

	int GetID() const
	{
		return m_id;
	}

	void Destroy()
	{
		m_isDestroyed = true;
	}

	bool IsDestroyed() const
	{
		return m_isDestroyed;
	}

protected:
	std::time_t GetTimestampMS() 
	{
		using namespace std::chrono;
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}

private:
	int m_id = 0;
	bool m_isDestroyed = false;
};



// One time Event which is triggered after the amount of milliseconds set
// It is destroyed after the trigger
class DelayedEvent : public Event
{
public:
	virtual void Trigger() = 0;

	DelayedEvent(std::time_t triggerDelay) 
	{
		SetTriggerDelay(triggerDelay);
	}

	void Update() override
	{
		if (m_triggerTimestamp < GetTimestampMS())
		{
			Trigger();
			Destroy();
		}
	}

	void SetTriggerDelay(std::time_t triggerDelayMs)
	{
		m_triggerDelay = triggerDelayMs;
		UpdateTriggerTimestamp();
	}


private:
	void UpdateTriggerTimestamp()
	{
		m_triggerTimestamp = m_triggerDelay + GetTimestampMS();
	}

private:
	std::time_t m_triggerDelay = 0;
	std::time_t m_triggerTimestamp = 0;
};


// Recursive Event triggered periodically based on the amount of milliseconds set 
class LoopEvent : public Event
{
public:
	virtual void Trigger() = 0;

	LoopEvent(std::time_t loopInterval) : m_loopInterval(loopInterval)
	{
	}


	void Update() override
	{
		const auto nowTimestamp = GetTimestampMS();

		if (m_lastLoopTime < nowTimestamp)
		{
			Trigger();
			m_lastLoopTime = nowTimestamp + m_loopInterval;
		}
	}

	void SetLoopInterval(std::time_t intervalMs)
	{
		m_loopInterval = intervalMs;
	}

	std::time_t GetLoopInterval() const
	{
		return m_loopInterval;
	}

private:
	std::time_t m_loopInterval = 0; // ms
	std::time_t m_lastLoopTime = 0;
};
