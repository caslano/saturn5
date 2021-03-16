#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class K, class... Ps>
      struct nth_of : nth_of_c<K::type::value, Ps...> {};
    }
  }
}

#endif


/* nth_of.hpp
VSaogu/fZ+PD00nkkVS54e1hwp51bYnq1IA8klqAlD8WnXjsviiipjcgj6QqBBW6+ug5RK1oQB5JLUTKH1WeLlnyGFFbG5BHUosMf15PJTzLVgJ/akAeSS1GKt7ztSkrTCKqbUPySOpyw/uvfoHKG4ga05A8klpieIZvNXqSjdkWNSSPpK5Ayp/Rj3lxAhvBPtKQPJK60vBrhbY9yOZ6bzQkj6QqBXVj0bijRP3dkDySusrwMlw6/mc2nu/WiDw=
*/