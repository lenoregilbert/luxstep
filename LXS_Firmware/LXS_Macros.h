#ifndef _LXS_MACROS_H_
#define _LXS_MACROS_H_

#define LXS_SECONDSTOMILLISECONDS(milliseconds) (milliseconds * 1000)
#define LXS_SECONDSTOMICROSECONDS(seconds) (seconds * 1000000)

#define LXS_MILLISECONDSTOSECONDS(milliseconds) (milliseconds / 1000)
#define LXS_MILLISECONDSTOSECONDS_FRAC(milliseconds) (milliseconds % 1000)
#define LXS_MILLISECONDSTOMICROSECONDS(milliseconds) (milliseconds * 1000)

#define LXS_MICROSECONDSTOSECONDS(microseconds) (microseconds / 1000000)
#define LXS_MICROSECONDSTOSECONDS_FRAC(microseconds) (microseconds % 1000000)
#define LXS_MICROSECONDSTOMILLISECONDS(microseconds) (microseconds / 1000)
#define LXS_MICROSECONDSTOMILLISECONDS_FRAC(microseconds) (microseconds % 1000)

#endif /* _LXS_MACROS_H_ */