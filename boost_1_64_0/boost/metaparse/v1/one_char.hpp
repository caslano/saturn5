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
mwLqUn1HNLt/D8se9wlChAuCDaG9DdpsVNX0Z/n9/GEURsurW2r5sPZ7TSrApl9YGhD8JxAQHkUNTfJbPumrog8ipWbdhU+SQefJyIZEpLKZHXrlxzSRcvCPTIA6/eEYzvto5XVHupQFtTDkVHkgPvadIXwoT74aljyVd0c9hXzZONoBtb48j0xGS98h0G/qzFHjcsQJWPbvMJ0ODxGbEQuR5JVLLoc4pSIuznfMewTBpNXzE9CMjFEK5H5aGrPZWQ4OoPmuuKAFWnuVDG3KA7Y4bIxl2I12hK2T4zldABYLwIXZOExVBNS5ctCxAUOIZz5QKMJD1076sALvsAtyArHx9Lxbh2aVa3qHkVvRDJ65wA53yTc1JbZqwpZzrPkecafmKb33zJyX44txCkvQIkV5kcCOCBwDBycqdi09nfQQsEgP8BfmsRCnu04NRiHzi0zzJ+fWpvyL9C6hSURaNWV8iEv5SdXMqNdqrimSzh4MaOQM92A3s9ptkSICKeItKS9aZgn2qj65hsCOlYPWG/LtgIcCPU6THQ3egwWhm+3HrA+t4Z8/6wQThA==
*/