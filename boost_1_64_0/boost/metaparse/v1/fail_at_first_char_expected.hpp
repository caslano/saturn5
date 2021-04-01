#ifndef BOOST_METAPARSE_V1_FAIL_AT_FIRST_CHAR_EXPECTED_HPP
#define BOOST_METAPARSE_V1_FAIL_AT_FIRST_CHAR_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/void_.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/metaparse/v1/error/expected_to_fail.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct fail_at_first_char_expected
      {
      private:
        template <class S, class Pos>
        struct apply_err :
          boost::mpl::eval_if<
            typename boost::mpl::equal_to<
              Pos,
              typename get_position<typename P::template apply<S, Pos> >::type
            >::type,
            accept<impl::void_, S, Pos>,
            typename P::template apply<S, Pos>
          >
        {};
      public:
        typedef fail_at_first_char_expected type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            apply_err<S, Pos>,
            reject<error::expected_to_fail, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* fail_at_first_char_expected.hpp
lxl/ker/OL1WJtOZD0SMZsIausIvBWS4AlFbuXItpn8sAW7RXOJoSflnaz7eL/EP1HmX8Q86PR8xwM/5Tz9WxZrHiZUM0tIfJoA25dBcL3E6QY+xa49Ci0GX279btxP22DNDszMezqFhacbUpcWbByscUu5oy31sK9lJVvBWR6FBffri4Kids6RMIrcz82afyayN0wzgkOUxZT2hnR+QUdj0r4oQF5n2aHtwDOyEVstppVn5ZuyT8y9PO3vX/jtwcUeCU1f16Sh6SoGFyKVeU7gb6VInLvLD6alB4hYjZK77MJeMzGWvRbr9pXK/yiSpAIVdS1X303HOereZi9nl8FnZhORPxqmebcn496pASnXsTAzF5fWLCW3+N1bq0X2FmvXTe3AGqrBn2lsYs29bOdzhyBFvOSKswZBaon5K5AHOsbJxAHUBq/OwmR6pTWo0ki+LzSftmi5nRpJqEUARlz80J8QkwRY+FCU0V1eAUhwXT643cFzLgv5iTQexnOKxo+JeoWWkIVf5IajfM0xJvG3yhJZTlv7zorhFOR18/VrQtp0yPRcbwRW8xw==
*/