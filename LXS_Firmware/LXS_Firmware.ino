#include "LXS_Debug.h"
#include "LXS_App.h"

LXS_App lxsApp;

void setup()
{
	LXS_DEBUGINIT(Serial, 115200);

	lxsApp.Init();
}

void loop()
{
	lxsApp.Tick();
}
