#ifndef BOOST_METAPARSE_V1_FAIL_TAG_HPP
#define BOOST_METAPARSE_V1_FAIL_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <boost/metaparse/v1/fwd/get_message.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>

#include <iostream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct fail_tag { typedef fail_tag type; };

      template <>
      struct get_message_impl<fail_tag>
      {
        template <class A>
        struct apply { typedef typename A::message type; };
      };

      template <>
      struct get_position_impl<fail_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };
    }
  }
}

#endif



/* fail_tag.hpp
OOzPGwgOcShMcLCrpQSHeLqa5O4mOOh5G8FB3p8JDva8j+CwDg7qLM5h3T+a4CCvnOAwjgqCQ7y6gODQvwTBIU5eR3CIu78hOOy3NhIc7OoVgtOlfEhw0F/fJcU52NUYgoO9nE1waPd8goP+FhEc9guXEBz0t5LgdCm3ExzkbSU42POrBOeTspvgEIc+JzjYad+lxTm8Dz2W4DBvJxIc9lH/QnAzpMzrxtV34/Dc5w5CHvz8IYKDXnYQHNr9E8E=
*/