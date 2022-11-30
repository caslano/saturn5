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
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
*/