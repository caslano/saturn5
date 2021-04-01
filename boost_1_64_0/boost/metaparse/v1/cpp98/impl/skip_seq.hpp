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
Ei+ObrPpVEpj4tMUdMj514THcsbRjHf230NJP8CWmwQ19Zy/DUDjRCA7MAZvaBz+UrtoCkNoQETsnqKkXF2xd8UnL+YjL6rXtwnHOJv4DemPr8bqVABBkgzgFSWG06vXNh+wBkPV03SHWhcdmBx00Hpe0HPVtkbthaGYI5kDUwuywcsWQvDLIpGQx5KhyuFXMkaajKSXjaqJEsPGm4FT2JVu4Uv8JsH6Q7g6H02p5UajQmwxGi0zawh7jbi510aeHMg2eYiJs23W27nfRPuY1e19um+1C2ttF97rejs8uZcuzLerOSndXhcoBKhLQNEst5SkFiSut1BWpxvzj2/SvCv9/pGKGT3GUKltsvRyTe7Zmvlo75bdVgpt8caVF+KgrGgJzGAhVQWp8KzjWWABdWOuM8WOtYK9JYQupLSda3nszovXqHMK03msrrnZPfLjA4a7LklbvWt5o/jcmQRH2wx4UYbFp7JGyG0lGiXIhedrmycirFiLlcmS50Db68LCNzmFKMj2GceKRfD2kgwBxLIUCSX/zRkzizX2smsawqiqfJg14LZhD9addQ==
*/