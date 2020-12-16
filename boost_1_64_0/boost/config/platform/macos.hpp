//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Darin Adler 2001 - 2002. 
//  (C) Copyright Bill Kempf 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Mac OS specific config options:

#define BOOST_PLATFORM "Mac OS"

#if __MACH__ && !defined(_MSL_USING_MSL_C)

// Using the Mac OS X system BSD-style C library.

#  ifndef BOOST_HAS_UNISTD_H
#    define BOOST_HAS_UNISTD_H
#  endif
//
// Begin by including our boilerplate code for POSIX
// feature detection, this is safe even when using
// the MSL as Metrowerks supply their own <unistd.h>
// to replace the platform-native BSD one. G++ users
// should also always be able to do this on MaxOS X.
//
#  include <boost/config/detail/posix_features.hpp>
#  ifndef BOOST_HAS_STDINT_H
#     define BOOST_HAS_STDINT_H
#  endif

//
// BSD runtime has pthreads, sigaction, sched_yield and gettimeofday,
// of these only pthreads are advertised in <unistd.h>, so set the 
// other options explicitly:
//
#  define BOOST_HAS_SCHED_YIELD
#  define BOOST_HAS_GETTIMEOFDAY
#  define BOOST_HAS_SIGACTION

#  if (__GNUC__ < 3) && !defined( __APPLE_CC__)

// GCC strange "ignore std" mode works better if you pretend everything
// is in the std namespace, for the most part.

#    define BOOST_NO_STDC_NAMESPACE
#  endif

#  if (__GNUC__ >= 4)

// Both gcc and intel require these.  
#    define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#    define BOOST_HAS_NANOSLEEP

#  endif

#else

// Using the MSL C library.

// We will eventually support threads in non-Carbon builds, but we do
// not support this yet.
#  if ( defined(TARGET_API_MAC_CARBON) && TARGET_API_MAC_CARBON ) || ( defined(TARGET_CARBON) && TARGET_CARBON )

#  if !defined(BOOST_HAS_PTHREADS)
// MPTasks support is deprecated/removed from Boost:
//#    define BOOST_HAS_MPTASKS
#  elif ( __dest_os == __mac_os_x )
// We are doing a Carbon/Mach-O/MSL build which has pthreads, but only the
// gettimeofday and no posix.
#  define BOOST_HAS_GETTIMEOFDAY
#  endif

#ifdef BOOST_HAS_PTHREADS
#  define BOOST_HAS_THREADS
#endif

// The remote call manager depends on this.
#    define BOOST_BIND_ENABLE_PASCAL

#  endif

#endif




/* macos.hpp
IVpIV3X2xVuaZeynOTmy5EWFBmkWdIDum2QPBow9r5kDLUqwf9qvn9YsB62VYAWerKivWeBBut7JrkLvoZplonkLJqw9SMhCKyOYet6pXg6ZoZ1gnX9IWcX1gtbEoltKK7s+V3Jc77Ocg9m8mz6M4GvsG8zPpFvVZtH6fAhWdBtOJ1+bqWhHzLo9nN3Byv3EaTO8IaSrnNr5ON9z0EIEi9zty/n5n6ExJtknT7vt5WvljJzuz7gl+jsitCjBPt7x1QJ9nz2qazLpGjtLdU0mXWNoXwv1Yvkx9Dr38+fM6jthsnx3qs/gvu48ngfBtnxx8DbXGdo4wab0OnyT6/oHMywQbNz3AxI5PrQUsgj887f47/rzMS+YYalg3x/zyc/n4aJ6/sik85eB9otgl3cteMz3uEt4rZh086r0Y0lOd4XmaclK/hmi/07TFZrzIJs/a3NPrpdsMxwQbFSRUP1dyI/0HEdmqXef30mloEWxyecWrqrnlkw6tz5oZTSTzm2iPfCqfm1GQuL42r0b7dIsE+1XwSJz7lTVLPsn3G9KsGCfo+c0S/kZ570F+7pY2fKa+V8zQ0mLbhOeZLfhstxAE9It3739qGZhaLHiMW9VmqJZDlobk26Di0b8olnqLTMkC+myH/nl1cx2m+qMTK0zKsttqjMyoe8Jd6AB5RcFw0YMO4InmyzjdzN8DLpd7d+8m2Ypd6gNkqltULVstIeCfdPCu4Zm/v/AuVghvx9er1ZBs/R7ND9P9sG8oNqaZd6j+iRbfKT8Zc7PwOAPM5wQrOqZ7XbNfO5TnZGpdUblNDDbfapPMrE+w9A+Fexpa6+2mgXiJHSiYH6TqoZrloV2X7DxG2dSfgkOn0f6M2U02CMnvxeaRzP/R/Qelkx9D6ua7RHNu5EtTvlqs2ZhBukcj+h9B1n9Hw4U0CwbrZhgvn9fkqQZPKY5QDJ1DpBieEz1SabWJ8XwmOqTTK1Puoc/1q+/4ZCUtC3/V4f5Po2WKtih4W805XHBP9X2SSaNNXyeYN9j0u38pQ+68H36qRl8hXTrfEYN5Pye0v2BTL0/UDmfUX9GpvZndEw0bzZ5XJD9jO6pZDPWtBzF454/zRApWLK52A8c359UZ2TS/CfaPLIY/LPsp/UL8336OfUhZM0+z8zg/hoscEmwp0d2hPJ40GSBwlV0GzwsxJ/HGnUs6rMFWd2UvTncz9ss8LVgZXqHdOV7eF0L5BXsJ2VkJqdDs+hG3x7TvdElXbO507w4PjSzbtI+wRkuxzyUnUPrwUZAJto7ZCOc46W2Fy5o5qhnge2Ctev12yjNwupb4JRg37++4Tqna2CBW6V0q3EPFzGQ+fe3qOMJsoh6bQI4HdpgwUpu9eX8ctC8BQuqGdRGMxigxk6m7idA5oOWR7BL26+auCxSOqozMhtaPcHWjXhIfU98kgOtHNlIvM+seuyVoFk6WiPB9pkn7dQsB62aYIOeeZfSzD+Y4iPTr5X4UFuwnl8s2OOF/ELDgik/MiG/0Ixgyo9MyC80W82PTViLOiYH7WOyOBjX6MjItUGaZQ60qGNvsqjwgPWaZQ2ywAnBTr7v+41m2YMt8Eww22eX8/E4eYgFWlC/FI/XeO1pB97ltjvUAlMFOziq2FZu8/irZHsU3QpEfrqDjxlpgQ15dGu67O1GfN3GWaB9ed3KrV3zhj5vSm2CTFzfk4OWIORX9fu/d+axW5oFvrHoplSddoVtpQUiiurmfzyzMtsWC8wR4ms2eXAK57fVAq0EW7i3Ko1Dnj9P2aa3CWdjaJ72Xl3NMrbReSBLW/pmTc0yt1tgrUm3RGV4f82yvrLAECFd1/geCzQL+pr6ELK4m7ZimoU=
*/