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
LWdKUr3+pwRrAQAAhAIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjhVVAUAAbZIJGBtksFOwzAMhu+W8g7WEMcRwQmhMIFgiJ1W1jLEMbQui0iTqsnY9va46caYxKlJ/Pu3P7sqUoilDjQBZVzt+fNFu43vqjCBpyKDaZYvIS/mCxiPy87WoORRoOSQc4Y5dd/UjYOpCFRHrd310f2B4w/WkIv7eJkuLAgpawJ1bFl9uKFyuqFUHtet9brCjYkr3DeASg5xVKVvGu2qZHAj5fnzPC9m2c05Z2bzRSEvr65xXKD1n3IwSg8Hjt9sVRtL2Jvejk60I3bmEKTya2e26GhjjaMADWkXMXr8ICi948YjVUkIcUX7YaFvo/GOa/U2/UQO6DySJXWm3mGlo0ZdR+qQE7HfB650YF9yOAorH0egvpOWDdrOR196O4HXfLpA7bzbNX4dBGT3eY48hzva6qa1dMF4/Pr2KNIOBRTv2RRnIi0TGU7Ay+usENzU0VQN6AO2+Idb/AUXR/JBK3p2cQrfFzi4KvkLIo8/3g9QSwMECgAAAAgALWdKUoS6FYlvAQAALQMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjgwVVQFAAG2SCRg
*/