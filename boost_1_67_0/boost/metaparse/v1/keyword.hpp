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