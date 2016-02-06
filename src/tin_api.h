/* tin_api.h
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

#ifndef TIN_API_H
#define TIN_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tin_api.h"

#ifndef TIN_DEFINED
#define TIN_DEFINED
typedef struct Tin Tin;
#endif


/**
 * Creates and initializes a new Tin object with options passed.
 *
 * @param options An options object as described above.
 *
 * @return Tin object pointer on success.
 * @return NULL if Tin object fails to initialize.
 */
Tin *tin_new(void);

/**
 * The mainloop that needs to be run every tin_iteration_interval() milliseconds.
 */
void tin_iterate(Tin *tin);

/**
 * Returns the time in milliseconds to wait between tin_iterate() calls for optimal performance.
 */
uint32_t tin_iteration_interval(const Tin *tin);

/**
 *  Frees all data structures associated with the passed tin object.
 *  Call this before closing shop.
 */
void tin_kill(Tin *tin);



#ifdef __cplusplus
}
#endif

#endif /* TIN_API_H */
