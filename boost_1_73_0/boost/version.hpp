//  Boost version.hpp configuration header file  ------------------------------//

//  (C) Copyright John maddock 1999. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for documentation

#ifndef BOOST_VERSION_HPP
#define BOOST_VERSION_HPP

//
//  Caution: this is the only Boost header that is guaranteed
//  to change with every Boost release. Including this header
//  will cause a recompile every time a new Boost version is
//  used.
//
//  BOOST_VERSION % 100 is the patch level
//  BOOST_VERSION / 100 % 1000 is the minor version
//  BOOST_VERSION / 100000 is the major version

#define BOOST_VERSION 107300

//
//  BOOST_LIB_VERSION must be defined to be the same as BOOST_VERSION
//  but as a *string* in the form "x_y[_z]" where x is the major version
//  number, y is the minor version number, and z is the patch level if not 0.
//  This is used by <config/auto_link.hpp> to select which library version to link to.

#define BOOST_LIB_VERSION "1_73"

#endif

/* version.hpp
2nFY/X/Sjs+H2I9XNtqSbsfTW8YZ2dC0VnEGqORwqB8/dH6hAWzyik36qgH2TC2rI4trb/5GyV4ZbFuGS/4b/bzTgIngwZcgH3hBnODzgpr8JL37z9O0OYqkPXk9GvfSFsRoy8YIw+2Ult4CA318vquPT9DD/t9B0o10/4+pNYfqDK6+mpyc44x2jXCq6ptiFG2tKZ3LRZOQm8d/ZqivZV6qPTTISn8vz6S/l9rp7zlZ+Kvd
*/