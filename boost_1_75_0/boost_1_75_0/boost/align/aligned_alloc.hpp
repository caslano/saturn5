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
HnIOpm7SfuoDv5oQaDtmnId2MdnCrBkp8QTx/iABS/iAabNtVXwy9cavF0Lby50fRD4fJhAs3FKwcS50jeyZoY0XWXdbl9Auhi4iN6H7/lE44y/Iww/P6rtW+V31CGa3x2fPteyhXI76qxLACM104mxdG89H3YgCn6fuLwqUWvz5oUFmWi6JwJ6JSLC3mvi6QDtSrGT+vAOVK1Jg6DVxTxO5JbtLqlQgm90uTb470H9eFeXV6+m62A4eL12/QR2X050KUREMuPYFMaYxnrGlATjnog7znAl/0cRMUd6fy5qLsnH+8O++ZIs73/5e49NjwX2wsapkRKtAXnFyjCTLBZB9Gl8ojjkwByYBwuvMgzE2Ol5f6R60l9IhKy6YhVp63Uf9Ykw++jN9vz1JA3cxhPrBsTxCNA72ETGNwTkanqqEokx1V3ddp86maIdqW2WcgbI9vNpEY52Orx6m/SFAUYYizjbqFOE21LuKswqmPDEaudBtHsddQT3qkVynBl33g/YwVo8knIFrrskAS5vhVAOdpNwR8j7EiCjiNvsM5XqpQ4z1JM3smf4XEcNlh1I18UO6MGvx3Y0a2d8eFbL6gEVSC6fXD8sEN0GuqfoiC6rTvBHwBCGxgB/P/B7gakX0KvfGXvzqi4URY8YsH/Gl4Prwx4WQiAib4zHNJuS4XlwIjUraxIZf+OuiLJFeu6/3vPNN0jLHGCANJkvH
*/