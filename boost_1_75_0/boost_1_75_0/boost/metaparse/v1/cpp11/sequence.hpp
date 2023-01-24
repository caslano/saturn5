#ifndef BOOST_METAPARSE_V1_CPP11_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP11_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/push_front_result.hpp>

#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct sequence;

      template <>
      struct sequence<> : return_<boost::mpl::vector<>> {};

      template <class P, class... Ps>
      struct sequence<P, Ps...>
      {
      private:
        template <class Res>
        struct apply_unchecked :
          transform<
            sequence<Ps...>,
            impl::push_front_result<Res>
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef sequence type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos>>::type,
            typename P::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos>>
          >
        {};
      };
    }
  }
}

#endif

/* sequence.hpp
RoG4vO9XmsqjICtnLN1rg1X6/mFjSSfd+BtLun82LunIG7st6WFkD9xNc/uXR1/sBSPkOKnP4eo6SrelCmwi90MVJpfKuroCzqOk+jj7TB5tBcEI4u4J4VI+djPZwt8sSbGwQapUG88n4iI8J0tBOAvmgvi+XVbv7jqmL8IFGeIFUuNAPjijnHY6E7LP8WRUvUhl1pdHSTEmiNidgoidGRRjDbDaYAfLGS5z1MoWOpy12D2sHCQowzpN/8JCTsaVBG20Sd6SwzbJ6xL0GQuyMy/HBOTFv1AC8pXUon3kfUYC8hWUgzUFNW6VuBcqmSS4Tg7RsQiymNC5SfXDUoRiF27/4Ssb0x7KfdbbuIMjrTCc0lxtqBKBhzgAyier/pqgWseVnADs2j9+5WqNu0SARgXqkb+wUaqnrCA8Ter0h0WtH8wV35qg7eRe2K7+qVRfLTazTJtZphT1GXd8abNorwozFWZVr5nY/CX5jkYsFuH7RqSGH5fx8Yh4PGhlsu5B2FQAPvS5FEnsx1T10SZmfg61OQ/bxJANNEYpruvhp16cxe6aaKhTECrKlqh9Ktxpsvvgr5XaAMrten8vWws82uX/6dTJQU93jSizGp3D2hsePPQOmUw/hOGbjjzF4VvNPF5l2jCMt+ZW9t6ArSS46cjdLJ+VJigrzWNIJZQABNv3KSMY4gwgmDOg3JXFlYi49btvMBx6Wr5BFcMW
*/