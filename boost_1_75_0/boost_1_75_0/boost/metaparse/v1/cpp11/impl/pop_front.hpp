#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_front;

        template <char C, char... Cs>
        struct pop_front<string<C, Cs...>> : string<Cs...> {};
      }
    }
  }
}

#endif


/* pop_front.hpp
0NgrzqEykwkeX0k8wKy9uAt3UyvICEArZxqtHDkmalIPgCs1i3IsKDZub5qag/GhxkO76CFzKucYU4FrTnFtGF9zWihHWpLvWULd295a5B8WhozIT3Z5ApdcaZxlpXCWVcBZhrmUB1xtnGVZAaUjCEQ7qHwVRM/0/ZQD8yaqSAtU4jrKf7AeeMgZZ1uBXnwODTlk0opswM3rLzzTF25nR1qvrRmJ4FiDCDaRiEFKhX+S+vbY4mNxSvjawN+mhPd9JyghHKSx0xMp4c9WgxLa8vlUDQRRh9BqHKjjffXnYBbuAvyDtdJz6CjFcPQiZaM4Ri86i4/Rb4KjvpMxdB0mFetrfCtSvsVs+H3oWG3zkrUEzq+A/u7kgtQzw0eKbAcwP5OH49jd/8FtcDAQadEDSkP+JiJr6VORrGHCCtsmOVrkWE2U6ciXAcmDJgf9IjLaavq3FjaNAvV+wbDe/pWMv/tD/YqI7iAX+9F/cAx+ByxREaV1UC6nLbjuP0jHp2Qi9Mt2eNc6yM6+MYB8sGvfuQygKwPRKY74U3wfALhZ3B8H952Bsisy8bWgmroTu0gLROFgngKscTpltbXJ0UK/dSE883NA+TXWC0biV37FMdieo+TI27SuZ7HwzMWALplnAroc2YNxfwTDUQnkzHeuyYSYccdFWUiofv8s8SKlwIuAKAKoqs42JZGZjUyiugZQTL3SW9ZHd+VZLUYt
*/