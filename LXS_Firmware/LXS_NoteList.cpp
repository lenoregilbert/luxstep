#include "LXS_NoteList.h"

LXS_NoteList::LXS_NoteList(const uint16 inSize)
	: mSize(inSize)
	, mCount(0)
	, mHead(0)
	, mTail(0)
	, mCursor(0)
{
	mArray = (LXS_NoteList::Cell*)malloc(sizeof(Cell) * inSize);

	clear();
}

LXS_NoteList::~LXS_NoteList()
{
	free(mArray);
}

void LXS_NoteList::clear()
{
	for (int i = 0; i < mSize; ++i)
	{
		mArray[i] = Cell();
	}
}

void LXS_NoteList::add(const LXS_Note& inNote)
{
	remove(inNote.channel, inNote.pitch);

	Cell* cell = getFirstEmptyCell();
	if (!cell)
	{
		Cell* droppedCell = getFirstValidCell();
		remove(droppedCell->note.channel, droppedCell->note.pitch);

		cell = getFirstEmptyCell();
	}

	cell->note = inNote;
	cell->inUse = true;

#if LXS_NOTELIST_DEBUG
	LXS_DPRINT("add: ");
	LXS_DPRINT(mCount);
	LXS_DPRINT(" pitch: ");
	LXS_DPRINTLN(inNote.pitch);
#endif

	if (mCount == 0)
	{
		mHead = mTail = cell;
	}
	else
	{
		mTail->next = cell;
		cell->prev = mTail;

		mTail = cell;
	}

	mCount++;

#if LXS_NOTELIST_DEBUG
	LXS_DPRINT("end add: ");
	LXS_DPRINTLN(mCount);
#endif
}


void LXS_NoteList::remove(const uint8 inChannel, const uint8 inPitch)
{
#if LXS_NOTELIST_DEBUG
	LXS_DPRINT("rem outer: ");
	LXS_DPRINT(mCount);
	LXS_DPRINT(" pitch: ");
	LXS_DPRINT(inPitch);
#endif

	Cell* cell = getLastValidCell();

#if LXS_NOTELIST_DEBUG
	LXS_DPRINT(" cell: ");
	LXS_DPRINTLN((uint32)cell);
#endif

	while (cell)
	{
		Cell* prev = cell->prev;
		Cell* next = cell->next;

		if (cell->note.channel == inChannel && cell->note.pitch == inPitch)
		{
#if LXS_NOTELIST_DEBUG
			LXS_DPRINT("rem inner: ");
			LXS_DPRINT(mCount);
			LXS_DPRINT(" pitch: ");
			LXS_DPRINT(cell->note.pitch);
			LXS_DPRINT(" next: ");
			LXS_DPRINTLN((uint32)next);
#endif

			mCount--;

			*cell = Cell();

			if (mCount > 0)
			{
				if (prev)
				{
					prev->next = next;

					if (next)
					{
						next->prev = prev;
					}
					else
					{
						mTail = prev;
					}
				}
				else
				{
					mHead = getNextValidCell(next);
					mHead->prev = prev = 0;
				}
			}
			else
			{
				mHead = mTail = 0;

#if LXS_NOTELISTDEBUG
				LXS_DPRINT("end rem inner break: ");
				LXS_DPRINTLN(mCount);
#endif

				break;
			}

#if LXS_NOTELIST_DEBUG
			LXS_DPRINT("end rem inner: ");
			LXS_DPRINT(mCount);
			LXS_DPRINT(" cell: ");
			LXS_DPRINT((uint32)cell);
			LXS_DPRINT(" prev: ");
			LXS_DPRINTLN((uint32)prev);
#endif
		}

		cell = getPrevValidCell(prev);
	}

#if LXS_NOTELIST_DEBUG
	LXS_DPRINT("end rem outer: ");
	LXS_DPRINTLN(mCount);
#endif
}


void LXS_NoteList::release(const uint32 inMicros, const uint8 inChannel, const uint8 inPitch)
{
	Cell* cell = getLastValidCell();

	while (cell)
	{
		Cell* prev = cell->prev;

		if (cell->note.channel == inChannel || cell->note.pitch == inPitch)
		{
			cell->note.release(inMicros);
		}

		cell = getPrevValidCell(prev);
	}
}

#if LXS_LCD_DEBUG
bool LXS_NoteList::debugGetActiveNotes(String& outString) const
{
	Cell* cell = getFirstValidCell();

	while (cell)
	{
		outString.concat(String(LXS_NoteStrings[cell->note.pitch % 12]));
		outString.concat(String(cell->note.pitch / 12));
		outString.concat(String(" "));

		cell = getNextValidCell(cell->next);
	}
	
	return true;
}
#endif