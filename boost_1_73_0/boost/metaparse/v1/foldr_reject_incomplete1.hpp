#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete1
      {
        typedef foldr_reject_incomplete1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr_reject_incomplete<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr_reject_incomplete1.hpp
ifWiaLa/i5aiuxghbhMLxUqxS1Qd5u9iuVgvigyXE61Emhgn5ooVYrtIudTfRC8xTswXK8V2UX6E6YsnxXpR4jKfMyJTTBTzxQqxRZS+XJuKjmKF2CLKX6EdRS+RI6aK9aLESO0kOopsMVnMFyvFdpEySh1EL5EjponlYqMoMdr6K7qLXaLyGOUXvcRYMUusEFtE+RzjihwxV6wQ5f8kJ7qIHDFXrBQ7RdU/m5boLyaL+WKl
*/