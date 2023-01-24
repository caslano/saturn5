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
I2rh1OohoLTa/LxiDvpkICsyz1Du9wS5ltkKTNfnZ9bKXGZJGzsPyF8GKhPvQ7nhAoWUoWUBkpwWnlZWezeXWqQbl+Ja6eLsmULjKtoeIiVhCzzWC/j3dyG9O7hAnGYMOXqFGicwt6IAY1EnSanhzBqwPyhZeD+x+9HdM2oOpTHYKdIaEzJjkFHu6EZwRSavzUI/+DFDdiqO2UekTRHTaenMh1Fp0JQO8LpwHmKAmkkuXF36xVGVLstuXSrxsMhv6euo4OjiNtvsVi4g/ZKKycV72W5N4oBHaPRoyWXteQ1rrwWKr3fWmrn33Fo4AdpScn/0XD8SsBzME3NTEw2gD6HuzV0BRQPZCAlfvuR5LRgejbaAyAJvwmazBbXeSykXGK0nRuq7vHwJ3gqy1hKr6svMydyXe6ujzZckDN7uBzOARjLNDyLUP1GGqUhl9Pk5jJd88IvlC9SWVG1v0A5KTK3PnnXBh2LvBMe2oZfssvFVWD5vEnhyh88V0yWrp4/Z7OkM/cz8bvzCr9L4UYlTjjZn2Uygh2hXqXIGszBHPWoX8rGhCTW5/Sl1vtFgae/IeJMTq3x5DyLO4+D+QSOlyi+h7mdoAv59LXakhrcmaMMFdPutBpF8Ycy548t7YKHSzdUmYSqV3kVouS0rH2V40znm9E3kYDGn2efoV8PhTeryVZjW+XFVblrGTjrf6EKrTOh1lqz/o7Krm+j8
*/