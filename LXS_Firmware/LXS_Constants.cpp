#include "LXS_Constants.h"
#include "LXS_Macros.h"

#if LXS_HAS_LCD && LXS_LCD_PULSE
uint8 LXS_PulseBitmaps[] = {
	// Frame 1
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	// Frame 2
	0b00000,
	0b00000,
	0b00000,
	0b10000,
	0b10000,
	0b00000,
	0b00000,
	0b00000,
	// Frame 3
	0b00000,
	0b00000,
	0b10000,
	0b11000,
	0b11000,
	0b10000,
	0b00000,
	0b00000,
	// Frame 4
	0b00000,
	0b10000,
	0b11000,
	0b11100,
	0b11100,
	0b11000,
	0b10000,
	0b00000,
	// Frame 5
	0b10000,
	0b11000,
	0b11100,
	0b11110,
	0b11110,
	0b11100,
	0b11000,
	0b10000,
	// Frame 6
	0b11000,
	0b11100,
	0b11110,
	0b11111,
	0b11111,
	0b11110,
	0b11100,
	0b11000,
	// Frame 7
	0b11100,
	0b11110,
	0b11111,
	0b11110,
	0b11110,
	0b11111,
	0b11110,
	0b11100,
	// Frame 8
	0b11110,
	0b11111,
	0b11110,
	0b11100,
	0b11100,
	0b11110,
	0b11111,
	0b11110,
	// Frame 9
	0b11111,
	0b11110,
	0b11100,
	0b11000,
	0b11000,
	0b11100,
	0b11110,
	0b11111,
	// Frame 10
	0b11110,
	0b11100,
	0b11000,
	0b10000,
	0b10000,
	0b11000,
	0b11100,
	0b11110,
	// Frame 11
	0b11100,
	0b11000,
	0b10000,
	0b00000,
	0b00000,
	0b10000,
	0b11000,
	0b11100,
	// Frame 12
	0b11000,
	0b10000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b10000,
	0b11000,
	// Frame 13
	0b10000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b10000,
	// Frame 13
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	// Frame 15
	0b00000,
	0b00100,
	0b01110,
	0b11111,
	0b01110,
	0b00100,
	0b00000,
	0b00000,
	// Frame 16
	0b00000,
	0b00000,
	0b00100,
	0b01110,
	0b00100,
	0b00000,
	0b00000,
	0b00000,
	// Frame 17
	0b01000,
	0b00100,
	0b10100,
	0b01001,
	0b01010,
	0b10100,
	0b00110,
	0b10100,
	// Frame 18
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
};

const uint32 LXS_PulseBitmapFrameThresholds[LXS_PulseBitmap_FrameCount] = {
	0,
	250,
	500,
	750,
	1000,
	1250,
	1500,
	1750,
	2000,
	2250,
	2500,
	2750,
	3000,
	3250,
	3500,
	3750,
	4000,
	4250,
};

uint8 LXS_PulseBitmapGetFrameIdx(uint32 microseconds)
{
	uint32 milliseconds = LXS_MICROSECONDSTOMILLISECONDS(microseconds);
	milliseconds %= (LXS_PulseBitmapFrameThresholds[LXS_PulseBitmap_FrameCount - 1] + 1);

	uint8 frameIdx = 0;

	for (uint8 i = (LXS_PulseBitmap_FrameCount - 1); i >= 0; i--)
	{
		if (milliseconds >= LXS_PulseBitmapFrameThresholds[i])
		{
			frameIdx = i;
			break;
		}
	}

	return frameIdx;
}

uint32 LXS_PulseBitmapGetFrameOffset(uint32 microseconds)
{
	uint8 frameIdx = LXS_PulseBitmapGetFrameIdx(microseconds);
	uint32 frameOffset = (LXS_PulseBitmap_FrameStride * frameIdx);

	return frameOffset;
}

uint8 *LXS_PulseBitmapGetFramePtr(uint32 microseconds)
{
	return LXS_PulseBitmaps + LXS_PulseBitmapGetFrameOffset(microseconds);
}
#endif /* LXS_HAS_LCD && LXS_LCD_PULSE */

#if LXS_LCD_DEBUG
char* LXS_NoteStrings[] = { "C","C#","D","D#", "E","F","F#","G", "G#","A","A#","B" };
#endif