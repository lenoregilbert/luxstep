#ifndef _LXS_SEQUENCE_H_
#define _LXS_SEQUENCE_H_

#include "LXS_Config.h"
#include "LXS_Types.h"

#include <MIDI.h>

#include "LXS_NoteList.h"
#include "LXS_Clock.h"

class LXS_Sequence
{
public:
	LXS_Sequence(const uint16 inNotelistSize);
	~LXS_Sequence();

	void init();
	bool tick(const LXS_Clock& inClock);

	inline void handleNoteOn(const LXS_Clock& inClock, const uint8 inChannel, const uint8 inNote, const uint8 inVelocity);
	inline void handleNoteOff(const LXS_Clock& inClock, const uint8 inChannel, const uint8 inNote, const uint8 inVelocity);

//private:
	LXS_NoteList noteList;
};

inline void LXS_Sequence::handleNoteOn(const LXS_Clock& inClock, const uint8 inChannel, const uint8 inPitch, const uint8 inVelocity)
{
	noteList.add(LXS_Note(inClock.systemTime.microseconds, inChannel, inPitch, inVelocity));
}

inline void LXS_Sequence::handleNoteOff(const LXS_Clock& inClock, const uint8 inChannel, const uint8 inPitch, const uint8 inVelocity)
{
	noteList.release(inClock.systemTime.microseconds, inChannel, inPitch);
	noteList.remove(inChannel, inPitch);
}

#endif /* _LXS_SEQUENCE_H_ */