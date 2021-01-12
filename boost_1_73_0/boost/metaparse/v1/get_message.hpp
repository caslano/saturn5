#ifndef BOOST_METAPARSE_V1_GET_MESSAGE_HPP
#define BOOST_METAPARSE_V1_GET_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_message.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_message_impl;

      template <class T>
      struct get_message : get_message_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_message.hpp
ShruPvv3tcdCIy9U5pnyY2ftsT1MS3v8tHv3OvVIHzp08NBfbofgeW6muV/w/CpxqJgjPvb+nNlRO/TJGJCucS8dOiB6bkGJvXie29XK32fwoEHxe1zjz/krE7/HNXiOYHnDQVkT99fF2iavLZ7UDq5P9nffDd+vnNxjv5LBfYsvBW2dUjY/d0pQ955BwUeISkHZJuWeF90f1X1oep/hqf17Z6VmDs7Kzhw8KD0tNbco+c9G
*/