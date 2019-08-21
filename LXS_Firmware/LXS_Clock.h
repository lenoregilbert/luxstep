#ifndef _LXS_CLOCK_H_
#define _LXS_CLOCK_H_

#include "LXS_Config.h"
#include "LXS_Types.h"

class LXS_Time
{
public:
	LXS_Time();
	
	void init(const uint32 inMillis, const uint32 inMicros);

	void update(const uint32 inMillis, const uint32 inMicros);
	void deltaUpdate(const uint32 inDeltaMillis, const uint32 inDeltaMicros);

public:
	uint32 milliseconds;
	uint32 deltaMilliseconds;

	uint32 microseconds;
	uint32 deltaMicroseconds;
};

namespace LXS_ClockSource
{
	enum Enum
	{
		Uninitialized,
		Internal,
		MIDI,
		Count
	};
}

namespace LXS_SyncType
{
	enum Enum
	{
		Uninitialized,
		Free,
		Beat,
		TrigReset,
		ReTrigReset,
		Count
	};
}

namespace LXS_EventType
{
	enum Enum
	{
		Uninitialized,
		Note,
		Beat,
		Clock,
		Start,
		Stop,
		Count
	};
}

class LXS_Clock
{
public:
	LXS_Clock();

	void init(const LXS_ClockSource::Enum inSource, const LXS_SyncType::Enum inSync);
	bool tick();

	void notify(const LXS_EventType::Enum inEvent, const uint32 inParam);

	LXS_Time systemTime;
	LXS_Time activeTime;

private:
	LXS_ClockSource::Enum clockSource;
	LXS_SyncType::Enum syncType;

};

#endif /* _LXS_CLOCK_H_ */
