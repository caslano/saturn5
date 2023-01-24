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
8imzQtx+h0S38DSahAxIwKOQf8t2IAEn/Er7S+j3LKokyugX2jtihHzMxwsq2WzEA7gdyizjwqDchO2or9QqNWzTMorvJsi/7M3X5lFNhLhc9RGw2vLjU2Gz2aJlishn3C4IJcSu1ifEsxt/xGpsJiBlExIdL2DscYxNYjfswV8ru2kn/LJfFLM77+pcYtK2kqs6bXmPb5OAAqEaijR1fy/SJMkvCXCSd2xBI2cGKJX1bIYwqjvsg1+vxSeGI2qrQjvqnXm98JKOT9GRA0Jio0Z3ELpIN+DuA1vRA1/vzfWVcT7ciTpPSZssLu2Lu3htfkmsUB12tJB1XoFaYk6l2qBbz3RnyFwI9AwKUbzxhN+PDhzIn+yz25KmyC22YvM+egebJ4roz/uB5kkziGECuMEe5bWcF70oH1xBYsKEMGDB3zTAgk8OR0lmbq81xw1zyOuNQhplJJrJqiCfBPm5YbBZ7IWZwe2DmcG6/4RE14Ktsg9CoSe2BYiNL3BumirzR8xk3SE7YMCCcCg6QyjhZXZT0A4cikdddUmkbjo6rIKnjITRXofIggv+7xEZRuRmfeG/Acdm3H08FY6MfifDTglnXBcjWHfuDqRM9Kw7lQJG1vMiBCBRfMGFUYhKL4W46hhH5IQJrGchxbDujXLZML0LKhHbCCV09gPQb+Ds8RH8XoXfv8On0EKB+Z0fl8i6x7xPPGrx095o/wX6
*/