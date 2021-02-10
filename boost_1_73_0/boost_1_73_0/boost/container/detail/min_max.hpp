//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP
#define BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace container {
namespace dtl {

template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }

template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_MIN_MAX_HPP

/* min_max.hpp
U0xfUFRSLjNVVAUAAbZIJGCtWG2PGkcS/t6/oo7TxbDCkMS5nGM7yWHM2sgsIIaNY2kl1Mz0wMTDDJruWZY7+7/fU909vMe2TtnVLtDTXS9PVz1VReuuRld/2Y9osTj64s/M/s3wg9fq0LjI/1ChuXxgNvtI7hcH7/D6FaratD/1cdagrzr1ker21MzresHvZ7OvUHfHRvK/Nh++m/FbrLiT/nw3X2+LZLE0VO826LuffnpKj+n7b7//tkmvZJaolAKjsrkqFk16EdmVfy/lw0NLq1+apAzJtHUkcLpMNOk8NhtZKML7NAlVplVEUlOkdFgkc3xIMjJLRXGSKuqOxu/7w9dN2iyTcOnlbPOS9DIv04iW8l5RoUKV3Dsxa1kYymNIgPwo0QYyS5PkWQvqFRlVrLQXw0bIVOck72WSyjnUSUNLY9b6WbsdlkUKT9pRHup2WEHRWprViVfvYc1KbilfGzI5lVo1ifc3aZVHScyvgAiL63KeJnrZ3JsFhVnUzgvSKk29OBxNlHYuKAo8Wk3eSWtYnxh+0XmmWdtmma+ONgJWLyguiwzqAAv2RTmAb1KZRaqw+y0QlRaPsoX8C1e2tz2iPINVVOsE1A9qNJc60U1615++Gd1O6V1nMukMp+9pdE2d4Xsv721/
*/