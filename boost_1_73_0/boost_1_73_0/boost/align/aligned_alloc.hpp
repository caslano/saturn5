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
C33oy+wku8k/FVmeLZt6Mi8W2a1MKWOfyIilDfUV1tsU+vFktc7k/UXRTMt8nrWr5bJudA1x8v1H2ev6Voao1lkub67a/uL2AcW1DFjtdNzGajnLOwFCPpysqtm8GE2bTp98/PASp3klX0yxxduyu7Fhn3COnTY7Pjp6m1WrxaRo7KunXBG30K4mi7LLFutsmXdTf/dZfIA7sqPMuhpPvrv4WtDh8Sg7qdoul4M7L+ay4ll2potqZZDHghzTuroqr1ey5yuBXytrlZPW7ct7XTnFuE3elIW+8Th7WdvxZrd183E8WZXzGfeU1Z2APbu4OI3vfM2XniYv+QFcvDv6w0W2e/7qKNv/6vGXexnW+2SUvW/z6yJd5ROsUt48yHb39zi6IOisbHN5YDbIbrpu2R4AWX3oYsa3Hkf4dIUAwIHTFO1qgePpmrxqrxTgT4j8OOGixRkD1nXbAQwKjOErblefffpDQ68q+b3tBG9fXZ4R7fJq1upLel6KB7b8TACWHU6nxbI7yD4ff57dFPnMF/T8AaAdXpwNsu/enMqP15dvTjNBYv77qWjasq6yP+urX2RHnGbVFmFts2JedMW4Kaqcu78qOX9Tr65vsFp988sf2NlVPZ/LF68vZVtNMSubYtrZvr6Kr4T5ygoQ
*/