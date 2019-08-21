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
	if(LXS_LCD::tick(inClock))
	{
#if 0
		lcd->setCursor(0, 0);
		lcd->print(LXS_PSM::psmStates[4], BIN);
#elif 0
		lcd->setCursor(3, 0);
		lcd->print(LXS_PSM::psmStates[1], HEX);
		lcd->setCursor(6, 0);
		lcd->print(LXS_PSM::psmStates[2], HEX);
		lcd->setCursor(9, 0);
		lcd->print(LXS_PSM::psmStates[3], HEX);
		lcd->setCursor(12, 0);
		lcd->print(LXS_PSM::psmStates[4], HEX);
#endif

		return true;
	}

	return false;
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