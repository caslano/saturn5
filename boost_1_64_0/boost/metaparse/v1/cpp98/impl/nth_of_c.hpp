#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/nth_of_c_impl.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>
#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/mpl/list.hpp>

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        #ifdef BOOST_METAPARSE_NTH_OF_CASE
        #  error BOOST_METAPARSE_NTH_OF_CASE already defined
        #endif
        #define BOOST_METAPARSE_NTH_OF_CASE(z, n, unused) \
          template < \
            int K BOOST_PP_COMMA_IF(n) \
            BOOST_PP_ENUM_PARAMS(n, class P) \
          > \
          struct BOOST_PP_CAT(nth_of_c, n) : \
            boost::mpl::if_< \
              boost::mpl::bool_<(0 <= K && K < n)>, \
              nth_of_c_impl< \
                K, \
                boost::mpl::list<BOOST_PP_ENUM_PARAMS(n, P)> \
              >, \
              fail<error::index_out_of_range<0, n - 1, K> > \
            >::type \
          {};
        
        BOOST_PP_REPEAT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          BOOST_METAPARSE_NTH_OF_CASE,
          ~
        )
        
        #undef BOOST_METAPARSE_NTH_OF_CASE
      }
    }
  }
}

#endif


/* nth_of_c.hpp
H2OegJix/6RElIvC2+dlXPs/gywgfqamT/uruvxjGirvqLSPN7qhyWi9Zhhb6rrgelVqx+YuuSAIX5QqY/205KbCn33DkMhc0n2EHV5zBb7/z8lTn5wRenNzTcKbgqd2HFktgFBL7RCKAZzji5cvb26HcXVN4xZ5gdgqvkML5mszZquRnalxXREq+/x/rfYHQySA9I5oGDzRe6oE5hOTu9/B7pbtZIH19h6pkhxj4dVRORXD72HIJpsV0rbdq2oDaXH9fu7JBRCOMyYp0A3BvvzD8GgH9eA6XrSiIAgZY8Z+j6dU/JurvnVZkGdaD7bKcnOoICW28uiYhiwAIJNGgwW3L+9auXxsT9M6DB3XqdReoEPWAqAVIcZCTHDRmV90MEQnuMoUFnlCYJhx8Wo+nZnJ2zRfPoiipQDH4QH0u+Z0SFdghHu2/vzixfgscyF5XhFbpElgDqszezlyCCRxYM8CpPcFftQN5fsuas2TvWjNI0rBja3qi58fmEReozX+xbevBHQG6A+UmOq55WKefpEayKVQVU6xWhjvWDH7EISHkJTaciWo1AVxbQ==
*/