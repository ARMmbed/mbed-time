# POSIX time functions for mbed OS

This module provides simpler time functions for mbed OS, in the style of the POSIX time functions. All values returned from this module are derived from the realtime clock (RTC), so they return the time since the device started.

## Installation

* Install the module in your project via: `yotta install mbed-time`.
* Add `#include <sys/time.h>` to the include list in your .cpp file.

## Implemented functions

* [time](http://www.cplusplus.com/reference/ctime/time/)
* [gettimeofday](http://linux.die.net/man/2/gettimeofday)
* [settimeofday](http://linux.die.net/man/2/gettimeofday)

## Example

Retrieving the time since startup, in milliseconds.

```cpp
#include "mbed-drivers/mbed.h"
#include <sys/time.h>

static void read_time() {
    struct timeval tvp;
    gettimeofday(&tvp, NULL);
    printf("Time since startup %li ms.\r\n", (tvp.tv_sec * 1000L) + (tvp.tv_usec / 1000L));
}

void app_start(int, char**) {
    // on startup, set the time to 0.
    struct timeval tvp = { 0, 0 };
    settimeofday(&tvp, NULL);

    // every 500 ms. we call `read_time` function
    minar::Scheduler::postCallback(read_time).period(minar::milliseconds(500));
}
```
