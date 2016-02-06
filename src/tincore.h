/* tincore.h
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

#ifndef TINCORE_H
#define TINCORE_H

#include <tox/tox.h>
#include <time.h>

#include "friends.h"
#include "groups.h"


typedef struct Sn {
    Tox     *tox;

    Friend  *friends;
    uint32_t num_friends;

    Group   *groups;
    uint32_t num_groups;

    time_t   time_bootstrapped;
} Sn;


/*
 * Returns a new initialized Sn object. sn_kill() must be called when this object is no longer needed.
 * Returns NULL on failure.
 */
Sn *sn_new(void);

/*
 * Frees all data structures associated with the passed Sn object.
 * Call this before closing shop.
 */
void sn_kill(Sn *sn);

/* The main loop that needs to be run every sn_iteration_interval() milliseconds. */
void sn_iterate(Sn *sn);

/* Returns the time in milliseconds to wait between sn_iterate() calls for optimal performance. */
uint32_t sn_iteration_interval(const Sn *sn);


#endif /* TINCORE_H */
