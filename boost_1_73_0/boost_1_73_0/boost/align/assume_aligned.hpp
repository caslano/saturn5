/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ASSUME_ALIGNED_HPP
#define BOOST_ALIGN_ASSUME_ALIGNED_HPP

#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#include <boost/align/detail/assume_aligned_msvc.hpp>
#elif defined(BOOST_CLANG) && defined(__has_builtin)
#include <boost/align/detail/assume_aligned_clang.hpp>
#elif BOOST_GCC_VERSION >= 40700
#include <boost/align/detail/assume_aligned_gcc.hpp>
#elif defined(__INTEL_COMPILER)
#include <boost/align/detail/assume_aligned_intel.hpp>
#else
#include <boost/align/detail/assume_aligned.hpp>
#endif

#endif

/* assume_aligned.hpp
zXxm8MVVtFAt2T48vibs6zUHGTEuKrhC+4weh9v/fm6OQyLwQXZcp7ZU+kAY1MjTwY5vSvgfQEY+lhR1iupa7qjaRQQIMhz1jd5t9IhWJ48EfSQO+RwW7bxT3KuibGRSzsED1982knDHH0vUAIZRv4TUL1dNbQt6oMFGgWi3j5UMcePDhOuiX4BwrhVHS02dMA+Z205/4ljB1ArKD15ugwfpfm1cFDgDDNCtlN1PHD+J5ZVjjksNehjcuPDa0DyF1djQohQ/fvT4Ec0AoGALxpMyYJwxYDD3QbGFvRImf4hAggUQlGwWdRNB8wRK0yZoWPnT8mR0Ed1mwMBtscMwkWmJTZGd17ALFIslf7XgG+AwDA86NHSzXRfVhADLter2TD7gUACqW/lom4K7ZZpTKM10UXpdQTlh5exUhdHVqP+pgJ4PowNeZrrGwEHMsFQjFFSC1Hz7pv6HwCzHyNHSC+s6JFe6t3agTzgPzmYr9dm4LCHqimp79Sx3XYwYEAR3C8zB8XuewsXABIlNuyz4lRs5KFJrbkRxla/m3SYwFBXUtjYrCswAQRwwpIKwahFb2t2sDQR4GgqRutd2SxDbXBRyOozskPZ8/jgmTTITUNU5YewWiIryTvmJaAOEtACU+xK++6JA26veIqBz
*/