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
P8550O+X2nZu22q7dWk43pvwmROiqBitsiQ/3ChFtHj1BJwx1yBAV63IFk3PeSe44CWh5nXMFHIPAm53u/pwRG09rydsROynweZGxufw9wn7u0cwR4Te4MUngeIASk+213XaHOm/sMWWPTigjdT47c0/s7tSH+D3IiNA63F7mlNLOlcv+R69TqqQ//XsG09zZvIQjXlwuCpqaZoofP9Crrz+9DNi+IBxwmZvHbzUZ56QUS0H1n85lwwldfzX+FKaMpYG7ZM9p4PmY+xe3unu8GODv4Nr/RdtLKRydHd1YvE0UVwrEFZY3dRU0Yu0rIYnYyVST56lNDRDdh+UZygM709SAobAj6YIc6ZicNkWfzeXyoErPl2eHzCv+wnJg1ykalJsh+7L6kYfm7kIbHhC+6rHSdk5zNLzKhQHhj4oJMlDxn6OwwEGgP74YStxn6AFPHAcrwaOh46S1ti7Fi8LtAzqWH8ku91qRjlmAhxGJnPcsU3i1UVufleJnRrdAr0JpYTS2crTQLiR1EUC1F3tmcG3Zru4VlPebeUM5qkIFm2qZJSz+zE/r2UfYQ==
*/