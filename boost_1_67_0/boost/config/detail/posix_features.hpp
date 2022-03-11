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