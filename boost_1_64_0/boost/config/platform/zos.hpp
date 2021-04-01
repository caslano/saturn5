//  Copyright (c) 2017 Dynatrace
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org for most recent version.

//  Platform setup for IBM z/OS.

#define BOOST_PLATFORM "IBM z/OS"

#include <features.h> // For __UU, __C99, __TR1, ...

#if defined(__UU)
#  define BOOST_HAS_GETTIMEOFDAY
#endif

#if defined(_OPEN_THREADS) || defined(__SUSV3_THR)
#  define BOOST_HAS_PTHREADS
#  define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  define BOOST_HAS_THREADS
#endif

#if defined(__SUSV3) || defined(__SUSV3_THR)
#  define BOOST_HAS_SCHED_YIELD
#endif

#define BOOST_HAS_SIGACTION
#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_DIRENT_H
#define BOOST_HAS_NL_TYPES_H

/* zos.hpp
Ue5vAJ3l0joqvkM9HrOQuC0teiJ70UgTkKmZaOuja8B/sGy+6CJqWTAxOwylsvGUeMDwhdhFGgolPTokju6uAEedd1zT9jr2PnKnlE2LWAdVWsmDF32vXxVWq1lTAY4Be/pxRXegVkB26BG7WjLIMMKhk0XTHqW72mxiABb1n3rEhY9drxBgG/t3nyiB3A+BfLdipQftpYh6XNG6fI2PVRV7RtMX+dg7ZviZOtwW/g5o1zEy9WtagercPETwjekbF5gmatcBmW3ADhXePbSOyBzoIddI2RL1jb8ahOxQv6Kh4XRVX79ea+/jz7rCejnm1H4oLn7RZ2skqcaUl4E+rlinljyFV8fCwzqGy46TnqAEuWJlH8Yr8zKMqK8N6Sepo1TcMwNR139KMwKahukF2WsC4jPPyfRYilEuwASHWFfikMpDyA2I8Tk7sMyI+kc2+z0zgJYAXPqZJnJJI4n6LZKTpsj+hHYSf3wd745xbI45M/RHZlkXKa4f33wDGXCQ6k09L1TrdY7kE4FzaUdNGTXorGmOTOL2lKW/kq5GORqGFb0K48J9+cIFzQ==
*/