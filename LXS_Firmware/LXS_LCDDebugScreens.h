#ifndef _LXS_LCDDEBUGSCREENS_H_
#define _LXS_LCDDEBUGSCREENS_H_

#include "LXS_Config.h"
#include "LXS_Types.h"
#include "LXS_Constants.h"

#include "LXS_NoteList.h"

#if LXS_HAS_LCD && LXS_LCD_DEBUG
#include "LXS_LCD.h"

class LXS_LCDDebugScreen_ActiveNotes : public LXS_LCD
{
public:
	LXS_LCDDebugScreen_ActiveNotes();

	void init();
	bool tick(const LXS_Clock& inClock);

	void update(const LXS_NoteList& note);

private:

};

#endif /* LXS_DEBUG_LCD */

#endif /* _LXS_LCDDEBUGSCREENS_H_ */