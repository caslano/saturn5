//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org for most recent version.

//  SGI Irix specific config options:

#define BOOST_PLATFORM "SGI Irix"

#define BOOST_NO_SWPRINTF 
//
// these are not auto detected by POSIX feature tests:
//
#define BOOST_HAS_GETTIMEOFDAY
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE

#ifdef __GNUC__
   // GNU C on IRIX does not support threads (checked up to gcc 3.3)
#  define BOOST_DISABLE_THREADS
#endif

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>




/* irix.hpp
2nwsM/r/4Uzlf0zPo34VbcvMU+uHaLlriRA926sYaruvcp/t//udVK4axtl3uUQ4/pLklHlexHoq+d0X9VRyLphGQvh9bssFc4AgflfLfDGXWCx+ld5o2F6lUeflR0b0ONhWYecl33/vWXitKcJsvywjyR9Hl5hq+uC7TDWnJuPFVrl+1vrVVrnB1nqZtT7MWh9GuleR5PfbapL85r+XJI+UXE9yMckNpsrx8iuSj5PcSHIPyc0kOfcZdX7C/yA=
*/