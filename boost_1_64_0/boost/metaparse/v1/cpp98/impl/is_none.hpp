#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_IS_NONE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_IS_NONE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_char_except_size.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Stub = int>
        struct is_none0
        {
          template <class C>
          struct apply : boost::mpl::true_ {};
        };

        #ifdef BOOST_METAPARSE_DEFINE_IS_NONE
        #  error BOOST_METAPARSE_DEFINE_IS_NONE already defined
        #endif
        #define BOOST_METAPARSE_DEFINE_IS_NONE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, class T)> \
          struct BOOST_PP_CAT(is_none, n) \
          { \
            template <class C> \
            struct apply : \
              boost::mpl::eval_if< \
                boost::mpl::bool_< \
                  C::type::value \
                  == BOOST_PP_CAT(T, BOOST_PP_DEC(n))::type::value \
                >, \
                boost::mpl::false_, \
                typename BOOST_PP_CAT(is_none, BOOST_PP_DEC(n))< \
                  BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(n), T) \
                >::template apply<C> \
              > \
            {}; \
          };

        BOOST_PP_REPEAT_FROM_TO(
          1,
          BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
          BOOST_METAPARSE_DEFINE_IS_NONE,
          ~
        )

        #undef BOOST_METAPARSE_DEFINE_IS_NONE
      }
    }
  }
}

#endif


/* is_none.hpp
X4rCXTduhsic/NkV7G+XtbY5cp1n3AJF++qBQsZvhpXTXyK7VCRCFuBZ6NT2wB2e6wVWBPolqOypeJ3vLlVhn92kXGZzQWbfwnNuQWl4Ho4FUM27AP/P0uItibiauUbk/m9T8DseXJ2pwdA5yUL1GhA5rJVYICjqexX6mV2KM+uQ6t7lwLjjUpTa4gaSZSvzXH69DRGvyA3gVr7gtw8mWAIlK8ug9kCxPXa/9NUMwo0Q2JQ3hjZqfE1lWBw7PaTdQ80YlgH8kWVRYvi3qhzHDtc0hQufn2W2qAE0ZmwETzbujvk9GDWhb850On1/9Jb2gN+LIvNVUiERRrq96OWfthDSkhGpiGba5e5yoCBeWVXUx7bfweehXoqqqKc3lZr9vau3IS4C3UCLd0XPtcCrd3Ymt8KPMmkx4U2ZSKVyhDmPKZfj1Yo8gxIb2PYkIZZ8B9QNkl1+oDGLj44/siX6lWYmL5n0WOayuqEp4r0x1Ziuvjd1CVWgFIGJgn2w9OFaa490MzRDCwjmXWdGyhZ76LSMjAWaV0XcvglM8zWbBXrziXvDrt7NjpFOvQ==
*/