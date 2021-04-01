/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_ALLOC_HPP
#define BOOST_ALIGN_ALIGNED_ALLOC_HPP

#include <boost/config.hpp>

#if defined(BOOST_HAS_UNISTD_H)
#include <unistd.h>
#endif

#if defined(__APPLE__) || defined(__APPLE_CC__) || defined(macintosh)
#include <AvailabilityMacros.h>
#endif

#if defined(BOOST_ALIGN_USE_ALLOCATE)
#include <boost/align/detail/aligned_alloc.hpp>
#elif defined(_MSC_VER) && !defined(UNDER_CE)
#include <boost/align/detail/aligned_alloc_msvc.hpp>
#elif defined(__MINGW32__) && (__MSVCRT_VERSION__ >= 0x0700)
#include <boost/align/detail/aligned_alloc_msvc.hpp>
#elif defined(__MINGW32__)
#include <boost/align/detail/aligned_alloc_mingw.hpp>
#elif MAC_OS_X_VERSION_MIN_REQUIRED >= 1090
#include <boost/align/detail/aligned_alloc_posix.hpp>
#elif MAC_OS_X_VERSION_MIN_REQUIRED >= 1060
#include <boost/align/detail/aligned_alloc_macos.hpp>
#elif defined(__ANDROID__)
#include <boost/align/detail/aligned_alloc_android.hpp>
#elif defined(__SunOS_5_11) || defined(__SunOS_5_12)
#include <boost/align/detail/aligned_alloc_posix.hpp>
#elif defined(sun) || defined(__sun)
#include <boost/align/detail/aligned_alloc_sunos.hpp>
#elif (_POSIX_C_SOURCE >= 200112L) || (_XOPEN_SOURCE >= 600)
#include <boost/align/detail/aligned_alloc_posix.hpp>
#else
#include <boost/align/detail/aligned_alloc.hpp>
#endif

#endif

/* aligned_alloc.hpp
P7sKSpHSDyp5LZmYna4CmNEK2G3x0lo9rtQT5UPOwzPGN+mT5NbKVzgvcAHIoiUqS3v8ShobXhnrLP5VlG2pZtLwt4GQ88YpmPWu3+hs3BEzoJkGprDe4MF3kF2C6YOPg5OwxL4fCmY/H6PM9E/GTbO15DsB7TOJO2QYQS5WKuwLeILLfSlJene+gHS0T/dSvd/OKQUyE1rGMnTFOVDZ8VhdPgRWYK2pDQvAJvURAg6tZ/FB9lKCK9Vvs3b0NoqR7W9uxX9pl7C6KN4jorXPiZk19LkWFnwS+RiuulZJ+uRPctkN18TjT+BWAWYW6tM4RaNMwyOI36EzJATJXyOEu5+rT0FvVrjw5l3Agd9xOTC0D53C7G3fHhAijVpuhxE7IrOHAT0iTNl8j/wW9CR2cbQEcgFny80qXoRpm+Tc8JLTj/6J5r4pot8SjVuGAe9howJGzbkkIvuKndcw7Lwv9r2PsVzcdGPbBaTvY4TD+y1u4aymQBziUw9QJ8Q+P5/60PMFS3ey3uyRlEKCce1WYYaCahW4Y01VtpoYmU65BoN3D0rXstL+j1W1HA==
*/