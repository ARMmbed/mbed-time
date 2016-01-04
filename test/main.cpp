/* mbed
 * Copyright (c) 2006-2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed-drivers/mbed.h"
#include "mbed-drivers/test_env.h"

#include "mbed-time/Calendar.h"

#include <sys/time.h>


time_t unixtime;

void endTime()
{
    MBED_HOSTTEST_RESULT(true);
}

void printTime()
{
    /* verify that exactly 1 second has elapsed */
    time_t now = time(NULL);
    MBED_HOSTTEST_ASSERT(now == unixtime + 1);
    unixtime = now;

    uint8_t hour   = Calendar::getHour();
    uint8_t minute = Calendar::getMinute();
    uint8_t second = Calendar::getSecond();

    uint8_t day    = Calendar::getDay();
    uint8_t date   = Calendar::getDate();
    uint8_t month  = Calendar::getMonth();
    uint32_t year  = Calendar::getYear();

    printf("%lu %u %u %u %u %u %u %lu\r\n", unixtime, hour, minute, second, day, date, month, year);
}

void app_start(int, char *[])
{
    MBED_HOSTTEST_TIMEOUT(60 * 60 + 1);
    MBED_HOSTTEST_SELECT(default);
    MBED_HOSTTEST_DESCRIPTION(time test);
    MBED_HOSTTEST_START("TIME");

    /* test year */
    Calendar::setYear(2015);
    uint32_t year  = Calendar::getYear();
    MBED_HOSTTEST_ASSERT(year == 2015);

    /* test month */
    Calendar::setMonth(12);
    uint8_t month  = Calendar::getMonth();
    MBED_HOSTTEST_ASSERT(month == 12);

    /* test date */
    Calendar::setDate(31);
    uint8_t date   = Calendar::getDate();
    MBED_HOSTTEST_ASSERT(date == 31);

    /* test hour */
    Calendar::setHour(23);
    uint8_t hour   = Calendar::getHour();
    MBED_HOSTTEST_ASSERT(hour == 23);

    /* test minute */
    Calendar::setMinute(59);
    uint8_t minute = Calendar::getMinute();
    MBED_HOSTTEST_ASSERT(minute == 59);

    /* test second */
    Calendar::setSecond(50);
    uint8_t second = Calendar::getSecond();
    MBED_HOSTTEST_ASSERT(second == 50);

    /* test unix time */
    unixtime = time(NULL);
    MBED_HOSTTEST_ASSERT(unixtime == 1451606390);

    /* schedule tasks */
    minar::Scheduler::postCallback(printTime)
        .period(minar::milliseconds(1000));

    minar::Scheduler::postCallback(endTime)
        .period(minar::milliseconds(60 * 60 * 1000));
}
