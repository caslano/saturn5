#ifndef BOOST_CONTAINER_DETAIL_VALUE_FUNCTORS_HPP
#define BOOST_CONTAINER_DETAIL_VALUE_FUNCTORS_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//Functors for member algorithm defaults
template<class ValueType>
struct value_less
{
   bool operator()(const ValueType &a, const ValueType &b) const
      {  return a < b;  }
};

template<class ValueType>
struct value_equal
{
   bool operator()(const ValueType &a, const ValueType &b) const
      {  return a == b;  }
};

#endif   //BOOST_CONTAINER_DETAIL_VALUE_FUNCTORS_HPP

/* value_functors.hpp
TgeOY+kktAeL2RZ2Ebv4RcqP78wufrmmsv0hWGdg2Zl55pmZZ4PNBPZ/2OUF5A6evXL7y/HC+53Rqld/88L8v0GefwP3h4YbvL8g1AwerL7le/Aiq28wtVb5GOuYnvP8BeE2BJL+zch4k9MjrjjL0X6uutteXNYGpvM9OHz79ld4Ba8PDo98+MCk4A2khsst7y99OC7typ81u7kJNH/nAzfAmmDHYVYLDVpV5pr1HPC5EQWXmpfANJRcF73Y4ouQYGoOlWg4zJPVRRR/8uG6FkU9+rlVA+haDU0JNbvi0POCiyvnpmO9AVWhB/RfCm3Q52CEkgGG52B43+rRDYFgjVbArpho2BbDMQO1MZ3+bTYrhr7BTGalKvSsuKMiqE37n6wuEE3LbkF1BoyCQXMfaL8PrSpFRXekCBe7YdsIXfsPsDCgLGeqB82bZnSHpoJrlwKHdGTLp53QIXph6KaV1BTtulbtzkakdXRUDb3EcEgL7isVEu/DIEve2/2WiLsoI8uW8mdK9oC9BCURFUzCFKJ0AlumhfbhPMpOkrMMzsP1OoyzC0g+QhhfjP4+R/EH7A2BUXvgN13PNaLoQbRdI3i5E/yHTroXZCcwP1svT5NVlp+GX/OTJM3yeRLHi3kWJXEKb2ByeAR/DZKa
*/