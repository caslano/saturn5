/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP
#define BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#//Try to avoid including <string>, as it's quite big
#if defined(_MSC_VER) && defined(BOOST_DINKUMWARE_STDLIB)
   #include <iosfwd>   //Dinkum libraries for MSVC define std::char_traits there
#elif defined(BOOST_GNU_STDLIB)
   #include <bits/char_traits.h>
#else
   #include <string>  //Fallback
#endif

#endif //BOOST_CONTAINER_DETAIL_MINIMAL_CHAR_TRAITS_HEADER_HPP

/* minimal_char_traits_header.hpp
5Ei1ct627vyz281r725q9p3B/6FTT7zB8fIr7AU/YnQ7fyCGy2eTzGjgem2FdLYxoA/bKBpysm79cq07xqFM0aqMt+RxKskg7SEcZxosNDlUqyp2FCaDQiJWpje1sHItK2m3cE6+A7piD+yZwRboDdRggt17ygEssGDuaKaPJVfN2g0qC1Sb3L5BjwXUbIS7cJx45ot4GY/jWeKFVcVO8Ih8EnP32+Rr+Gk+mzgH6OTs2vjzmtqlknaHdCiLHV7chX9I1JeuQO75xrtfy/TOIVeIBi0xw6F1thHPlyk9fBgNVx+xn+wYAxreaJezqc6NrkjrvM2upZvwgz1d4d+yJfidmvohLatQqLYeEP/1gkK6GYWfw+ksPJjOpssTL7wyi2dkzd2lSNZT64bvo54oPnxQLRX0gTTkQk7NN7o2nau0NXHEysrrpA/sQQ1SdeNuH6q4mCyPFxF8DmfHE2+Blq7RTp+TND4ip7kmLmb4Zfmumy7wODqK4i8R6Zhdk5OUth38KJlMIJwlMV0eB4vbk4MRcY0O49aRDT+4tDv1OAT8B1BLAwQKAAAACAAtZ0pS75dHL2AKAADpGAAANAAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxJTkZPX1RMU19T
*/