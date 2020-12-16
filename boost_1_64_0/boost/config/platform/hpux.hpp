//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2003. 
//  (C) Copyright David Abrahams 2002. 
//  (C) Copyright Toon Knapen 2003. 
//  (C) Copyright Boris Gubenko 2006 - 2007.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  hpux specific config options:

#define BOOST_PLATFORM "HP-UX"

// In principle, HP-UX has a nice <stdint.h> under the name <inttypes.h>
// However, it has the following problem:
// Use of UINT32_C(0) results in "0u l" for the preprocessed source
// (verifyable with gcc 2.95.3)
#if (defined(__GNUC__) && (__GNUC__ >= 3)) || defined(__HP_aCC)
#  define BOOST_HAS_STDINT_H
#endif

#if !(defined(__HP_aCC) || !defined(_INCLUDE__STDC_A1_SOURCE))
#  define BOOST_NO_SWPRINTF
#endif
#if defined(__HP_aCC) && !defined(_INCLUDE__STDC_A1_SOURCE)
#  define BOOST_NO_CWCTYPE
#endif

#if defined(__GNUC__)
#  if (__GNUC__ < 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ < 3))
      // GNU C on HP-UX does not support threads (checked up to gcc 3.3)
#     define BOOST_DISABLE_THREADS
#  elif !defined(BOOST_DISABLE_THREADS)
      // threads supported from gcc-3.3 onwards:
#     define BOOST_HAS_THREADS
#     define BOOST_HAS_PTHREADS
#  endif
#elif defined(__HP_aCC) && !defined(BOOST_DISABLE_THREADS)
#  define BOOST_HAS_PTHREADS
#endif

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>

// the following are always available:
#ifndef BOOST_HAS_GETTIMEOFDAY
#  define BOOST_HAS_GETTIMEOFDAY
#endif
#ifndef BOOST_HAS_SCHED_YIELD
#    define BOOST_HAS_SCHED_YIELD
#endif
#ifndef BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#    define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#endif
#ifndef BOOST_HAS_NL_TYPES_H
#    define BOOST_HAS_NL_TYPES_H
#endif
#ifndef BOOST_HAS_NANOSLEEP
#    define BOOST_HAS_NANOSLEEP
#endif
#ifndef BOOST_HAS_GETTIMEOFDAY
#    define BOOST_HAS_GETTIMEOFDAY
#endif
#ifndef BOOST_HAS_DIRENT_H
#    define BOOST_HAS_DIRENT_H
#endif
#ifndef BOOST_HAS_CLOCK_GETTIME
#    define BOOST_HAS_CLOCK_GETTIME
#endif
#ifndef BOOST_HAS_SIGACTION
#  define BOOST_HAS_SIGACTION
#endif
#ifndef BOOST_HAS_NRVO 
#  ifndef __parisc
#    define BOOST_HAS_NRVO
#  endif
#endif
#ifndef BOOST_HAS_LOG1P 
#  define BOOST_HAS_LOG1P
#endif
#ifndef BOOST_HAS_EXPM1
#  define BOOST_HAS_EXPM1
#endif


/* hpux.hpp
5BhytSTw+VSPryk41PjIbGiNBYvqtzJKsxS044K1n1RmKds6BTBLtgObhq7SLPszRZ0TJ4u1NnykWeDn+O7JpFujEVm12TJwXlNIV7P/9UOapaIVFdLNftLwqGY5f6fYyfTYm+G7ZAUqkDWD0RD6ScBVzQLRLIKdPLl5qmZBaGbd1PcdZGFyOvX9A5nDxY7lO3dNsxQXWzJgo1mz1E1UZ2TzW46Yp1mOS7oGq5c31gy+kMpJ714o9i/kdE1u1l6umb+L2cIf9tHM5mJxLVK2cJ2hDRLseesOezTLQCtg0e3rtXOiNMvcpoCPWbdaS6eHaZb+tQL9QLffi+aZzDHsVKC2Sbf9mScmcp3tUmCMkC4xLOkix7CbnkXJPih7812yF5u5rxJs8676PpplodVQhLr2yv+U89untjMyqZ1l5GrDIGuf3gabgx2Ol6q8XDPYT2MUsjYLe5TUzAfNopvaXsj8XexR1a2faGaTj6m+xyMLRAsR7G+tJ8VplumSbvujcHp/FApZ+/WxWwtp7BYK2fvV2MnU2MngQO7pfA5Qv0RWtcWVE5rZDuR+zCCDY4a5HLPD5knJmqUYpEs1yC/DIF2mS36nFzcdxPVikC7HID+fg7mn8z8o52faP2y8ZoEHcz9mmMExHS7HVKb0W8D1Ih9Trhf5mHK9uBxz0GhrINeLwTHhkEF7OSQfs8SAshW4vaCV1Y2eOyh2g2M6pHT03EGWbpAuQzY59kO5x5dtkC7HJb7QauaaHPvh3I9pO5z7MQMPy8cst6vmx1wvh3Ovs1SDY6ZL6eQ6yzJIly2bHLuBwZHcY/c/kns62xE59ug1Oe24DzFIF3bEoF4kk2PPNChntpyfHLtLOSdGvu3g837U4LwfNTjvR+VjRpY7tJHjMzhmisExU12OufBatQF8PRgcM8vgmNkux2xRbOlkzeBY7ufBdswgdimdfI4cBsdMNzhmhsExsyWj+QIyn+O5W6CBOQws3cCyDAy+yd1sBhZmYKkGlmlgOQbmfyJ3CzKwFAPLMLBsA/M5aXD+DMxhYOkGliUZzS+RQVbuZjOwMANLNbBMA8sxMP9TuVuQgaUYWIaBZRuYz7e5W6CBOQws3cCyDAy+y91sBhZmYKm5WghkouWjZ6eWMAwiIhuGaeZzRlHXUpHdrfJhdc38zypgF+zy3s+CNUtHayjY9YYZ3TTLQVssWNk/6mVqlvG9AscEG1kzdTPbOQXyC+a9q9tOjgGtmmBPrtk6cH5oeQSLrxe+WzM4r0AhwYaElqZ5zCRcs6f3861gPPXzNB9iYIFo/QUb2OrLeM0y0PxFS7Is4vkQtLK60T2H5mZ+oPokm9C14Luahf0gpaN7Ds2HoP1NsDxHh0wgwzWCCvQSrMa1TF/NMi9Ix6S+h+ZRDMz/omTUzii/XC0cUtCqk70BdcE2tWq6ZpkGBpdozQJZzt0d7TQLQ5shmPXLyfd4b4rLOO8tWLfvmxXVLActRLA6R7ts0MxxBdfeCja2RrNOmmVdoTZBJu5bkZ2rJULOFX1dQiD+7Vhczd2aObJpvoeswy6v+qqNgyy0emStwQ5pXbv/pJnPj3hNCzbgps/nmvmjdREscnfwB5qloHU36dbt65pJnO4nBUuuW5uKac80C0NrIthrGbF1NMv4SS7nqNtv19QsBy2/YJ3u71ikGfxMsZN13bcwlfNDqyaUc0rX1o+5Xq7J5Rz2uO5grpdf5HL6XTvTiI+J5q2beo7IHAaWYmCpBpZuYBkGlmlgWblaCGT/otd1G6gFysDfEriPRPMSrNPen83cR/5K61HI9iy5t1yzwOt4TZt0q/Lm2uLcX/9GfR3Z1FrVpnFZ0Lx1k8qZY2A=
*/