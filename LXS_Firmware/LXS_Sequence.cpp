#include "LXS_Sequence.h"

LXS_Sequence::LXS_Sequence(const uint16 inNotelistSize)
	: noteList(inNotelistSize)
{

}

LXS_Sequence::~LXS_Sequence()
{

}

void LXS_Sequence::init()
{
	noteList.clear();
}

bool LXS_Sequence::tick(const LXS_Clock& inClock)
{
	return true;
}