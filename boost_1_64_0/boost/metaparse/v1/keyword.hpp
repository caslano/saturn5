#ifndef BOOST_METAPARSE_V1_KEYWORD_HPP
#define BOOST_METAPARSE_V1_KEYWORD_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/void_.hpp>
#include <boost/metaparse/v1/lit.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      // Does not consume/check anything after the keyword
      template <class Kw, class ResultType = impl::void_>
      struct keyword
      {
      private:
        struct nonempty
        {
        private:
          typedef lit<typename boost::mpl::front<Kw>::type> next_char_parser;

          typedef
            keyword<typename boost::mpl::pop_front<Kw>::type, ResultType>
            rest_parser;
          
          template <class S, class Pos>
          struct apply_unchecked :
            rest_parser::template apply<
              typename get_remaining<
                typename next_char_parser::template apply<S, Pos>
              >::type,
              typename get_position<
                typename next_char_parser::template apply<S, Pos>
              >::type
            >
          {};
        public:
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<
                typename next_char_parser::template apply<S, Pos>
              >::type,
              typename next_char_parser::template apply<S, Pos>,
              apply_unchecked<S, Pos>
            >
          {};
        };
      public:
        typedef keyword type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            boost::mpl::empty<Kw>,
            return_<ResultType>,
            nonempty
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* keyword.hpp
Bfd2AMrhs/zhlxwJYCmFRwCveL3FJRMTwGJxCXcfW/2HAQiWTVOyVc0sl9ANDFiDF5ouSeD01mpGZk4OGncRiBT7DhneW5t/YSDqOsZ6MEvvSAABFSfMP+RQEQRLvd9GGMEefW+IfQGMlYz/8D4Eh9C2pzT9EoCVOUH0sqYWUuVLjYCx1GyClukU3hMGcOSkvyaetgfLYpRpiTBLtbUE8nqr6ADfHr3dj7EM0nFR02zKS4A1yuJzcrIHLdI49haidduMhFE1gso7T+/2k0+JPlaRNN5CytrR4Mg3Fzj7MJUD00pRRYqhKo9bWsoL1u9D1Pm8ESnnfIIY5/V/6UEysYLxKhyFveGzY/2Z8qpLftVKgJGJMaoJVrqo8LnVPHGH5LG0LWGzJ9WUFvkoSM7LzwqZAz0LbNT28MF/HfxXIZOBnpxOVyjINkOrSqS3YhJtL4FlF29z6Ksy42MIh13vqFRIElpbd7sjirmt/ITbfUOK47Z9ie2ZYpaaKn1cgpBQJu1x9v/4juF4c25jJmEfY6OlBGBf8JC2cmrYp0akHDN3Nz+3NDNeEGZWhA==
*/