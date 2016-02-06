/* tincore.c
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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <tox/tox.h>

#include "tincore.h"
#include "util.h"


/* Time to wait between bootstrap attempts when we are not connected to the DHT */
#define BOOTSTRAP_INTERVAL 8


void cb_self_connection_status(Tox *m, TOX_CONNECTION status, void *object)
{
    Sn *sn = object;

    if (status == TOX_CONNECTION_NONE) {
        sn->time_bootstrapped = get_time();
    }

    fprintf(stderr, "Connection status: %d\n", status);
}

static void register_tox_callbacks(const Sn *sn)
{
    tox_callback_self_connection_status(sn->tox, cb_self_connection_status, (void *) sn);
}

/* TODO: This is for testing purposes. The UI-layer should eventually be supplying a nodes list  */
static struct toxNodes {
    const char *ip;
    uint16_t    port;
    const char *key;
} nodes[] = {
    { "144.76.60.215",   33445, "04119E835DF3E78BACF0F84235B300546AF8B936F035185E2A8E9E0A67C8924F" },
    { "198.98.51.198",   33445, "1D5A5F2F5D6233058BF0259B09622FB40B482E4FA0931EB8FD3AB8E7BF7DAF6F" },
    { "195.154.119.113", 33445, "E398A69646B8CEACA9F0B84F553726C1C49270558C57DF5F3C368F05A7D71354" },
    { "46.38.239.179",   33445, "F5A1A38EFB6BD3C2C8AF8B10D85F0F89E931704D349F1D0720C3C4059AF2440A" },
    { NULL, 0, NULL },
};

/* Attempts to bootstrap to the Tox DHT network. */
static void bootstrap_tox(Sn *sn)
{
    if (!timed_out(sn->time_bootstrapped, BOOTSTRAP_INTERVAL)) {
        return;
    }

    sn->time_bootstrapped = get_time();

    for (size_t i = 0; nodes[i].ip; ++i) {
        char bin_key[TOX_PUBLIC_KEY_SIZE];
        if (hex_string_to_bin(nodes[i].key, strlen(nodes[i].key), bin_key, sizeof(bin_key)) == -1) {
            continue;
        }

        TOX_ERR_BOOTSTRAP err;
        tox_bootstrap(sn->tox, nodes[i].ip, nodes[i].port, (uint8_t *) bin_key, &err);

        if (err != TOX_ERR_BOOTSTRAP_OK) {
            fprintf(stderr, "Failed to bootstrap DHT via: %s %d (error %d)\n", nodes[i].ip, nodes[i].port, err);
        }
    }
}

static void do_connection(Sn *sn)
{
    if (tox_self_get_connection_status(sn->tox) == TOX_CONNECTION_NONE) {
        bootstrap_tox(sn);
    }
}

Sn *sn_new(void)
{
    struct Tox_Options options;
    tox_options_default(&options);

    TOX_ERR_NEW err;
    Tox *tox = tox_new(&options, &err);

    if (tox == NULL) {
        return NULL;
    }

    Sn *sn = calloc(1, sizeof(Sn));

    if (sn == NULL) {
        tox_kill(tox);
        return NULL;
    }

    sn->tox = tox;
    sn->num_groups = 0;
    sn->num_friends = 0;
    sn->time_bootstrapped = 0;

    register_tox_callbacks(sn);

    return sn;
}

void sn_kill(Sn *sn)
{
    if (sn == NULL) {
        return;
    }

    if (sn->tox) {
        tox_kill(sn->tox);
    }

    // TODO: properly destroy everything in the Sn object

    free(sn);
}

void sn_iterate(Sn *sn)
{
    if (sn == NULL) {
        return;
    }

    update_time();
    do_connection(sn);

    if (sn->tox) {
        tox_iterate(sn->tox);
    }
}

uint32_t sn_iteration_interval(const Sn *sn)
{
    return tox_iteration_interval(sn->tox);
}
