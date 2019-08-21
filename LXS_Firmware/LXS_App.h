#ifndef _LXS_APP_H_
#define _LXS_APP_H_

#include "LXS_Config.h"
#include "LXS_Types.h"

#include <MIDI.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>

#if LXS_HAS_LEDSTRIP
#include <FastGPIO.h>
#define APA102_USE_FAST_GPIO
#include <APA102.h>
#endif

#if LXS_HAS_LCD
#include "LXS_LCD.h"
#if LXS_LCD_DEBUG
#include "LXS_LCDDebugScreens.h"
#endif
#endif

#include "LXS_Clock.h"
#include "LXS_Sequence.h"

class LXS_App
{
public:
	LXS_App();

	void Init();
	bool Tick();

	static void handleNoteOn(const uint8 inChannel, const uint8 inNote, const uint8 inVelocity);
	static void handleNoteOff(const uint8 inChannel, const uint8 inNote, const uint8 inVelocity);

private:
	static LXS_Clock clock;
	static LXS_Sequence sequence;

	static bool noteTriggered;

#if LXS_HAS_LEDSTRIP
	APA102<LXS_LED_DATAPIN, LXS_LED_CLOCKPIN> ledStrip;
	rgb_color ledColors[LXS_LED_COUNT];
#endif

#if LXS_HAS_LCD
	LXS_LCD lcd;
#if LXS_LCD_DEBUG
	LXS_LCDDebugScreen_ActiveNotes debugScreen;
#endif
#endif
};

#endif /* _LXS_APP_H_ */
