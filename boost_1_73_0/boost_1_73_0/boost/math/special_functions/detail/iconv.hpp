//  Copyright (c) 2009 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ICONV_HPP
#define BOOST_MATH_ICONV_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/round.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace math { namespace detail{

template <class T, class Policy>
inline int iconv_imp(T v, Policy const&, boost::true_type const&)
{
   return static_cast<int>(v);
}

template <class T, class Policy>
inline int iconv_imp(T v, Policy const& pol, boost::false_type const&)
{
   BOOST_MATH_STD_USING
   return iround(v, pol);
}

template <class T, class Policy>
inline int iconv(T v, Policy const& pol)
{
   typedef typename boost::is_convertible<T, int>::type tag_type;
   return iconv_imp(v, pol, tag_type());
}


}}} // namespaces

#endif // BOOST_MATH_ICONV_HPP


/* iconv.hpp
AAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTAwN1VUBQABtkgkYF2SYWvCMBCGv+dXHIofXVSYspIVxphMGOhct32O7XUNpklJTp379UvaqUMITe+497n3jghCT7n0mDKhTGnDtcXjwbrCpyybZ6v2A5/rVzZ/WLy8r5+Y4JcKwTsR67M+PGqFhoZeFchE3gahwqPbo0sZldSE+lMIwsgaux7g0RRwUFSBMnupVQENulp5r6yBcDpR0PBOBCK3dS1NkbJhBtp+8TjGeDSa3dA3QWyVcD54Xr5li1UyiD1Wy3XG+R9+WCodPPIzRcQERPh97xrXCyYr5aGQJINJrcFYgg1G1xQgURo3cZq43cUHOlUeofG4Kyw0zpLNrQZZEjqgCiF2gEr6AEIDPV9Z6jGxb2WBhs5Zl9sikKd3Af4vFidaymwTUwlMWN3eNickRl79xOSMbfS2+78dTxipGu2OEpiyaDkOm8D1Ri5swc9m+OWR/AJQSwMECgAAAAgALWdKUmvsvsk3BQAAqBwAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDA4VVQFAAG2SCRg7Vlbb9pIFH4fif8wbZWXbo0hSdWWdZDGQIAWCBcn3exqVRl7sB3sGXdmHEJ/
*/