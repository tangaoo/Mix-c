/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */
#define TT_TRACE_MODULE_NAME                "main_tc" 

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "ttlib/ttlib.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

/* //////////////////////////////////////////////////////////////////////////////////////
 * declaration
 */
extern int std_out_main(void);
extern int mod_main(void);
extern int thread2_main(void);

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
tt_int_t main(tt_int_t argc, tt_char_t* argv[])
{
    /// init ttlib
    if(!tt_lib_init(tt_null, tt_native_allocator())) return -1;

    /// trace
	tt_trace_i("in main \n");

    /// done
    struct option longopt[] = {
        {"init", 0, tt_null, 'i'},
        {"file", 1, tt_null, 'f'},
        {"list", 0, tt_null, 'l'},
        {"restart", 0, tt_null, 'r'},
        {0, 0, 0, 0}
    };
    tt_int_t opt;
    while((opt = getopt_long(argc, argv, ":if:lr", longopt, tt_null)) != -1)
    {
        switch(opt)
        {
            case 'i':
            case 'r':
            case 'l':
            tt_trace_i("option,%c", opt);
            break;

            case 'f':
            tt_trace_i("filename,%s", optarg);
            break;

            case ':':
            tt_trace_i("option need a val");
            break;

            case '?':
            tt_trace_i("unkonwn option,%c", optopt);
            break;
        }
    }
    /// trace left
    for(; optind < argc; optind++)
    {
        tt_trace_i("argument,%s", argv[optind]);
    }

    tt_lib_exit();
    return 0;
}
