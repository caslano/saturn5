//  (C) Copyright Brian Kuhl 2016.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Check this is a recent EDG based compiler, otherwise we don't support it here:


#ifndef __EDG_VERSION__
#     error "Unknown Diab compiler version - please run the configure tests and report the results"
#endif

#include "boost/config/compiler/common_edg.hpp"

#define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#define BOOST_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS

#define BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE
#define BOOST_LOG_NO_MEMBER_TEMPLATE_FRIENDS
#define BOOST_REGEX_NO_EXTERNAL_TEMPLATES

#define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#define BOOST_NO_CXX11_HDR_CODECVT
#define BOOST_NO_CXX11_NUMERIC_LIMITS 

#define BOOST_COMPILER "Wind River Diab " BOOST_STRINGIZE(__VERSION_NUMBER__)

/* diab.hpp
/xhC2YkoRAkWGpwjGtUR0sbqNyI7pHBQ3IwF6+dU56qzHwgq6Uzsqq6nomiUDmoxgVVSz+/Uhk4uEiwKWH7zfBS+fdsX9J2ph+gR4TS0bxRfUYPG6QkixnT1EDDNI3fXujkfWV15lIijzsGYJGE5tqhaO9KL+xdJpMH4cL0oUrApQ8M7yRxfV8ERFI/WBijeuAFH1+d5TnioEL3fTjypsECKpUkXnruKvlbTjjluyUjaPpruekctb1AihGfbrBuqjM1XYnz6AxzWkYSCVemDMf5M9qbgas1WUc7kc5ko+ZoH+t5XiYOpwVhY3a4Ms6peoHqT0MpSqobU1DCepOgtauNmIJZ1RBKDdCo7WKiHkIB7aNvCaz3jB3Ns3RAXcIulH3TdRv3SvugWln4RX9BahbH+/KJCTo3287IZo4s/DBunqsTtBt6xJUJIAheBuuyxiPUBhh5IhMEupRpMsbpMREJ05e6Tkd4et/D0SSw0U7523J1t9He3aelAXYEoctwND9SLpxaF1reCZCXJ1O9PxT1SQrvg5+Up8zd0cXa51P9JI1MTJm96+ciGrg==
*/