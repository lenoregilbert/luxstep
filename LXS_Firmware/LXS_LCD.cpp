#include "LXS_LCD.h"

#if LXS_HAS_LCD

LXS_LCD::LXS_LCD()
	: LCDKeypad()
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
	createChar(LXS_PulseBitmap_Blank, LXS_PulseBitmapGetFramePtr(0));
#endif

	clear();
}

bool LXS_LCD::tick(const LXS_Clock& inClock)
{
#if LXS_LCD_PULSE
	createChar(LXS_PulseBitmap_Char, LXS_PulseBitmapGetFramePtr(inClock.systemTime.microseconds));

	setCursor(15, 1);
	write(uint8(LXS_PulseBitmap_Char));
#endif

	return true;
}

void LXS_LCD::clear()
{
	curCol = 0;
	curRow = 0;

	LCDKeypad::clear();
}

uint8 LXS_LCD::print(const String& inString)
{
	setCursor(curCol, curRow);

	curCol += LCDKeypad::print(inString);

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
}


#endif /* LXS_HAS_LCD */