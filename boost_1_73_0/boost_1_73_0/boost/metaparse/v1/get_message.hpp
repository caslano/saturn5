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
q1x/rTRUVTqth0pOtwC09DApjlQE3sJF2bUHmtCrAzsShrn1GEu0JHOhrdoJbdbH2XEdvnuYSxM537W7i7xldmE667SEKJ3ItSTu5l2u836s/GW624RkPkQztUHVWRibtcDX1dX4K2pVrrHHUlL3TZZnp/ZDt7Dj3Iamm3s0f1dc2tTdujwBGBmLpbK0EYmlHHVCL7cUJoyO1mAZU3JqsMSqkF2QnRZGVVTbkFOnXc2TsAYnTbQVCg2905uGPEs=
*/