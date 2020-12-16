//  (C) Copyright John Maddock 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  cygwin specific config options:

#define BOOST_PLATFORM "Cygwin"
#define BOOST_HAS_DIRENT_H
#define BOOST_HAS_LOG1P
#define BOOST_HAS_EXPM1

//
// Threading API:
// See if we have POSIX threads, if we do use them, otherwise
// revert to native Win threads.
#define BOOST_HAS_UNISTD_H
#include <unistd.h>
#if defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0) && !defined(BOOST_HAS_WINTHREADS)
#  define BOOST_HAS_PTHREADS
#  define BOOST_HAS_SCHED_YIELD
#  define BOOST_HAS_GETTIMEOFDAY
#  define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
//#  define BOOST_HAS_SIGACTION
#else
#  if !defined(BOOST_HAS_WINTHREADS)
#     define BOOST_HAS_WINTHREADS
#  endif
#  define BOOST_HAS_FTIME
#endif

//
// find out if we have a stdint.h, there should be a better way to do this:
//
#include <sys/types.h>
#ifdef _STDINT_H
#define BOOST_HAS_STDINT_H
#endif
#if __GNUC__ > 5 && !defined(BOOST_HAS_STDINT_H)
#   define BOOST_HAS_STDINT_H
#endif

#include <cygwin/version.h>
#if (CYGWIN_VERSION_API_MAJOR == 0 && CYGWIN_VERSION_API_MINOR < 231)
/// Cygwin has no fenv.h
#define BOOST_NO_FENV_H
#endif

// Cygwin has it's own <pthread.h> which breaks <shared_mutex> unless the correct compiler flags are used:
#ifndef BOOST_NO_CXX14_HDR_SHARED_MUTEX
#include <pthread.h>
#if !(__XSI_VISIBLE >= 500 || __POSIX_VISIBLE >= 200112)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#endif

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>

//
// Cygwin lies about XSI conformance, there is no nl_types.h:
//
#ifdef BOOST_HAS_NL_TYPES_H
#  undef BOOST_HAS_NL_TYPES_H
#endif





/* cygwin.hpp
2zjz3/J4Wf8MEK3kmPQKy+O5erBHuL09UBZ6eC73IuB7EUCUElyQvhH38si3G1ohY6Ld3hycWcj1IN9bxXUhdl73dx082h7iYpLc3lFyHlQPLuMI4HEEQKQyTlvT6dl+MsH9/aSWBcDLxkwAEUo6zfVt88w3TVohxya6b/fpf8vjZWNAgGFKu3x0v/DCf+6BekiKrxsSru7Q6LaPO+VM5DYhjzOBx5kA4cqcgvqebiU9VheR9WJCo9zXKKRMqC6Mxrm06jGAok/zzG9jacXETt19O4TKmch1IY/dAWakTqSRVKiywkJjbLNH28VotzcKyoHHUzVMkEbPZwUAIKBXq3lqlEOVFnRt7M/jyX4iGid/3Lbzo5SHdP/Eh9vfqC04wx5ToiDtijpE+SOP9m2RJ9tCTL1I9/cRlInLnjtNTTCG6qIQ/lm0bbnmqoYotga0S1VRT7YJN25mp+cg7xPRw8T72BXGP8f96UPfmg1W5hSj737y/Xt7MOF/Mjaa4Bqlda7L3ri77AHNsjJM8ESwxOONl2jms8kEcSbdrh68PFmz7C9MECGka7tr31LNwjaboK1gvy2ePEizTLRegnXcPaeeZrYt+F/B1gXe/0IzB9pBwfJ9ufIG21Yac5NNDYiqpFmKi+3940GSZqlohQU7OntjDNcZWgPB6kwddUoz+NIEBQVruAumcZ2hBQi2cEGlZM2C0KyClb54rRnXmYuVa1dzJMeH9rputIchlROtjGCZ0OoBnyO0QoL1u/B7VY5hW+7mj/aeWNeZe8rzMdH82GhOjgy2527+BhZoYGEGlpKrmSF9u94Gy4CZ9xIxgQKwwwQTycqiVdsRUk6zdLRgwerZi7TWzOcrap9kU6Y8yaNZEFoZ3dTzQJaCliVYjQV7KmiW+rUJupl12zE/8ZRmGZkmcJh0u9DCP56PudcE60G3uzNrnNMsbJ8Jllh0W/+bmdP5HzFBtpAuJ+5cpGaBR7FNCGVp28YvlNOdMMEHQroycwY30CwHrapQzmIb/7mVy5KlniMyOkcUg4GlG1imgWXnas7JOhM0JysHCpz/eXFpnqdF6yhYm8K1H/CcMdowwRpV2f0bz3t/S9ctWceLjdkC0T4VrP7Q/b/wM8B3JogU7PDeaXv43v9d7sfMQDMLVr2/H5cz08V8U4N4XjgLbZBgvx7/xZfLedoEDwWr9k5vP773njFBd8GOjLr6FY/V0CyC7Usx1eLnXrQQwb5//wN+T+I4a4Jqgn2ZVnY7x25gWWg/mHSzVm+7iuvzPF5HQjpbwcG1OQY0X8F2XBlZhfNDqyEc8+iCz2fxMS/kXpYgtDK60fVO+aFtFev62cqNHPtF6l/IvJ8kV+X6RBsiWPM53bL5/n/JBPXJyqPNGd1wPMeA1lSwYmVXdufzgFZLsM+m9u7IbfcyztHk1W1QWskK3JZ+M0Exk26Dm4XGaX2r/00TfEvH9EebVD2hhma2WyaYIdilrn/YNctGq6jotuVeixuapd4xwUKLbrOrvWfTLOi+yXm7YpuxvEwBzVIemqCHkC7Jd9cOzXKequeIjM4RxfCM3h+R/bQ3fx/NMv7Esgj29c7PNrDh/78MujULaNVMsywTth/B9lUbu55NUeBHweqkxU/mcpoVaC/kN2fZxCJcL1YFQoV0replxGjm46VAB8GqdC7yrWYOtFGCLb04YL5mkEeBkUJ+Eb/WncXl9M49v6C8CnQVLLb466O5XtAGCBZ1rEoLrut8GJNZt01PjpTi+AopcFUoy/j3JjzmevFRwA/YpPu7T5HczWZgQQbmMLBUA8swsCwDyzEwn6IG8ckmx2dgDtnk+GST45NNjk82OT4D83nNID60pYI=
*/