#ifndef BOOST_METAPARSE_V1_ONE_CHAR_HPP
#define BOOST_METAPARSE_V1_ONE_CHAR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_end_of_input.hpp>
#include <boost/metaparse/v1/next_char.hpp>
#include <boost/metaparse/v1/next_line.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/get_prev_char.hpp>

#include <boost/mpl/empty.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct one_char
      {
      private:
        template <class C, class Pos>
        struct next_pos :
          boost::mpl::eval_if<
            boost::mpl::bool_<
              C::type::value == '\r'
              || (
                C::type::value == '\n'
                && get_prev_char<Pos>::type::value != '\r'
              )
            >,
            next_line<Pos, C>,
            next_char<Pos, C>
          >
        {};

        template <class S, class NextPos>
        struct unchecked :
          accept<
            typename boost::mpl::front<S>::type,
            boost::mpl::pop_front<S>,
            NextPos
          >
        {};
      public:
        typedef one_char type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename boost::mpl::empty<S>::type,
            reject<error::unexpected_end_of_input, Pos>,
            unchecked<S, next_pos<boost::mpl::front<S>, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* one_char.hpp
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
*/