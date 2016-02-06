/* util.h
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

#ifndef UTIL_H
#define UTIL_H


/* Returns the current unix time. */
time_t get_time(void);

/* Should be called at least once per second. */
void update_time(void);

/* Returns true if timestamp has timed out according to timeout value. */
bool timed_out(time_t timestamp, time_t timeout);

/*
 * Converts a hexidecimal string of length hex_len to binary format and puts the result in output.
 * output_size must be exactly half of hex_len.
 *
 * Returns 0 on success.
 * Returns -1 on failure.
 */
int hex_string_to_bin(const char *hex_string, size_t hex_len, char *output, size_t output_size);


#endif  /* UTIL_H */
