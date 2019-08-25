#include "LXS_LCD.h"

#if LXS_HAS_LCD

LXS_LCD::LXS_LCD()
	: LiquidCrystal(LXS_LCD_PINS)
	, curCol(0)
	, curRow(0)
{

}

void LXS_LCD::init()
{
	begin(16, 2);
	noBlink();
	display();

#if LXS_LCD_PULSE
	curPulseFramePtr = LXS_PulseBitmapGetFramePtr(0);
	createChar(LXS_PulseBitmap_Blank, curPulseFramePtr);
#endif

	clear();
}

bool LXS_LCD::tick(const LXS_Clock& inClock)
{
#if LXS_LCD_PULSE
	uint8* curFrame = LXS_PulseBitmapGetFramePtr(inClock.systemTime.microseconds);

	if (curFrame != curPulseFramePtr)
	{
		curPulseFramePtr = curFrame;
		createChar(LXS_PulseBitmap_Char, curPulseFramePtr);
	}

	setCursor(15, 1);
	write(uint8(LXS_PulseBitmap_Char));
#endif

	return true;
}

void LXS_LCD::clear()
{
	curCol = 0;
	curRow = 0;

	LiquidCrystal::clear();
}

uint8 LXS_LCD::print(const String& inString)
{
	setCursor(curCol, curRow);

	uint8 count = LiquidCrystal::print(inString);
	curCol += count;

	if (curCol >= 12)
	{
		curCol = 0;
		curRow++;

		if (curRow >= 2)
		{
			clear();
			curRow = 0;
		}
	}

	return count;
}


#endif /* LXS_HAS_LCD */