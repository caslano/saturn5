//  Boost config.hpp configuration header file  ------------------------------//

//  (C) Copyright John Maddock 2002.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for most recent version.

//  Boost config.hpp policy and rationale documentation has been moved to
//  http://www.boost.org/libs/config
//
//  CAUTION: This file is intended to be completely stable -
//           DO NOT MODIFY THIS FILE!
//

#ifndef BOOST_CONFIG_HPP
#define BOOST_CONFIG_HPP

// if we don't have a user config, then use the default location:
#if !defined(BOOST_USER_CONFIG) && !defined(BOOST_NO_USER_CONFIG)
#  define BOOST_USER_CONFIG <boost/config/user.hpp>
#if 0
// For dependency trackers:
#  include <boost/config/user.hpp>
#endif
#endif
// include it first:
#ifdef BOOST_USER_CONFIG
#  include BOOST_USER_CONFIG
#endif

// if we don't have a compiler config set, try and find one:
#if !defined(BOOST_COMPILER_CONFIG) && !defined(BOOST_NO_COMPILER_CONFIG) && !defined(BOOST_NO_CONFIG)
#  include <boost/config/detail/select_compiler_config.hpp>
#endif
// if we have a compiler config, include it now:
#ifdef BOOST_COMPILER_CONFIG
#  include BOOST_COMPILER_CONFIG
#endif

// if we don't have a std library config set, try and find one:
#if !defined(BOOST_STDLIB_CONFIG) && !defined(BOOST_NO_STDLIB_CONFIG) && !defined(BOOST_NO_CONFIG) && defined(__cplusplus)
#  include <boost/config/detail/select_stdlib_config.hpp>
#endif
// if we have a std library config, include it now:
#ifdef BOOST_STDLIB_CONFIG
#  include BOOST_STDLIB_CONFIG
#endif

// if we don't have a platform config set, try and find one:
#if !defined(BOOST_PLATFORM_CONFIG) && !defined(BOOST_NO_PLATFORM_CONFIG) && !defined(BOOST_NO_CONFIG)
#  include <boost/config/detail/select_platform_config.hpp>
#endif
// if we have a platform config, include it now:
#ifdef BOOST_PLATFORM_CONFIG
#  include BOOST_PLATFORM_CONFIG
#endif

// get config suffix code:
#include <boost/config/detail/suffix.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif  // BOOST_CONFIG_HPP

/* config.hpp
S80WINX5ofBDuOt14RtawaOGHogTIKV9KZA0pIts70y1P1xtWYCIcDbdjwgYC/Zc15riQz1aLN0tcRT0W/SqeZiV+K6ptiA7Y/zrppX1J/rYncvmGr5vdO0so9VCEarubtxseCO/t/OArqWmQl9EZdyQCcXBiwCCzimFUYAVuSoEGs1OPxVoneHYirFB9kuDpG+8aBCb/nbD4U4iJwn7p46n8HS4+nOMhzWHLwAzoL/2saX0NnB9qha87/y9AcHRnVV4WH7F1SbrTuyLRV2gThuKiUpfw6NdGlmrvNfpzYrbecSrNY6OfKhmKjpbkNHMEDBENEzo+TvsElSrZzmANwCjkcaKAr2LyakkDokYS4FNOyCn1k8VC2Sw2EBaQusN8Pl+EmCq5AMFl6/b3wW7i4mWTvhZkwZKsxyK5/PAYY+0xZdfYjB2bOe6Ya2jimm7mCiO0EHlMqd3ysXpuutDZ6dTQSOHa9b5I0gRFHm376Ci/bxXdLmzputAH/qaR1oHvv2WX2jrSBBzIPhrJDcIynUJqXbrYHWZNuYqYJT5sexDdgmt9x22XA+Aqw==
*/