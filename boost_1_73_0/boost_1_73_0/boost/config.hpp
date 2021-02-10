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
2jgS/9+fYh7p20u6GALp9hpa7l1K0oTXLOSAXpvb7uPJtjBqjOSVZBK6ve9+I9kGQ0jS1yV96bXkBazRSBr9ZjQzkrX1eHMfZwvu/Azt/xA/+GsanEnxgfp6PfNw+AnSP2z0Hn/vGKIKixafhjtwZ4tPsG1bDLMxXpjn4fCOYd4bwcxX1TR8PzSPSHG2sF1LxDPJwrGG7dYO1Pb3n4EL9d16rQyHhDMaQV9T7lEZluFFYCn/HJOrq4qi/ygD1UCiiu1oMGYKlBjpSyIp4HPEfMoVDYAoCKjyJfOwwDjoMYURiyi0umfn7c5xGS7HzB9jHzORgBqLJApgTKYUJPUpm6ZdxERqECNsjX0HTGnsL9FM8AoOTUFTOVHYhRmcREoAmRIWEQ+HIRrGWseqUa36iYxQ8mogfFX186lXxnqSzeIcJZiQGYhYgxaQKFoGw1eGiQjYyPwiFEiMEy9ialxeiIID8aAqJCgaRdgVNmNUpSJT6GfIlA0XxCgt0+ZHCa7MSJdjMVliRAixk1EiOQ6DECBPIBDgMiQ8oNLy2knnI2RoWmhvUMlC1gAER0mgdNCHdr8EHlFMleFte3DSfTOAtwe93kFncA7dV3DQOce+Xrc7h6hvhiNJoFexpApHlsAmccRoYAfc3MeJCA8T
*/