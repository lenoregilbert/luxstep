#ifndef _LXS_LCD_H_
#define _LXS_LCD_H_

#include "LXS_Config.h"
#include "LXS_Types.h"
#include "LXS_Constants.h"
#include "LXS_Clock.h"

#if LXS_HAS_LCD

#include <LiquidCrystal.h>
#include <LCDKeypad.h>

class LXS_LCD : public LCDKeypad
{
public:
	LXS_LCD();

	virtual void init();
	virtual bool tick(const LXS_Clock& inClock);

	void clear();
	uint8 print(const String& inString);

private:
	uint8 curCol;
	uint8 curRow;
};

#endif /* LXS_HAS_LCD */

#endif /* _LXS_LCD_H_ */