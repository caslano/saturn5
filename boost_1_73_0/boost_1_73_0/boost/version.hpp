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
9oAMtoPG9f/RcAGGdxfCkJiNhN9NqNsmoW4LhHbaJLTTAqHdNgnttkCo1yahXguE9toktNcCof02Ce23QOhxm4Qet0DooE1CBy0Q6rdJqH+X0H9QSwMECgAAAAgALWdKUlwpwoGdBAAAoAkAABkACQBjdXJsLW1hc3Rlci9SRUxFQVNFLU5PVEVTVVQFAAG2SCRgjVVtT9tIEP7uXzFfTrRSnBdDEojUOwFHgWt5KQ6telGFNvYmXsXetXbXCblff89sCNCqlysfgtd+ZuaZeWZms8aWJHROpZpm/DxsD/vtXhTRbTMtVUbhpZWlFE66EW3/ekfDiE5NVW1stSRTe2X0K0iyDwibP8B2/eCkB+TN29fA5LD/HGjW6Cx8IKW3bIBhxKnR3qpp44195f8lTjKIonGh3JYnPGRlk0tHvpA0M2VpVkrPKSuEniMLZGdo6Us4U1p5JUpSVV3KSmovmAOZGdnGAUFTkS0kcpzsf/u1INNmPlOP2ygn9+fxyc399fjrCIaVWco84DNjamk3wTgs/jN82qgyHxEcUBznyolpKeNceFkLi5CT3rf/RBXe17FofMGIrBILuUEgM2M9V9QKuyYtKmZrSRsdX6UgUtWqlJZA5IvSuVk5hOmGOEG8qim9mq49uxNlGQpC
*/