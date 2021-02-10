//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  sun specific config options:

#define BOOST_PLATFORM "Sun Solaris"

#define BOOST_HAS_GETTIMEOFDAY

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>

//
// pthreads don't actually work with gcc unless _PTHREADS is defined:
//
#if defined(__GNUC__) && defined(_POSIX_THREADS) && !defined(_PTHREADS)
# undef BOOST_HAS_PTHREADS
#endif

#define BOOST_HAS_STDINT_H 
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE 
#define BOOST_HAS_LOG1P 
#define BOOST_HAS_EXPM1



/* solaris.hpp
6D/n3V1Pr2oJk/kU9t6//xPewP7u3oEDJzmjpIFEErYh/ZUDR6U++avOb29dQT45QCTkjfsEMK2pAMEreZP3BHDf0IIwQUrIBZREFD3d4AtlIGsCFW0IzMNo5Qd/O3BT06Iece74AKLmQ1NCnV8T6ElB6LWB6fJeAq8QAfFLKiRiDpJy5iI9AUn6VowwKoi8ERzy65w2+Qbpcgm1lJ34MJsVQ99gJrOSF2JWbKVwa9l+l9UKo2nzO+CdBMlhEMQBZe9Ay0taqRUlwsNu2DRU1M5jWEjIyhnvQZCmGeHQlRJhUiCQjGo5yhI6jJ5KtQjOhGK7qXn7xBBlHYGqoWdIh7KgXclReAcGVpJe22shtiyjylryH5TsMfYSOMOowPYS8BMbNrmgwoFLPz0NL1K49OLYC9IVhJ/BC1Yj3pkfnGBvUGTtgdx2PREYRQ+07RpKyifkP3XSLTc9hflFvPSDz2EWxf65F6+yKIxTeAv23j4kpFPN/YcNdkM3qvpw4L575+7igXrLSC7usisiKau4Kjb2lEDY5BQC73xhvYy9fgPookVuckmEVH2OELlyh45js7KhxRnSQMkqCKPET6xfKSuaoSRwpKhNL9afLE1ScDx/FtFE/QU7NbZJg93yYjQONJxdwY6i7aaHmvJk
*/