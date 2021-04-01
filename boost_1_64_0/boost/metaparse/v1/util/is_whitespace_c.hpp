#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct is_whitespace_c : boost::mpl::false_ {};

        template <> struct is_whitespace_c<' '> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\r'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\n'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\t'> : boost::mpl::true_ {};
      }
    }
  }
}

#endif


/* is_whitespace_c.hpp
NaiEpAyy5DQV5yGjJKaF5KKJaEGUGNyH5vXpw5awr+6V/C7qElW1sh7QqX84sB1cT3QiJgXJPN6bBEEYPAu7eP1/eEeLqq//AvoCbrpaO1IjxOexL39UlAxCB1E+qwnOv5l6kKW4p/Ow6jl7ZXricIuUhQKOIU4VucCAVtPRGChmKUWT4g1jAG1nSyPpNFZ9koIwUpjuB3aAYrBrcs8JVhmfPKGJU4lSq3XqKJJve2Gd6Gt40RIcM3m3PR6wrQYXPkoo7pu5puB6LDdBJKbG0xtMvjr6y70Llg0zTQT/CA4exfc6GvuGma09W6RaKo7lc0Yx77dpFne0zfWeOqm1UtqrduzfrlObRXrfk1ynKatQgnpC2JPgscVSTew6OTIXgVFz/o/cbVTJ0cVMQHe7czrPvj9fvCMfaeSk6lq4jDYBup6KSabwhp2jF1YggsI9JT/5lyW2x+pKro/hZOsXkdRX8iiwXIsH7mgDfOjyPlf2mSbcG0UX2Manc7g2uAt+HaEsEfSeUgUOfrbZKOWnXuJz+rtWPJz9ak4Ql9IWyxUcfHTN+5RtfbDpGw==
*/