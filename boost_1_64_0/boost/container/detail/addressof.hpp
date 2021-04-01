//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP
#define BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace container {
namespace dtl {

template <typename T>
BOOST_CONTAINER_FORCEINLINE T* addressof(T& obj)
{
   return static_cast<T*>(
      static_cast<void*>(
         const_cast<char*>(
            &reinterpret_cast<const volatile char&>(obj)
   )));
}

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP

/* addressof.hpp
MokgDvurZH3b52PJ9I82kK0wvNdkQld5ZFfQCKUnEuuYWzajW/0IYu6zIweQ/ny3ayDr2K0tHO/r4EhJ1ZWsNjb0j/xl7XwDgNpY0NXJ9oWsu31VrvAOwY9+obRqvrp47HpZQV4DLkbKrNH4HRUwIWnYA53b72/F2S29sqGU5gvYLbN5HT2JtpGzLPB08Z0NcQXXt/MdJsiE6ZHx5Vwb3BQ6EEjRfgVumGu1R1G9pVn0TkoCQvhUA049Gg4qh5eHtwfVJD+UpSJ4L5H0UX6tBN0BPEPQ4dMzILuYBs7DamcOLBoXw/EHeV1+4tot3EtcVO/pVN/byZxOmf+Zses76KaSaK60Bu8ArCAt1n+29sBZWwRUkz6iYmcrsyjgQ7TI0yXe/1mDzcE1HtmgVVlLeUODXUW7DqJYfrV1JsmGAylL+JlDIYzql3lUV4OCl1I6Il0xX0kLY+lI2WAqZ0c0VBRspRUxNolv4/ax7jd9cFFxQJgrdTZM7xl3D8mBhDtilQf5KGh9NZ2SbZZd4cUow8GxTHrq4Z7Th0+OFdlLgxGN8BOSQWaZU4Wp1Q==
*/