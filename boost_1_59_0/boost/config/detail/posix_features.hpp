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
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
*/