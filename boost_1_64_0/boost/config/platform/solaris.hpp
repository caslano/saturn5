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
+sntbPzSlt9xWdCqCralVMpjzg+tm2DHHu0L4frsbwVvNvmb5aD+8nlfX7vEES5nf/m8FyvZoRa3M7QLgvknVfmd62WAFX4S7Md1Zfy4nMFWGC7YlV/OtOHrdqAV6oltvlOkg2NHCxQsZvXOD7mfGGSFxYJdTljWmcuCNkBoL+Vub7BwfiFW9ftUsviowQmcDq2EYD5l8n/MMYTI/WDJZG3tVm3wGWLl/QsmYzQ9Nt8/r5kDLVKwgVF1bmqWg7ZAsA437VfIcG7GCoMEs7RfvEIz/1D5mN5FzqZrlo72RCzL0gq7NMvGT/N2CPaPJc+DNcsKp/ZJtnnLbkWzoGG5x5eBNliwZpXrXNTMFmGFKYK9e2TNB/yMgDad7E2IhZ4jylzkZ4tIK/QWbPU/spbzswxaV8E6l2qzWrMguxWSBKt/5Ppb/PyAZlF0O9urdWvNHMOt6vMfWfC48qBZWIzan/Ex2295xM9jI3CsKBzT2vOP7prZ4qzwpZCuiTWCxih28I/X2+4UCIGxPpYvNMtGa23S7e1GwaO1+kxxYDkpvxRIgLPFMhO4LSVZ4QPBDi87skCzwLFWeGrR7cnSK/oxJ1thD+g29/fJ1djetKpzQWTfl85sy20+Bfslwe6kFfXmdFOtMNtLt50fHuM2n/G2FTZbdVPe3ziT22eqFcoLMUyblTcItP2CFur92VQYJu/rZ2AZBpZpYFkGlo02TtFt40rg/flgqRXWmnU7PyJkIMewHMc9gvUu/c1RzXI+sEJPi26fPNnVggzXZ2HfI6RLzSrcQLOgT63qewSy4e+E9tQscJ0VKgrWdrhjk2YOtB6iFS6rzRNBNtpQsmlgh59WrRyuWdh6KzQy6/Z2n3Kxmjk24vkT0r23J3aKZuloN4V06eVWx2iWupnaGdmGUb9/opn/VivME+zLod7pbNus8Hchv0+Knl6jGWzH+7uQ7rsTLetwOvyJk3OCPZzZ8S7HsNMK10C3OvlCbHxv3KX3WdMhCY5tuB3I99vdVhir6Na96a2mPN7da1V/M5FszJ2/L+D7yj4rnBFsx/H77/AY7KAVQDhmkc/v8L0447BVnU8m+8r/ymhOd8QKxYRjVn1nRyTHcBTHbkK60p1ut+N0x9T7LRndb2nfbLQAshkwHi51WTpNs0y0HopurUs/4nQZJ+R0F2uOLs37Np2g9kLW4eHl6XyOTuLzu2B7rjcI4n2bTtKYlizq5zaxXE60kybd2h6Iy9Is65QV+gnltHQOKsExnKZ7P5n+HV8sZKO1J5sJUbC+4OMWmgXilEMHwWpAkX6apZ+heSKy0r02bdfM5yzdN8m+tW88qVkqWpyi226viV58zPNWOCSk++KdRVfYfqD5HrKUToMfanNdYRdwbEr18taLvYve/FmzoEtW2AK6VTxcsoFmgZetsFJI93PlnxVOl22FIoJ9+LAK9WcRkPGjlddEzYIR4Hv5Wi3Nsn/CuRLBBvgMv6tZ4DUrPBJsZVSXodq9MfNXvN/Se6fZ0A4enBnYlt9J/cMKeSid8wJKmDyP3xc77mJfLti865Vt/L7qnhWOgm4t/W/p3+n/Qfd+svPTruvfhN63QmnhmCUWvXOJ33M9sEI2nT/ny7akJ2Wi+R30P63q3nZk+YpEsmU9sUJ+wWz2hjM4vmdW9T0JWdaA/sBrf/608nzyHFyLo88n1xqW+ac+9p4L9WyN299L1SzouRU6m3SbOnZtC81ywAtiBLOf7VmSj6l4qeNBsiKro+Zq5m/2gmDB1t5Ii9UsFS1EsKyE8vk087F4Qbxg4z9/cIXX8KBVJpuH61he61b8Lq9xQQvJq9uFFR07aZbq4wVHCuo2NW9iFU5XIfc=
*/