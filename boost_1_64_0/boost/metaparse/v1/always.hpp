#ifndef BOOST_METAPARSE_V1_ALWAYS_HPP
#define BOOST_METAPARSE_V1_ALWAYS_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Result>
      struct always
      {
      private:
        template <class Res>
        struct apply_unchecked :
          accept<
            Result,
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef always type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename P::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* always.hpp
GovrllhW5ThKgJHkiHjxX3rVVU4D1l/BOCnWYJZiFOSMBmCHOvuiCqrysJy2OUjZEDZZIZsa6MerDN1qJnkHFAaTopeUueL/34BZGpk1ErsoWnocfLzXVQY6VVGLQua+G5CwVpehFxVRT78ub8l8WMBA9AwnGdXfbArVEZ0iq9BnIZRtlcrL6b8zoWzcYrmJF0H7NOr2Sq4jEJuPdAaluERnNA0H/GYkHWYzfzVT+wk/rIRcL8f5vKmK1eKAvj4dOa2D+TP0ny1gLhnUexTVv4YiCKDs8ISEh8mf8TOO0wroJqweYIX4rd686r2dvpLOiz3+5dgIYkAfZWuRtje+dXgvq0plxZO9N/UoQ53i12U1Lv2veZlYq1wCkKhl5EPfs+MAO6jfqUpVU1IFiKUOi4W7wIZwJoFKxI0ExqPcITRUX0mER0AiQegpTRr9ylB2Ix/H2lACBmqak4ldlAZTxb7Wkzu3oQxvb7TwdUDoVyNeYWS+GA2Pgt1xbpp+IelGkhYLKAQk4YrJfTmrKrD8oUv737KPLjfwrKvN/saQ2ZHMpBprf3HNC8Prjw==
*/