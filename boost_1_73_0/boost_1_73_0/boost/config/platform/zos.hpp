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
OwI3GsAiFVSYcOfG1/5tDHd2GNpePAf/CmxvvuG7cb0J9gZFrzWQp6omAqOoga4qRknecf5TJ92w4msY34ZT17vykyD0Y3/sT+EMBu/PwONrssJGVt39+wAGjC7U9cMf1m/vrbeoUFJCUvGcPBBJyyVXt41NJZA3ugbPnjnGMfn9G0C4rnBVc8kzzlR77Do842WJSwR5NEs09/wgciPjF1pmrMkJXCi/bScWXwztIeOoPwpnqD7BaYFNwrBXjkIxgfHyAU6rk3PtauJE49ANYtf3jCDFK0ih4rSUqjlwHlo0vm0mS0e7xq7DUDsZsFS0E2Psc7FAT1pNJDYgQtcpawg8UsZgQfDO00wynJaS7LoPo9WBJqctWHwyDKtcGvsPE3ccmwfAK3fqdOQ46ImReWD+1Q+unfAQcR13LZQcHSrcmR0cUii5A5hO7KAvdwCBH5wdMii5AwjjWdCXnb6ik4dSxH1EfGQT99xEnUyiccdr1KtdNLvsiVFXjrtss17hYmfqOZ0g456H2V9xrLtw252RYav1hxrnb3sWTJ3d7cOpnsPPBx1PSyqH2MZ0OVTKE/jXANhNBu6Tc5T3cEEkjqqGtjH4QZzgYcJgu+mxJXH7ECvjq8GJskaSjkvct0ter1p/CoC+NeazZnQS
*/