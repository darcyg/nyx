#include "config.h"
#include "event.h"
#include "log.h"
#include "nyx.h"
#include "poll.h"
#include "state.h"
#include "utils.h"

#include <stdio.h>

int
main(int argc, char **argv)
{
    int failed = 0;
    nyx_t *nyx = NULL;

    if (argc < 2)
    {
        print_usage(stderr);
        fputs("\nTry 'nyx -h' for more information\n", stderr);
        return 1;
    }

    /* initialize log and main application data */
    nyx = nyx_initialize(argc, argv);

    if (nyx == NULL)
    {
        failed = 1;
        goto teardown;
    }

    /* parse config */
    if (!parse_config(nyx))
    {
        if (hash_count(nyx->watches) < 1)
            log_error("No watches configured - terminating now");

        failed = 1;
        goto teardown;
    }

    if (!nyx_watches_init(nyx))
    {
        log_error("No valid watched configured - terminating now");

        failed = 1;
        goto teardown;
    }

    /* start the event handler loop */
    if (!event_loop(nyx, dispatch_event))
    {
        log_warn("Failed to initialize event manager "
                  "- trying polling mechanism next");

        if (!poll_loop(nyx, dispatch_poll_result))
        {
            log_error("Failed to start loop manager as well - terminating");
            failed = 1;
        }
    }

teardown:
    nyx_destroy(nyx);
    log_shutdown();

    return failed;
}

/* vim: set et sw=4 sts=4 tw=80: */
