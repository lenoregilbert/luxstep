#ifndef LXS_NOTE_H_
#define LXS_NOTE_H_

#include "LXS_Types.h"
#include "LXS_Debug.h"

class LXS_Note
{
public:
	inline LXS_Note();
	inline LXS_Note(const uint32 inMicros, const uint8 inChannel, const uint8 inPitch, const uint8 inVelocity = LXS_NOTE_VELOCITY_MAX);
	inline LXS_Note(const LXS_Note& inB);

	inline uint32 release(const uint32 inMicros);

	inline LXS_Note& operator= (const LXS_Note& inB);

	union
	{
		uint32 packed;
		struct
		{
			uint8 channel : 4;
			uint8 pitch : 8;
			uint8 velocity : 7;
			bool  active : 1;
			uint8 param : 8;
			uint8 reserved : 4;
		};
	};

	uint32 micros;
};

inline LXS_Note::LXS_Note()
{
	active = false;
	micros = 0;
}

inline LXS_Note::LXS_Note(const uint32 inMicros, const uint8 inChannel, const uint8 inPitch, const uint8 inVelocity /* = LXS_NOTE_VELOCITY_MAX */)
{
	channel = inChannel;
	pitch = inPitch;
	velocity = inVelocity;
	micros = inMicros;
	active = true;
}

inline LXS_Note::LXS_Note(const LXS_Note& inB)
{
	packed = inB.packed;
	micros = inB.micros;
	active = inB.active;
}

inline uint32 LXS_Note::release(const uint32 inMicros)
{
	micros = (inMicros - micros);
	active = false;

	return micros;
}

inline LXS_Note& LXS_Note::operator= (const LXS_Note& inB)
{
	packed = inB.packed;
	micros = inB.micros;
	active = inB.active;

	return *this;
}

#endif /* LXS_NOTE_H_ */
