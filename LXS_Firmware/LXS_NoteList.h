#ifndef _LXS_NOTEBUFFER_H_
#define _LXS_NOTEBUFFER_H_

#include "LXS_Types.h"
#include "LXS_Debug.h"
#include "LXS_Constants.h"
#include "LXS_Note.h"

class LXS_NoteList
{
private:
	struct Cell
	{
		inline Cell();
		inline Cell(const Cell& inB);
		inline Cell& operator= (const Cell& inB);

		LXS_Note note;
		Cell* next;
		Cell* prev;
		bool inUse;
	};

public:
	LXS_NoteList(const uint16 inSize);
	~LXS_NoteList();

public:
	void clear();

	void add(const LXS_Note& inNote);
	void remove(const uint8 inChannel, const uint8 inPitch);

	void release(const uint32 inMicros, const uint8 inChannel, const uint8 inPitch);

public:
	inline void resetIterator();

	inline bool getNext(LXS_Note& outNote);
	inline bool getPrev(LXS_Note& outNote);

	inline bool getHigh(LXS_Note& outNote) const;
	inline bool getLow(LXS_Note& outNote) const;

public:
#if LXS_LCD_DEBUG
	bool debugGetActiveNotes(String& outString) const;
#endif

public:
	inline bool isEmpty() const;
	inline uint16 getCount() const;

private:
	inline Cell* getFirstValidCell() const;
	inline Cell* getNextValidCell(Cell* cell) const;
	inline Cell* getLastValidCell() const;
	inline Cell* getPrevValidCell(Cell* cell) const;

	inline Cell* getFirstEmptyCell() const;
	inline Cell* getLastEmptyCell() const;

private:
	uint16 mSize;
	uint16 mCount;

	Cell* mArray;
	Cell* mHead;
	Cell* mTail;
	Cell* mCursor;
};

inline LXS_NoteList::Cell::Cell()
	: note(LXS_Note())
	, next(0)
	, prev(0)
	, inUse(false)
{
}


inline LXS_NoteList::Cell::Cell(const Cell& inB)
	: note(inB.note)
	, next(inB.next)
	, prev(inB.prev)
	, inUse(inB.inUse)
{
}


inline typename LXS_NoteList::Cell& LXS_NoteList::Cell::operator= (const Cell& inB)
{
	note = inB.note;
	next = inB.next;
	prev = inB.prev;
	inUse = inB.inUse;

	return *this;
}

// ########################################################################## //

inline void LXS_NoteList::resetIterator()
{
	mCursor = 0;
}

inline bool LXS_NoteList::getNext(LXS_Note& outNote)
{
	if (!mCursor)
	{
		mCursor = getFirstValidCell();
	}
	else
	{
		mCursor = getNextValidCell(mCursor->next);
	}

	if (!mCursor)
	{
		return false;
	}

	outNote = mCursor->note;

	return true;
}


inline bool LXS_NoteList::getPrev(LXS_Note& outNote)
{
	if(!mCursor)
	{
		mCursor = getLastValidCell();
	}
	else
	{
		mCursor = getPrevValidCell(mCursor->prev);
	}

	if (!mCursor)
	{
		return false;
	}

	outNote = mCursor->note;

	return true;
}


inline bool LXS_NoteList::getHigh(LXS_Note& outNote) const
{
	outNote = LXS_Note();

	Cell* cell = getLastValidCell();

	while (cell)
	{
		if (cell->note.pitch > outNote.pitch)
		{
			outNote = cell->note;
		}

		cell = getPrevValidCell(cell->prev);
	}

	return true;
}


inline bool LXS_NoteList::getLow(LXS_Note& outNote) const
{
	Cell* cell = getLastValidCell();

	uint8 lowPitch = 0xFF;

	while (cell)
	{
		if (cell->note.pitch < lowPitch)
		{
			outNote = cell->note;
			lowPitch = outNote.pitch;
		}

		cell = getPrevValidCell(cell->prev);
	}

	return true;
}

// -----------------------------------------------------------------------------


inline bool LXS_NoteList::isEmpty() const
{
	return mCount == 0;
}


inline uint16 LXS_NoteList::getCount() const
{
	return mCount;
}


inline LXS_NoteList::Cell* LXS_NoteList::getFirstValidCell() const
{
	return getNextValidCell(mHead);
}

inline LXS_NoteList::Cell* LXS_NoteList::getNextValidCell(Cell* cell) const
{
	while (Cell* it = cell)
	{
		if (it->inUse)
		{
			return it;
		}

		it = it->next;
	}

	return 0;
}

inline LXS_NoteList::Cell* LXS_NoteList::getLastValidCell() const
{
	return getPrevValidCell(mTail);
}

inline LXS_NoteList::Cell* LXS_NoteList::getPrevValidCell(Cell* cell) const
{
	while (Cell* it = cell)
	{
		if (it->inUse)
		{
			return it;
		}

		it = it->prev;
	}

	return 0;
}

inline LXS_NoteList::Cell* LXS_NoteList::getFirstEmptyCell() const
{
	for (uint8 i = 0; i < mSize; ++i)
	{
		if (!mArray[i].inUse)
		{
			return &mArray[i];
		}
	}

	return 0;
}


inline LXS_NoteList::Cell* LXS_NoteList::getLastEmptyCell() const
{
	for (uint8 i = mSize - 1; i >= 0; --i)
	{
		if (!mArray[i].inUse)
		{
			return &mArray[i];
		}
	}

	return 0;
}

#endif /* LXS_NOTEBUFFER_H_ */
