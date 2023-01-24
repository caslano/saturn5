#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C),
          char Ch
        >
        struct push_front_c<
          string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>,
          Ch
        > :
          string<
            Ch,
            BOOST_PP_ENUM_PARAMS(
              BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_STRING_SIZE),
              C
            )
          >
        {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
AyZY9REBTjHTdnSqbxeZab7tNWaRjR54E0/AQZXA5G1byHOxkvmo8Udeu4Ubmm3cVLvxIqK5qXsfdepZfdSXbw811h3Tz2as79pMi2n+0csKWPJWCmlEGhqqy5QlPdXletQvAgl8oX5FWTcGfG/NgH+sSTXgNUN94d81Q33C/4uhPnMbc6VhEYsQVxlSs2RzhI3edyCzcuWuXutIO/2Prf/VTv9gE7fTC6ecv51u2xx04uS/jhEI3Ei/d3WEkb5+U6SRXjigGyM9mOsDOCsEgdxIBHaKzP06K9jZqXJrI8Nh5LOTWc7W88GhZFMQhxUAdiCJfHK0QPjsWyFoQHPy6cZINJ7qz3fCB4O10ikyuNu1z7lbwtY+bcG1T/S6maJCUQvlY1wDjW/EeIr1Tv+Qz28E9GrkJLZKnFkM4P/l3JjSauhzjUFM34AxG0hz0qoozqhsaZR8bThJIPKvvck9bpqb6M8GzdWmro8+fWEXR1HI+igfujrmptUxafng5ghpWURros026ZRNOta9tNwhJzbQknnVDZq0fDsoLdvqWfVXAjNrry23ydPXBYoYWH1NDmV98bicAZM97QGDTfpaWjcL0350eMy46tqTbUYb7zkJKgpMYKft0npNoH4t39VAXtqbQkVkPrs2loa5Yh70Gi18kCe+WTH3fg27kFIQW6XdNqrdnU6zolVbhBz/Cm2JMmE/XPgqx4FR+KV6
*/