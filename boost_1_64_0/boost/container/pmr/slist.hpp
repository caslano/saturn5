//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SLIST_HPP
#define BOOST_CONTAINER_PMR_SLIST_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/slist.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using slist = boost::container::slist<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a slist
//! that uses a polymorphic allocator
template<class T>
struct slist_of
{
   typedef boost::container::slist
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* slist.hpp
0WFRZzc18bd6x3z5VHo8If7mDizBsy2XjlHg/S7affMlUu/yq7MLDNuEYwZisB85TtZ3/XK/WkzExP6dni+wERP7d7p/cIDh/kHsp/2WLZjJ2wdx3ptaxQlxTOQxcQ6Xmv0TcazoaTNHsnwwnGfiHBm1AmKLgOj+1k3sZxiHx95gJlz/IB+1KjCjMJOzXpzPolanZXBpRIM+PCRZO2PdjJlO++qUzQamNwrLApNq+UK7zWYN66WIcfCYE/p3D4wLNSNjJsYsjNkYszPmYCyFMSdjaYylM5bBWBZjOYy5GMtnzI0Gy3aOZF0krkiybsbgv6YZGTMxZmHMpmmwnUCD/mXpA4jplSIStwXWd2oljJUxVsFYFWM1jNUxVs9YI2PNjLUy1s7YKca6GOtmDP5rmpExE2MWxmyM2RlzMJbCmJOxNMbSGctgLIuxHMZcjOUz5masiLESxsoYq2CsirEaxuoYq2eskbFmxloZa2fsFGNdjHUzpgRom5ExE2MWxmyM2RlzMJbCmFPT4Dw7GO47VgFR6yZx99L9ivhi0DYjYyYwzDdXqiWHxN0n1eJiLJ8xN2NFjJUwVsZYBWNVjNUwVqdpOqWejGe+NNZ2+IJxm6U2HYylMOZkLI2xdMYyGMtiLIcxF2P5jLkZK2KshLEyxioYq2KshrE6xuoZa2SsmbFWxtqpSXP3FJo4Fysd02b19sWVSvM6hzEXY/lgmG+tXu9XSzOJ2y4de7eSuA1Sm45AX9w2aXuWwphT0+A5Fxjmu0uKqyBxW+X5wliNpsHzd5LPLS0HEwDGlUhmYczGmJ0xB2MpjDkZS2MsnbEMxrIYy2HMxVg+Y27GihgrYaxM0+AYEwDnxHrpOaUpyBf3IMwlahbGbIzZGXMwlsKYk7E0xtIZy2Asi7EcxlyM5TPmZqyIsRLGyhirYKyKsRownEtrpLlkD/bFPSAf7zKWwpiTsTTG0hnLYCyLsRzGXIzlM+ZmrIixEtnotgAMl9FqaTuhhPji7pf2K0bZ6HYCDNsskM/zkbhiOifEb7pI3Dpp39gIZhYmXl8ntdlGbI7Uhy5ieI4MzaD6TH5OYiG2StpvJhKTj72dxFZL29bZxNbIxzbE1krLr4AYjieOWQmxdVJcJTHclmMf6ohtkKyJmFsa63ZieIyCdkbVXkbGUO3ztCbGLIzZGLMz5mAshTEnY2mMpTOWwVgWYzmMuRjLZ8zNWBGY1rn07lDmfHmYthkZMzFmYczGmJ2afPwJpnUuvSSMOV/HWAVjVYzVMFbHWD1jjYw1M9bKWDtjpxjrYqybMSVc24yMmRizMGZjzM6Yg7EUxpyMpTGWzlgGY1mM5TDmYiyfMTdjRYyVMFbGWAVjVYzVMFbHWD1jjYw1M9bKWDtjpxjrYqybMcWkbUbGTIxZGLMxZmfMwVgKY07G0jQNziWYtM+lKxHM+XLGTIxZwLTOpbsimPPljLkZK2KshLEyxioYq2KshrE6xuo1DZ5boJ3lXLojEuPOcr6cMSdjaYylM5bBWBZjOYy5GMtnzM1YEWMljJUxVsFYFWM1jNUxVs9YI2PNjLUy1s7YKU2D17GAaZ1Lz4lizpczls+YG+0s59JbwbTOpbeTOPlceoqZOV/OWJqmwXMuNDyXTueLmTlfzlgdNfn3cWhnOZduiWbOlzNmZ8zBWApjTsbSGEtnLIOxLMZyGHMxls+Ym7EixkoYK2OsQtPgGBMNz6UTs/TRPm9qY8zOmIOxFMacjKUxls5YBmNZjOUw5mIsnzE3Y0WMlTBWxlgFY1WM1TBWh4bn0ok5+mqf+01hzMlYGmPpjGUwlsVYDmMuxvIZczNWxFgJY2Wy0W0BGp5LJ2a0aJ8=
*/