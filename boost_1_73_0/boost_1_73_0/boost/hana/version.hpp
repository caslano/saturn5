/*!
@file
Defines macros for tracking the version of the library.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_VERSION_HPP
#define BOOST_HANA_VERSION_HPP

//! @internal
//! Transforms a (version, revision, patchlevel) triple into a number of the
//! form 0xVVRRPPPP to allow comparing versions in a normalized way.
//!
//! See http://sourceforge.net/p/predef/wiki/VersionNormalization.
#define BOOST_HANA_CONFIG_VERSION(version, revision, patch) \
    (((version) << 24) + ((revision) << 16) + (patch))

//! @ingroup group-config
//! Macro expanding to the major version of the library, i.e. the `x` in `x.y.z`.
#define BOOST_HANA_MAJOR_VERSION 1

//! @ingroup group-config
//! Macro expanding to the minor version of the library, i.e. the `y` in `x.y.z`.
#define BOOST_HANA_MINOR_VERSION 6

//! @ingroup group-config
//! Macro expanding to the patch level of the library, i.e. the `z` in `x.y.z`.
#define BOOST_HANA_PATCH_VERSION 0

//! @ingroup group-config
//! Macro expanding to the full version of the library, in hexadecimal
//! representation.
//!
//! Specifically, `BOOST_HANA_VERSION` expands to an hexadecimal number of the
//! form 0xVVRRPPPP, where `VV` is the major version of the library, `RR` is
//! the minor version and `PPPP` is the patch level. This allows the version
//! of the library to be compared:
//! @snippet example/version.cpp main
//!
//!
//! @note
//! The major, minor and patch versions of the library are also available
//! individually with the `BOOST_HANA_{MAJOR,MINOR,PATCH}_VERSION` macros.
#define BOOST_HANA_VERSION                                                  \
    BOOST_HANA_CONFIG_VERSION(BOOST_HANA_MAJOR_VERSION,                     \
                              BOOST_HANA_MINOR_VERSION,                     \
                              BOOST_HANA_PATCH_VERSION)                     \
/**/

#endif // !BOOST_HANA_VERSION_HPP

/* version.hpp
IzoOZZkrCNIW5Qk/j+zYbBWyVyJ6MckdwaW/Ra8WzEWlmag0D476kj+Pzre82fakhyX6QulF+4pUV4ZeS3LO8Mv2jf8c0ntbfnht3iNNekNkCe5yViJKEUlKCCI9ewQOw2MQFubjNpQqvJS1Isjj9A+GVQBpvo9GdAMeBBr0FLT0OGgdjYlUB71F7EiaoGhyQoMNzyOjihAevIJTJwDW6asgCeVizi/KCsR0ofvXtSeDXhHfV0CDaBBV65oPK6uhPO/8/+V3FnPcWdL/Rj6tVS7x0kaOix8+SJexqZIsSW/Tmw0HiPp/DxS6+BDHb3OmHmG7/4Uzm5cOyTP6oGkLLe+EbUXPG5yKBc9Nl2QSReAMhvY1k0JN22wxOQO1Nh/BIboI+kFZ26aT93LFxHOAHR2+RrctffIh2s3JmP2pXNXx6eHbD8ZW5oAx8JgfTmORZzKAnFezoE0FuTSr+c3URfsRmAiRns9obL9XBZYt51dikwUsUhXPANHVSpwAC8EIn/1pYITzTdWPxydcKkcafFYB4Y99YV/I/xDN8UA8j1pNWALP3zWPmmdnDc6JuEqZzAY9QplJugmidyN/cSqltTAXS5T0R5QPCtMwZbSVIr/OgKQOi0u5ergSOPCI/8pkuFhSsqN8INqOZdwR
*/