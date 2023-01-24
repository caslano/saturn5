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
o2IgAScNAiMYU2EZXYhMxS37nrCDzSOmN+APEpI3qpCmN2A5oOSNE0SfGawA4/EVpDS94YSoMoNlzJW3wkayuwT5s7uUAtPG/eets7t0EJyp+yb9Rd0+P7u89SZStwNy0o/qmizajQBDKalsiYFFHz5tFd48zpr7vasZEVPnpZlPLUgSIAKoXlfxJYq+8//OZL7W9u70obtKa4oQwPIwrm3IIfQlJWF7k+CMSf5DuqilX6iiOSMbV1y1l4jZvm9tSbLGvv5nlWTLqixoKzitUnbL/xKvxCvIdAHEFbf2EK7ufxo+q6c4DXZLTNj9SpUqXT7SRjrJM8VrSjMkNq753YGmOjyJZqAgs3cLHLRuzYlH5fYIu+/q9MJ5beW91XlCbpslkPxZXBinsnNciTL/u7rNSvQcxSnoilrBN+/VSlkqXwhRxjyVreQQSsC2KqrKZ/O6AlkV9pHsAQqaFVdlP+L8MkHzLrIZB+nszA+MlAYvPz8Yxl9fdG8HbRNufzlB9RNB4Fqe6ti+EPcrSJirmx1cCA+qgajCPSFpDQOdp4I7nUJwlWR/ru7EoNggKoT1qQVHf8sTSvMTPeTJyA8/x3MOXOwkFJglLp0Ym5cp/hkQlQH4aMk18kDi8cgnpggwXX5A74jLCIzSCYMoFMHxL+jf/mQqvowKec56xlj7bO/UeMPJgP5zonC2MHP1+JZMRRDx9nfdCR5EzuWZ
*/