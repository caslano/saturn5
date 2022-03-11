#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SKIP_SEQ_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SKIP_SEQ_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct skip_seq
        {
        private:
          template <class ParsingResult, class NewResultValue>
          struct change_result :
            accept<
              NewResultValue,
              typename get_remaining<ParsingResult>::type,
              typename get_position<ParsingResult>::type
            >
          {};
        
          template <class Result, class P>
          struct apply_unchecked :
            boost::mpl::eval_if<
              typename is_error<
                typename P::template apply<
                  typename get_remaining<Result>::type,
                  typename get_position<Result>::type
                >
              >::type,
              typename P::template apply<
                typename get_remaining<Result>::type,
                typename get_position<Result>::type
              >,
              change_result<
                typename P::template apply<
                  typename get_remaining<Result>::type,
                  typename get_position<Result>::type
                >,
                typename get_result<Result>::type
              >
            >
          {};
          
        public:
          template <class Result, class P>
          struct apply :
            boost::mpl::eval_if<
              is_error<Result>,
              Result,
              apply_unchecked<Result, P>
            >
          {};
        };
      }
    }
  }
}

#endif


/* skip_seq.hpp
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
*/