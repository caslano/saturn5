//  (C) Copyright John Maddock 2010.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TUPLE_HPP_INCLUDED
#  define BOOST_MATH_TUPLE_HPP_INCLUDED
#  include <boost/config.hpp>
#  include <boost/detail/workaround.hpp>
#  include <boost/math/tools/cxx03_warn.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TUPLE) && !BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40500)

#include <tuple>

namespace boost{ namespace math{

using ::std::tuple;

// [6.1.3.2] Tuple creation functions
using ::std::ignore;
using ::std::make_tuple;
using ::std::tie;
using ::std::get;

// [6.1.3.3] Tuple helper classes
using ::std::tuple_size;
using ::std::tuple_element;

}}

#elif (defined(__BORLANDC__) && (__BORLANDC__ <= 0x600)) || defined(__IBMCPP__)

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost{ namespace math{

using ::boost::tuple;

// [6.1.3.2] Tuple creation functions
using ::boost::tuples::ignore;
using ::boost::make_tuple;
using ::boost::tie;

// [6.1.3.3] Tuple helper classes
template <class T> 
struct tuple_size 
   : public ::boost::integral_constant
   < ::std::size_t, ::boost::tuples::length<T>::value>
{};

template < int I, class T>
struct tuple_element
{
   typedef typename boost::tuples::element<I,T>::type type;
};

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0582)
// [6.1.3.4] Element access
using ::boost::get;
#endif

} } // namespaces

#else

#include <boost/fusion/include/tuple.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace boost{ namespace math{

using ::boost::fusion::tuple;

// [6.1.3.2] Tuple creation functions
using ::boost::fusion::ignore;
using ::boost::fusion::make_tuple;
using ::boost::fusion::tie;
using ::boost::fusion::get;

// [6.1.3.3] Tuple helper classes
using ::boost::fusion::tuple_size;
using ::boost::fusion::tuple_element;

}}

#endif

#endif



/* tuple.hpp
f3cgP0lVlUWZwgdP2rh0H49K0PkY3EGoy3EQ5LBWIm1lrZjf+FNLcDW55DfGFoPtuJGUw2HOKNpK18U8bjK97Q7QLfdi147ZVwZ2k7ZlrlrzvmkBb98GWqPmkSP8T/gee0jKiFkWJ0I0GZSBYv2kxx3fecIXsSJusiquSsv4mvVb9IH4EI6RKd+dPh/MALVK8iwVhm3ka2KfKgV6uhDoqU541OZFw+zQMtmZbRHWVm5KuzMNnzdJmWiiJK0ywbCBOtMzqAdUZevvTrC9+A9/JnUQLG3TONIJBzbXteyFeVsJyDI9cDMuqNjl756nd1myqtqohL7WnmFLm6hwmuh22LXjAOGvWCvKVOW57PP3Hwpqfre+zdO3nk1SZFVaMrscHoWHXP6d9VJX/+F88MY509GEamEZbetftwR/mek8XB9vp3KzTPEqjlPLbp+2rbuhvtjJ/TCRK5lMcilSXmJ+3tWlgRmkNlFv0P8XCb95Gh0nWRLk5t3srhG1F4y9qsL3X5dgX3pmSr/v0pMyeQBm6L8B+mVKtw/AcH93N/z5Pr7/0kD3AKzu4hy8nJ5BwuQa1Q2/6rxyeG6MZ3A/CPfe6DuD8ejvYXHhguxhfrXTYsg+1hSEsQ7v2ceg1xDiPnddD2fOwbTy/TPbu+5lcXTxdfRz90U6WL/9mkD+djelg1MbyXO0cn2fbveFeK74AIIx2vPLuP2Bfbpp8MA7s3vQGIwXJ7PdO4a+YW8W5+aJ7u4egzVamde57RF354MR199EYP1ve0gfZ1WAeXcf6jADc/9lpVoY+iI+DHDhHY3Z0+P3wS8fDpiruKM5/wiKo3c0+E20dYPFbeO/9GtCp3c4tz0SaaH/0plHeTQr9IGW1j5a0/T6hmvUy/g9yBqVxFWc8koy1zdRmD/8Hi63/0toHiDVZm2tFKO+rtRv5+eURxQirRrRstF+WPtTaCcVynPZ52lY0UINCxlbHvBsQRbHc7fPU0GVcsFbxZl309OLd7PrpTTeTZ0mDc/1aq0vq+n32l4fGyvWtjnP8qZlI0uzHhbhlSnq7rDPXzGVtbJoooJ5JtjVb9DxMJ+nYbXkcZI2EXOrgFaf4UKelsqp6zzjiucdj3Y+cXLcWkvalrCkjfRbBGmZSKtIjCGfr2acx6LJ84j5PtFh/qTzPk8JNpQlUVtLNjw1sDqke7E7grplBS9UmTVsfWMUKnmms1tat8/RurWJdqoAe/dP3bq6dTwXKU/aqiziVeW2YMbJxPJ0NnSXz3NcFpWImtpx0Dr96qV0/NRpnlWlYtSXlvL8mfJkQiZlmiknwTpUEJ7JlxG7qSqZpEJiO2Id0TAYP3spT8LzKknripEb/IDngM9TsyaNuRRt6pJhvQ7tE3Nu+TxQvHZcSIoYeVzoGeThlCePeRtncYN1c2MbeWZ9nlbHv2prIQqG2+bZ3r7/zMvod0YuRV1Ujc9kbxhpPI5zAR8orlC1aln4MMXydWPhdp+vZJVQvI7LThXOZdK16f20j7IkFrEqVMdgv2iCcUB5VFLHMpV1x2N3p1QPF0l7IlB4Lsu6yVnwaMZwefPpz32+Y3mexVLkiuldhrLVmu3a/ivadp16LMoSg/VNeqbD/4HiY8HztOUN05+t1lWGtGH3y4PYODKRSSKUna97E7XLJUf4IpaIStSwRrJgfQ9tdMrnq2AKjasiNqZjXbcU+te6XHI+T8mKiEcwH6as21JFQxrLbtbHT9dF0cSqjNyw7vkDvpK0hbNSRLCG4PREtUB9f7deTm2tjqpaxgUj72DsN4z73g501zRtk9ZlZiZ3K1K7D4ZnYHf6fC3oLuFl1DB6CRjkevycz3OsiKIykbJgo9d61nY=
*/