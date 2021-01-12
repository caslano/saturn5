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
h9jb6Lt3UAob8mf4F3km/mH0ECIfL70svqxIReJ6U6TWUHpO4qyETxB+Gf2RvwNt9tM2+3nhWuhJs17irOLvhyQe5UhZjpKwf163XD2Muqg6KC5T9bl2Xttjvai0OubX6/Brom8UH4X9oYPUdZ/A63i/Evmw/1rPiy/O835+fEope3QpuzjX2+5WynaXshfleNtrJnjb07K97Qal7GXjve3CUvby273tIWrflffS9dfvzWvV
*/