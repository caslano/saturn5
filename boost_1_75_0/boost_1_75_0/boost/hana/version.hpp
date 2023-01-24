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
93t0CoiafSsvio00cRiYNXe//8igCYHHcPd4QSdLGRQMngBGs+LioOZi/0wcQasrDfodQfKyfzMNvew72c+t2vCkCeDxcdEJ4NOJ2gSQ9Tbx3SAgwTfyjUXxBoOL3Q4fg3FMnag73uNW62smovTUybZ9K8Q43tdgXIfGWMd7w/7zcbDDd0RtJBVtqnSW72ppxHe1Dx3vD6bQlDk4X58yuet9W4pmDXl0qRZMvzttyFqXu9ibACjzV3TYA/a+klMvenDRzRt24z4ajDuYBmVMb6LVE5BdBbfbTbtyklJvoR5t40/JuF5OdylwF3xd2yJltAf0qN8z52sLR96wZycQ2ppteEaEs7C+LsVgYOuyYhYrcakHOFzvmmcxiXJbD9RTlWy4H6TWcxyUzdNJaELYfJx8WJ48ztf80e/qdrgPX8lJroOC3Rk3jOWSK+gL8H89RuLsehv6TY2nyMc2LfIxAmPPPBOGhvP795+hOK7HMULyFuMc8YHHaMWz5jiZCOv4z+P447Fk4NgaO0xbPTduyZL/iukM0uzwa5jS73gp/Bqm9aRkIDn94tfc8up4iRfmZJdESouJCD/ZMyMD64atYmZI4dLur8LU1Fh7K8qH6GN3/3G0fPrg+gbFwqSa+mufwiVul+LHaij+dXStwmKSHqUhKY16A5cpXGxnM9pVErMa14/wzBWEKnYJvqCP/lo0zTq9Bs+NWB8OM5z0
*/