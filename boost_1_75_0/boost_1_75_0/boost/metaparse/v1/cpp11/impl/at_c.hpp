#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N>
        struct at_c;

        template <char C, char... Cs, int N>
        struct at_c<string<C, Cs...>, N> : at_c<string<Cs...>, N - 1> {};

        template <char C, char... Cs>
        struct at_c<string<C, Cs...>, 0> : boost::mpl::char_<C> {};
      }
    }
  }
}

#endif


/* at_c.hpp
+bH3EhbSmeZpu/boPfWeaMntQMcqIPAZBR/aLG/ZrOh6895lCCHXaR8i47Td3ShNamXNo/aVZLWUR8e6u5u6ed3evcIqokdu+aSHrbQrweoVgP5aPkAJ/AboSm9wT825vX/u1BzUge7QLl5A1DpbVk7+G2YGwYUdT0OakQmD0Bvksh26q+Uaq6WbySlOz0XFK6zyjo5YrOX5V40hcK60Urgiu/eL2MSSYDRc46sP18tYhAizN8tq3dOCUpcaFysBylW9UaHgi4aXB9WJr9RYCdWLCeG0PmxRvlapy0qhpQCEDfEi4iJXsM5Km4yboFW8h9FQ4+9kF3wVh4aYd2gbU7eDrAHBKSQ4WvfdHYevMV+TujUtMjdwFWxc9kUn8YrcGX3KNhAcvtxlOI29DHLdcr64dZfhNLZuMTqNsecJ+ikCOb4hqAyJOyfRtgE8xfx46J9EYqygjDhthYMS2R1njihwXwRnvGq/oBxWbhestXCAQqoAe9ISu4EcdIPKwP8n3Wyfzd1sQR8oyk6KQA9lV1L+CBE1CCRgPFpwxuGf0/GPhH8y8U96pNMaHr4O9TKxIevs+OFcl0oWds7WmJLfLqrZY3yl+V5ffG+wTw2cExvsXYO62lg/7xonfvbyrkGTkK/vNmmV/V+wacvZY6spwJ5+7itQykM8EwGBIpm9kZ1xIG4GI39MFeU/2Mp4stJiBikk4EnaZyzO6p8y
*/