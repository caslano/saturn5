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
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
*/