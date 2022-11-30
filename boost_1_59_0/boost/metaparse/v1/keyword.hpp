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
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
*/