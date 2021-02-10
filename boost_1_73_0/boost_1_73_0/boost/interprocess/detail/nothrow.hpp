//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP
#define BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace std {   //no namespace versioning in clang+libc++

struct nothrow_t;

}  //namespace std {

namespace boost{ namespace interprocess {

template <int Dummy = 0>
struct nothrow
{
   static const std::nothrow_t &get()   {  return *pnothrow;  }
   static std::nothrow_t *pnothrow;
};

template <int Dummy>
std::nothrow_t *nothrow<Dummy>::pnothrow =
   reinterpret_cast<std::nothrow_t *>(0x1234);  //Avoid sanitizer warnings on references to null

}}  //namespace boost{ namespace interprocess {

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_NOTHROW_HPP

/* nothrow.hpp
0V/BNVDizoqzxdZCW7QcRXGEzgGdSb6Z4P9oKe6l0cwsgnXg0VeCOV6TGmpeVFKLaJhSLhYC9clWwjo45vAcZ0u5Al1Ew1t2iJzEF143oO1P03+M4c8PSA1N/2l6enJETz1YG7A/M2vNeNMoWURIloGCShACNZwnvKIkUkuOXgVgjRNsxa3k2hOc6FusByJ4x3vjxSW72zTAQIFHeNLSPoXAt6XQwtJWo+GPFb+0YE5iv65AYI68LAfPkOgOqKEEscNXbjSvZcFsq72sRTwhhQNMV6IRuhS6kDuBF40oWHKQ5NHKGfD/pjHWx/AqjF7IZWsJtAOZuE9AUUBLaBtu/QYiacuui6IPsDab3YzZ2qgFPJBlZrN3Zxm7XqBd2Fq6Cg0Q+SI98BAHAR6+QlwTLi1CKJRgR2V4iPyoj2imTnjkvBZKBcPcbYXacUli1Dv2hBsioeSBbkxO/EdiGL0lN77Cg0jKtL5pfRcWvaSVsOP/gK+v2Ox3hP5XeAnmi68hxLmFWPOC0L3cfhmG/9deThjYfudzP0EMFjFH0FNEZQC7c38W2Kcpex6N8PvwHXTQnKvOukzY48r2cmV7ufbP7XDF7686PydDJlcvjR75zvX2ZgKKdfI8pPV4DhwUo1T6KqEaSIc59xBrIYIr
*/