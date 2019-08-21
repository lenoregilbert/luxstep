#include "LXS_App.h"

//SoftwareSerial softSerial(50, 51);
//MIDI_CREATE_INSTANCE(SoftwareSerial, softSerial, midiA);
static MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);

LXS_Clock LXS_App::clock;

LXS_Sequence LXS_App::sequence(LXS_MAX_NOTES);
bool LXS_App::noteTriggered = false;

LXS_App::LXS_App()
{

}

void LXS_App::Init()
{
	clock.init(LXS_ClockSource::Internal, LXS_SyncType::ReTrigReset);

#if LXS_HAS_LCD
	lcd.init();
#if LXS_LCD_DEBUG
	debugScreen.init();
#endif
#endif

	sequence.init();

	midiA.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages

	midiA.turnThruOff();

	midiA.setHandleNoteOn(handleNoteOn);
	midiA.setHandleNoteOff(handleNoteOff);

#if LXS_HAS_LEDSTRIP
	pinMode(LXS_LED_CLOCKPIN, OUTPUT);
	pinMode(LXS_LED_DATAPIN, OUTPUT);

	for (uint16_t i = 0; i < LXS_LED_COUNT; i++)
	{
		ledColors[i].red = 0;
		ledColors[i].green = 0;
		ledColors[i].blue = 0;
	}

	ledStrip.write(ledColors, LXS_LED_COUNT, LXS_LED_BRIGHTNESS);
#endif
}

bool LXS_App::Tick()
{
	noteTriggered = false;

	clock.tick();

	// Read incoming messages
	midiA.read();

	sequence.tick(clock);

#if LXS_HAS_LCD
	lcd.tick(clock);

#if LXS_LCD_DEBUG
	debugScreen.tick(clock);

	if(noteTriggered)
	{
		debugScreen.update(sequence.noteList);
	}
#endif
#endif

#if LXS_HAS_LEDSTRIP
	if (sequence.noteList.getCount() > 0)
	{
		uint8_t time = clock.activeTime.milliseconds >> 2;
		for (uint16_t i = 0; i < LXS_LED_COUNT; i++)
		{
			uint8_t x = time - i * 8;
			ledColors[i].red = x;
			ledColors[i].green = 255 - x;
			ledColors[i].blue = x;
		}
	}
	else
	{
		for (uint16_t i = 0; i < LXS_LED_COUNT; i++)
		{
			ledColors[i].red = 0;
			ledColors[i].green = 0;
			ledColors[i].blue = 0;
		}
	}

	ledStrip.write(ledColors, LXS_LED_COUNT, 10);
#endif

	return true;
}

void LXS_App::handleNoteOn(const uint8 inChannel, const uint8 inPitch, const uint8 inVelocity)
{
	midiA.sendNoteOn(inPitch, inVelocity, inChannel);

	sequence.handleNoteOn(clock, inChannel, inPitch, inVelocity);

	clock.notify(LXS_EventType::Note, true);
	noteTriggered = true;
}

void LXS_App::handleNoteOff(const uint8 inChannel, const uint8 inPitch, const uint8 inVelocity)
{
	midiA.sendNoteOff(inPitch, inVelocity, inChannel);

	sequence.handleNoteOff(clock, inChannel, inPitch, inVelocity);

	clock.notify(LXS_EventType::Note, false);
	noteTriggered = true;
}