#ifndef BOOST_METAPARSE_V1_FAIL_HPP
#define BOOST_METAPARSE_V1_FAIL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/reject.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg>
      struct fail
      {
        typedef fail type;
        
        template <class S, class Pos>
        struct apply : reject<Msg, Pos> {};
      };
    }
  }
}

#endif


/* fail.hpp
7NQkOOS7VxMc8rXfEhzG8SjBQc8vEBza3UNwWI++Ijg82fQlinPwt3KCg54rCQ7PrxsJTpeSJTiM4xaCg708TnB42/ASwWF+PyU4+NuPBAc7OCZZnIOezyA4yKsiOLwHWEhw8I/LCA7y7iA4jOMpgkMe9irBod0PCA56OSJVnMO86QQHvUwhufkEh/ylk+AQdy8nOPjvrwkO432A4BBfdhIc4v37BAd53xIc9j3DF3PcKQQH/51OcFjPm0iug+A=
*/