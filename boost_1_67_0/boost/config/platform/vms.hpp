//  (C) Copyright Artyom Beilis 2010.  
//  Use, modification and distribution are subject to the  
//  Boost Software License, Version 1.0. (See accompanying file  
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 

#ifndef BOOST_CONFIG_PLATFORM_VMS_HPP 
#define BOOST_CONFIG_PLATFORM_VMS_HPP 

#define BOOST_PLATFORM "OpenVMS" 

#undef  BOOST_HAS_STDINT_H 
#define BOOST_HAS_UNISTD_H 
#define BOOST_HAS_NL_TYPES_H 
#define BOOST_HAS_GETTIMEOFDAY 
#define BOOST_HAS_DIRENT_H 
#define BOOST_HAS_PTHREADS 
#define BOOST_HAS_NANOSLEEP 
#define BOOST_HAS_CLOCK_GETTIME 
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE 
#define BOOST_HAS_LOG1P 
#define BOOST_HAS_EXPM1 
#define BOOST_HAS_THREADS 
#undef  BOOST_HAS_SCHED_YIELD 

#endif 

/* vms.hpp
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
*/