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
6HZD5LRWnW744O1+uXqavwTstiyxpfQlv3QrlfIzBU1MNBiDs28akkee73/+IXi9J+HjL8KNrWiCR/l939j18U9n+fm/4y9QSwMECgAAAAgALWdKUkRNJPp3AgAAGQUAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzQ3VVQFAAG2SCRg5VRRb9owEH63xH84UfFSkRoo29Q0RKqgaqt1BUHaPU4hOYjVYEe2Q5d/v7MDBWn7B3tJfOe777777pLIorFZajBmkZAbRa93bD6Uzk3MHpNk4R/wcJ+wiJ9uIt4GswsWaazKhlx5alOQKiswe590GzTdFoEPr4YwGgxg/r3DZqnFEJIa+zC4gRe1p5vhAIbjcHwTUszDj6TDVqj3qENw3ALjDb5J37HDpkpalDZ4Rrm1RQhfvUtiZoWSIWSlMmdRSVOhQ/lteWF35eliJkyljGiTNqJEme5w4h7D6/G3W8iKVBu0k00tZXMLqnKRE2N1KreE32HD0fX4C6ngenZqHDQgOS5gWgpXw4gcWZR5Iya3LYQBjWQbUJJMhBzX9RY2mNpaI1gFaVmqD6iNO1N9yIWm1pRuvIMO6PIILJiDqm1VWxCyTwlCbj3i9HX5/Cu5XyWzpyXsUy3SdUksDiVo
*/