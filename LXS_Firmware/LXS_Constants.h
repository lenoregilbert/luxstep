#ifndef _LXS_CONSTANTS_H_
#define _LXS_CONSTANTS_H_

#include "LXS_Config.h"
#include "LXS_Types.h"

#if LXS_HAS_LCD && LXS_LCD_PULSE
extern uint8 LXS_PulseBitmaps[];
extern const uint32 LXS_PulseBitmapFrameMasks[];

#define LXS_PulseBitmap_FrameRateMicroSeconds LXSMILLISECONDSTOMICROSECONDS(4250) // 
#define LXS_PulseBitmap_FrameCount 18 // 16 Frames
#define LXS_PulseBitmap_FrameStride 8 // 8 Bytes Per Frame
#define LXS_PulseBitmap_Blank 0
#define LXS_PulseBitmap_Char 1

uint8 LXS_PulseBitmapGetFrameIdx(uint32 microseconds);
uint32 LXS_PulseBitmapGetFrameOffset(uint32 microseconds);
uint8 *LXS_PulseBitmapGetFramePtr(uint32 microseconds);
#endif /* LXS_HAS_LCD */

#if LXS_LCD_DEBUG
extern char* LXS_NoteStrings[];
#endif

#endif /* _LXS_CONSTANTS_H_ */