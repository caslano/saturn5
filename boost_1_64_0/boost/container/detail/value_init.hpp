//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP
#define BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class T>
struct value_init
{
   value_init()
      : m_t()
   {}

   operator T &() { return m_t; }

   T &get() { return m_t; }

   T m_t;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_VALUE_INIT_HPP

/* value_init.hpp
1CdqdfskGChU6xsoWHET9ao0Zqel6XhqY2TJZX63qOZyLqMymh2W49vTVLzQunehXxe6LlaLADK/81wn4LJKyUXN/nGU3WnjonylJxCY3BYN7FH+4/T6mFVDlC6Y/pfQ3/zfAUdj4JmIID8PWDd993yfFhV61iR58/DAvp99FvMysOwHAX5dxXOu/iiAoRgW9/JKzoVPLj9Xdi5g6xdf4HVtUUb7MlIJVxxahUYIIZW0H6g81bEb9odfak3HJqqwO1JOp+7Q7TBUoXDXIT/NxD2d2RuwEaFnvXd45cQyyIHm6VIIw36iuqpVYIHcQVpizjDcUZoJwGGAz9yAvWI6uoDFSfXTwnxklrf7drK4KgkDGgyvIqy8+Jby5AytOh9rDOut/nzhxeX1qc1gAWHDQEbHpRHNTVlDYpk1OahUnn69kao97CZ+IgyTekeSmJAG9SFTzMpZikw19Sa/uPL8vuIcbg3a95moJq2ULmAlqnkwGNvnDFvRNm9VhYNRtGTsZjpSe/NloH7OO9qan5WxM1izCUfDAYWBcPWR2HmIE8FJpA7hEgS2T+YgFA==
*/