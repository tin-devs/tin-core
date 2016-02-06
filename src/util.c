/* util.c
*
*  Tin Software. All rights reserved.
*  Copyright (c) 2016
*
*  This file is part of Tin.
*
*  You should have received a copy of the Sleepycat Software license
*  along with Tin. If not, see <https://opensource.org/licenses/Sleepycat>.
*
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include <stdio.h>
#include <stdbool.h>
#include <time.h>


static time_t current_time;

void update_time(void)
{
    current_time = time(NULL);
}

time_t get_time(void)
{
    return current_time;
}

bool timed_out(time_t timestamp, time_t timeout)
{
    return timestamp + timeout <= get_time();
}

int hex_string_to_bin(const char *hex_string, size_t hex_len, char *output, size_t output_size)
{
    if (output_size == 0 || hex_len != output_size * 2) {
        return -1;
    }

    for (size_t i = 0; i < output_size; ++i) {
        sscanf(hex_string, "%2hhx", &output[i]);
        hex_string += 2;
    }

    return 0;
}
