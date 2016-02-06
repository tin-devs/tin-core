/* tin_api.c
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

#include <tincore.h>

typedef struct Sn Tin;


Tin *tin_new(void)
{
    return sn_new();
}

void tin_iterate(Tin *tin)
{
    Sn *sn = tin;
    sn_iterate(sn);
}

uint32_t tin_iteration_interval(const Tin *tin)
{
    const Sn *sn = tin;
    return sn_iteration_interval(sn);
}

void tin_kill(Tin *tin)
{
    Sn *sn = tin;
    sn_kill(sn);
}
