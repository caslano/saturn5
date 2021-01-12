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
Raw7jvuaHceRKYyg9C+Tv3O4Ye3PkXVN3W6y1b+HyDGMTK/uG2epf2/F352OSSMtk615XG/tl2+1y32U53rI/XE1tMuiUJbFPMKHSCeWM+1eax2UChtgXZuL/9sm9aBvP+3tBuNK3WmPobh/go4ySj4mEiuYV3hv2/sDkk3pQ1KjbLsOHiX8rXXsb2n2rXS/T9p66cJMlC6PqGtVjuls+YlJTTR1TYhLtubDrxjb+KI+2nUs
*/