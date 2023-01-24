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
al7+XkB+B+tu9LF2ff6sq3L9mur9NkfDIa1WqzRjNCCkJE1Tbt8+AnGBIBA0GkYKCMKAyTRjOEw4nmRkahHXn+/pPGuxSJsjoyMKNeVW1TOXZ0E5d1ZALpP7irBGa0WWSaPqzLAEwHgCsgxUSOEOdDVW6NIyvXxupMrNl9OWEXFBOeCo8qp5H/zO2DIONevsAougzgDoJIFMWyKQZmxdMkerqSSx5eYjAbMsKw6fKcPR5z//+YXnByxcDViWKHXe8L0EThw6r35p/4vY3zrEz7PVtHt4eECr1Zz7SGCiAN94cw8hHiGKoNW0u8B0G6SpZjhKOTpOybIqt3UIViObug4Jn2vjla99U++3itTewqA5F6X/rEpUbJrS5UfarAlIM81spphMBaOJ5niimdp4gDA0cfRo5hfyV413FVhEGGo1YeEJPdUmnMnFS3c3fuBPXrejsx5hKHkQ6psv2hBFG774n3P/1NhIdDZjq980O0kpnX9+f4NQKWW+E1ANAXirpjs5LF0N6M+jew35nf/zrFBbRzWpJAUsYSHA0eERYRjN1SuEYDoZc3N3hhANwtBIAI1mQLcbshU32Oo32G1Omc2ssacWkSvcek4h1h6h8PNW5FRnncpZnlUNRLUN3w5Q98wr5yJmlLLnDBrmYSa2IkmkWRcw0UwmyqwLSCSNyNgBhOtODReuM/gJD4l8rKsjCo62qMpQLqtjIXh8
*/