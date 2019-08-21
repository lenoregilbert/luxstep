#include "LXS_Clock.h"

LXS_Time::LXS_Time()
	: milliseconds(0)
	, deltaMilliseconds(0)
	, microseconds(0)
	, deltaMicroseconds(0)
{

}

void LXS_Time::init(const uint32 inMillis, const uint32 inMicros)
{
	milliseconds = inMillis;
	microseconds = inMicros;

	deltaMilliseconds = deltaMicroseconds = 0;
}

void LXS_Time::update(const uint32 inMillis, const uint32 inMicros)
{
	deltaMilliseconds = inMillis - milliseconds;
	milliseconds = inMillis;

	deltaMicroseconds = inMicros - microseconds;
	microseconds = inMicros;
}

void LXS_Time::deltaUpdate(const uint32 inDeltaMillis, const uint32 inDeltaMicros)
{
	deltaMilliseconds = inDeltaMillis;
	milliseconds += inDeltaMillis;

	deltaMicroseconds = inDeltaMicros;
	microseconds += inDeltaMicros;
}

LXS_Clock::LXS_Clock()
	: clockSource(LXS_ClockSource::Uninitialized)
	, syncType(LXS_SyncType::Uninitialized)
{

}

void LXS_Clock::init(const LXS_ClockSource::Enum source, const LXS_SyncType::Enum sync)
{
	clockSource = source;
	syncType = sync;

	systemTime.init(millis(), micros());
	activeTime.init(0, 0);
}

bool LXS_Clock::tick()
{
	systemTime.update(millis(), micros());
	activeTime.deltaUpdate(systemTime.deltaMilliseconds, systemTime.deltaMicroseconds);
}

void LXS_Clock::notify(const LXS_EventType::Enum inEvent, const uint32 inParam)
{
	switch (inEvent)
	{
		case LXS_EventType::Note:
		{
			if (syncType == LXS_SyncType::ReTrigReset ||
			    (syncType == LXS_SyncType::TrigReset && inParam)) // Note On
			{
				activeTime.init(0, 0);
			}

			break;
		}
		case LXS_EventType::Beat:
		case LXS_EventType::Clock:
		case LXS_EventType::Start:
		case LXS_EventType::Stop:
		default:
		{
			break;
		}
	}
}