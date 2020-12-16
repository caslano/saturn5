//  (C) Copyright John Maddock 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org for most recent version.

// All POSIX feature tests go in this file,
// Note that we test _POSIX_C_SOURCE and _XOPEN_SOURCE as well
// _POSIX_VERSION and _XOPEN_VERSION: on some systems POSIX API's
// may be present but none-functional unless _POSIX_C_SOURCE and
// _XOPEN_SOURCE have been defined to the right value (it's up
// to the user to do this *before* including any header, although
// in most cases the compiler will do this for you).

#  if defined(BOOST_HAS_UNISTD_H)
#     include <unistd.h>

      // XOpen has <nl_types.h>, but is this the correct version check?
#     if defined(_XOPEN_VERSION) && (_XOPEN_VERSION >= 3)
#        define BOOST_HAS_NL_TYPES_H
#     endif

      // POSIX version 6 requires <stdint.h>
#     if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200100)
#        define BOOST_HAS_STDINT_H
#     endif

      // POSIX version 2 requires <dirent.h>
#     if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 199009L)
#        define BOOST_HAS_DIRENT_H
#     endif

      // POSIX version 3 requires <signal.h> to have sigaction:
#     if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 199506L)
#        define BOOST_HAS_SIGACTION
#     endif
      // POSIX defines _POSIX_THREADS > 0 for pthread support,
      // however some platforms define _POSIX_THREADS without
      // a value, hence the (_POSIX_THREADS+0 >= 0) check.
      // Strictly speaking this may catch platforms with a
      // non-functioning stub <pthreads.h>, but such occurrences should
      // occur very rarely if at all.
#     if defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0) && !defined(BOOST_HAS_WINTHREADS) && !defined(BOOST_HAS_MPTASKS)
#        define BOOST_HAS_PTHREADS
#     endif

      // BOOST_HAS_NANOSLEEP:
      // This is predicated on _POSIX_TIMERS or _XOPEN_REALTIME:
#     if (defined(_POSIX_TIMERS) && (_POSIX_TIMERS+0 >= 0)) \
             || (defined(_XOPEN_REALTIME) && (_XOPEN_REALTIME+0 >= 0))
#        define BOOST_HAS_NANOSLEEP
#     endif

      // BOOST_HAS_CLOCK_GETTIME:
      // This is predicated on _POSIX_TIMERS (also on _XOPEN_REALTIME
      // but at least one platform - linux - defines that flag without
      // defining clock_gettime):
#     if (defined(_POSIX_TIMERS) && (_POSIX_TIMERS+0 >= 0))
#        define BOOST_HAS_CLOCK_GETTIME
#     endif

      // BOOST_HAS_SCHED_YIELD:
      // This is predicated on _POSIX_PRIORITY_SCHEDULING or
      // on _POSIX_THREAD_PRIORITY_SCHEDULING or on _XOPEN_REALTIME.
#     if defined(_POSIX_PRIORITY_SCHEDULING) && (_POSIX_PRIORITY_SCHEDULING+0 > 0)\
            || (defined(_POSIX_THREAD_PRIORITY_SCHEDULING) && (_POSIX_THREAD_PRIORITY_SCHEDULING+0 > 0))\
            || (defined(_XOPEN_REALTIME) && (_XOPEN_REALTIME+0 >= 0))
#        define BOOST_HAS_SCHED_YIELD
#     endif

      // BOOST_HAS_GETTIMEOFDAY:
      // BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE:
      // These are predicated on _XOPEN_VERSION, and appears to be first released
      // in issue 4, version 2 (_XOPEN_VERSION > 500).
      // Likewise for the functions log1p and expm1.
#     if defined(_XOPEN_VERSION) && (_XOPEN_VERSION+0 >= 500)
#        define BOOST_HAS_GETTIMEOFDAY
#        if defined(_XOPEN_SOURCE) && (_XOPEN_SOURCE+0 >= 500)
#           define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#        endif
#        ifndef BOOST_HAS_LOG1P
#           define BOOST_HAS_LOG1P
#        endif
#        ifndef BOOST_HAS_EXPM1
#           define BOOST_HAS_EXPM1
#        endif
#     endif

#  endif





/* posix_features.hpp
pG3aB6V8F1995+PUhlH47hL24YUv4N/drp0YNcddMCxo3EXs9CSYtrsOhmmAfZlj84D27re85R+EQeCcP0jYnXPec43AYhmb9kabiW25466/ijnVcaNN+wHPdzFghT/dQ3N/LGvTntJNrMu//Fs09xfgG9lNrL/ziqKB2dhFtOdynvPh928c+/d7BNY9CTYM2G0SVvnZNc8WWEfFpm2SsJFrf5ymfIDdKWGv6P/zRQLr2oO6RBj1acRigK20mVj30MQygZ3aC31MN7GrP9/ypMAO32TD9/EJe+xP7z4ksNMvtWkAE3bq4SWPCezEy2x4Z5awl7x2+1Li+XIY6yTsXYsHXkoye4VN+7jdxDYWk/upnq+GP1J5B36aPUttv9Wm9Uo87R/93UmBFQDzS9j67796rtCXU4DdxbEF8K1vWPTrxQI78FqbdpWEHf/py0oCOw3YWyXsG/HtLxfY4dts2jQJ++TxTz4isKOAfVnCdnxmzTWEvU7N9/cXvOx9AjsBmNNmYitzL/u4wIbfgHOAiX3r8P2foLoAtlDC5D52YhLsdF0MN7PqY12TYA7A5kjYtkefWE5tAGyNhJ1976d+S20A7J8StvLsotdTPaGzt0pY/oFv3iSws3UxPLAEu4BjCwEL71m+nPIBtk7Cll3x44MC636zTZthM7H7r/dmBbb/ANqDJhaaMdNG3xawdgn7QWyRk76DJd/CFaeHqC6AeSVs3l++T3oWewv2d8LYuoPqAtghCXvOx948nfLdAXOj1IbPbfYcp/7wVoWnNIbgIbBNG5Owk5e/cBX1lTvVNrwl9b391D4L9sGbbvs0tQ+wTgmbf8lHHqBx8G02Lc2xS+D3dw7fdbnADgA2T8J+t+HScwI7CtgJCVt7/apX0djzdtitl7D474evpLHnLpv2bQnrCn11EWGwaNwgYd/b/9THSNaAfZzLsxPmhyXevs+R7r4T15SEsTUlyRqwJyTs2s//7D0k60Ngh0g8/z7m+wx9v3fjNyJM/e6A3SthV9/3Pi/le4+ST/m2+wE7pJvYn5961wepnveAPcGxRfCNHpiv/5P6wwfAZrCZ2NOHpv2E5ltwcn+U58NB9YG+1Ddprf0RGAskrCtxulXIej8IM8XribK7zfeW+2m+/YRNe6WEveg7u7Yj5tm0i0WTZ1F5jR9L2dUjlUw2tXrtmrVrukdX7yn1dK+9krCJDb2rS+Cokk6t5n69gsKIQb8LnxnYlTCeWVuTH7mhKWUIuaq2pqZxWxM9h/RZC4yfQjM00K3LWsUeSGPlkGeBVBssCKkQjWRRy7400Gv1+Xbjp3b4d1HzZJEspxsuCiqjtk2skU2ML0niu/DGGX4z5YDHSI2WA5VBclDteI3seHBb0R/BzTKkAXksaZoc8HypwWKgIqhfWNYeGq0vYEGtH0FrBsdOuLtxWfPkAGdwE40WBJVR24bXyIaHSHX67agg6M/Y3sx+wY79U40XBBai6oRq12pk18Kpvx7jUR1mtTdz3sBDtAZLgoogOVhsR41sR3BN04fajZ+GW5sqh32FhssBi1DloNqmGtmmcASn78TFGPrbTAP/i6bJoVJOlscbLAizjNo2rMZtWPzvhfpBbkNsbGvmGIFv2jZcDFiErA81bXIDjel4B4H5O7Q2c+6Ew8bM6L4GS4IKkWRRc51hoFF9GE/N+D3JrmbJYhyekgFvyZHGCkMphdapnwfvWC6LSzHtlhyfQyN6AQnwvBj+ndUsWeDrceligxdeVIg6h95v017KZYH7Fpffv2uJgYb148uMn47MbWIfMV5TbLCFSYWosvge7AdzWaAQfvKbt/FomiF9M+5Yo0/F7CbOH/BX47sIFaI=
*/