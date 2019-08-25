#include "LXS_LCDDebugScreens.h"

#if LXS_HAS_LCD && LXS_LCD_DEBUG

LXS_LCDDebugScreen_ActiveNotes::LXS_LCDDebugScreen_ActiveNotes()
	: LXS_LCD()
{

}

void LXS_LCDDebugScreen_ActiveNotes::init()
{
	LXS_LCD::init();
}

bool LXS_LCDDebugScreen_ActiveNotes::tick(const LXS_Clock& inClock)
{
	return true;
}

void LXS_LCDDebugScreen_ActiveNotes::update(const LXS_NoteList& note)
{
	clear();

	String debugString;
	note.debugGetActiveNotes(debugString);

	if (debugString.length() < 16)
	{
		print(debugString);
	}
	else
	{
		print(debugString.substring(0, 15));
		print(debugString.substring(15));
	}
}

#endif /* LXS_HAS_LCD && LXS_LCD_DEBUG */