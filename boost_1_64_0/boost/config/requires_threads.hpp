//  (C) Copyright John Maddock 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_CONFIG_REQUIRES_THREADS_HPP
#define BOOST_CONFIG_REQUIRES_THREADS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_DISABLE_THREADS)

//
// special case to handle versions of gcc which don't currently support threads:
//
#if defined(__GNUC__) && ((__GNUC__ < 3) || (__GNUC_MINOR__ <= 3) || !defined(BOOST_STRICT_CONFIG))
//
// this is checked up to gcc 3.3:
//
#if defined(__sgi) || defined(__hpux)
#  error "Multi-threaded programs are not supported by gcc on HPUX or Irix (last checked with gcc 3.3)"
#endif

#endif

#  error "Threading support unavaliable: it has been explicitly disabled with BOOST_DISABLE_THREADS"

#elif !defined(BOOST_HAS_THREADS)

# if defined __COMO__
//  Comeau C++
#   error "Compiler threading support is not turned on. Please set the correct command line options for threading: -D_MT (Windows) or -D_REENTRANT (Unix)"

#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
//  Intel
#ifdef _WIN32
#  error "Compiler threading support is not turned on. Please set the correct command line options for threading: either /MT /MTd /MD or /MDd"
#else
#   error "Compiler threading support is not turned on. Please set the correct command line options for threading: -openmp"
#endif

# elif defined __GNUC__
//  GNU C++:
#   error "Compiler threading support is not turned on. Please set the correct command line options for threading: -pthread (Linux), -pthreads (Solaris) or -mthreads (Mingw32)"

#elif defined __sgi
//  SGI MIPSpro C++
#   error "Compiler threading support is not turned on. Please set the correct command line options for threading: -D_SGI_MP_SOURCE"

#elif defined __DECCXX
//  Compaq Tru64 Unix cxx
#   error "Compiler threading support is not turned on. Please set the correct command line options for threading: -pthread"

#elif defined __BORLANDC__
//  Borland
#   error "Compiler threading support is not turned on. Please set the correct command line options for threading: -tWM"

#elif defined  __MWERKS__
//  Metrowerks CodeWarrior
#   error "Compiler threading support is not turned on. Please set the correct command line options for threading: either -runtime sm, -runtime smd, -runtime dm, or -runtime dmd"

#elif defined  __SUNPRO_CC
//  Sun Workshop Compiler C++
#   error "Compiler threading support is not turned on. Please set the correct command line options for threading: -mt"

#elif defined __HP_aCC
//  HP aCC
#   error "Compiler threading support is not turned on. Please set the correct command line options for threading: -mt"

#elif defined(__IBMCPP__)
//  IBM Visual Age
#   error "Compiler threading support is not turned on. Please compile the code with the xlC_r compiler"

#elif defined _MSC_VER
//  Microsoft Visual C++
//
//  Must remain the last #elif since some other vendors (Metrowerks, for
//  example) also #define _MSC_VER
#  error "Compiler threading support is not turned on. Please set the correct command line options for threading: either /MT /MTd /MD or /MDd"

#else

#  error "Compiler threading support is not turned on.  Please consult your compiler's documentation for the appropriate options to use"

#endif // compilers

#endif // BOOST_HAS_THREADS

#endif // BOOST_CONFIG_REQUIRES_THREADS_HPP

/* requires_threads.hpp
rhl0Ht5iGCfcJ6ox3CcifmPge+N8oTEuqJoPsw0POPTazcBNsWdt0JgKTSlefCy1gbbRwpoKh/H5J+LQEbZylzaZ79DdYxIRnx2nOCYT4/TPFh/onhLDVPfCNQZ9QSuTX1t/xz6oxeSNDLa8iOcUGtt6Y8Ag/s02g3JsPTU/Pzm1BO3SxKfmqJxTr7z6s1MQJXUja7r1q3cTgz9mQO0RPmE7fJ+fJfsjWr2bVLQMbgq8gZrvT848emURCgixh+5AzEAYrrgZYGZpQu7tPNHa/6jS3HOK1ducgH6A2C3+CNW3r4KDDU8GIigfyO8mXKA8FyaoWZb7RS6m4GgbukIwxqmmqPXh/unT0MT9sv6ZKB+Q56aBw37831Se5zHJOcsP1/nOflT7rFiLOOsnb4F76hrn/TTuNezZgPiIfSjgwT0kzrPjMbYZcezPmR0ijptwsHwPbgF8uL3/sv4OpdRESdtnBBzP7Rk+O8X2/t4KOKuXuGWJnDPXQw6vu7Avpjn51hGcSV5y6Avw+sN8KB9m5/MGw5y5Bag+xD/kMIe9/3jtDYfxpZ4qnF7j1+qOmre8bZhXby6p9YnuXlCnvBFwByeH82yyv7xE9rFvzHgsjbiPPcRhW72YzoM34Tx7//XSEK63eWlZb2cctkeLb/BvCpz6K8TV1BeM7/wOCx8sq30ErA7Y/qXV74S+B0a6Vu2PCIwKCH1Gd6A+jyuk8cIH3+6lv+k3VMwmzjsQabL71mgTh2EnenzPEP1yWBwY81H/WxkORUVsy61DDKK/pK6/TR6HCxPUL+AG5NTr1pmGgfq3bzI4nu0h9kbEMF7tfesnsLl44WV5EMhEqMFv8nHzc8fVid2Kfa578Ql8TRtVMswKD2XIphjK/JTKVKJI3SiIvQBlVOPC1SPuVfC4xbKUflFkrcxj4IIkv+MzzsYPX0SBF0VBFgoQqCfwynAdd1e/Dn34W7J+4IZZHpZadm7hKrIH7XBVpsgk0qL1HhweNpt9HJgHvkK1i/6d1D/q8uFrF8DhXscFxNnah61t3k7XNoXEtQ2+3XkCu4cQ5JEfubWdi2RlQeUKNTYJZwrQdvbU4UIKdH1XdzDgX/R9+yX187YmbgBhnPasge9QnevvxhNhPXXCtcw3N6q1CBha9tWohhNLPMvZ+RTE5070BirnunljT+3kzSzCoeTUfGuL662Gd7g33VNvs1q7Y3OGc/FdhnNqcEIZEmg0whTh7qjnp+c1RxsnNuogKqjn9YYDTyLqdrc0Vzc90tc9gfd1UvpeEvir7+tODRpf96pf+66qJ15xZLJanu0tZb3HOsuqAhxfaeaBCk9u2eBZkCUzanIPJj2WIA8V9hYqe7h3enG63ieFm7phfVd3rAnjbYa3NKfcrIER9tYJ+a0V/m6qh9jkMEpAxwc1pzbdscSiUuMfvQXGU+XqXH9OESAigEMYX9c4j6Y3uwiXHjXnTZqDClQEaUjAeYfmJPVLeGdh5oiqClPzZb1S0Hn2c80JakueulrpueX1b8nSUcfwjur7rdV3NVICRHKgiV9j8gaad5PWu2odzsryrIodMDEMiON+jUNxnlADEssQHcc/6DjSmj+my3X3La3yIvldQSXR4XzbTqe3uLCMwWC58TwlGQphXdY4jyvnQVjFLS09GGgbn81tuo+Cid+udH8J48MxkH9nm56p/mBlfspKEsjfTIfh6QHX5ByU7d9pHdXfIQ++ydoJDxh0RnZ+k3rx6P9SL/qPhXrRhP8wrceOc6C/B8omz/xiHwsb9J++qn6YzoD+Jn8GWo9Ua6rHKI8Idh7ejsyJ3jrcAox1YOTNruvkoQVc9CuyQfNwmgPp1WFtNNiMzm8=
*/