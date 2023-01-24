#ifndef BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct first_of :
        nth_of_c<
          0,
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, P)
        >
      {};
    }
  }
}

#endif


/* first_of.hpp
+tmBEPbMQC8Mj5gG9rkHHVMpYMGLOYsz3W8jMwu0sIZ1VTPl3biHXbJnWspHxdikMpbUtCATmkyVR1BWIiRyHKu3lEB1ReELOfZMdxx9dssBRVkZ9FbU9NHcHmCchj/6evijz/UJ9amADLNEM+N0XTlFlTDWfTs/OjyqhBmjrt87Vbt07O8YgRHB9209gnzPY8rm5UTElMFMAA4s8dNxHOZQYSouYCVlUXCZXZIxiMwJGi/Gl0nHMLLs7CFlmxLUkLKGhO5Cyq6LPWtI2Ye4t/i/hJQpuJVXGvlWeVhI2TY1pOzHBB5SluUPDymrp31rriI+av9bPNkXMRRPJn6pjkvupctACTX9OA3fi9XFYgOOUBy34+u0kLKIVeI3Y9RV4qpewZCy/JjwkLLcmIiQMhyx4TFl8Qls9kuiBlkoFYwSq7TFuoaCyiq7DyrbwYLKGiiozBQaVNYwZwdcSqWoMWTsK6j+ZxwGlrW5U4PhWv/4Q8/CtUzf48rONoXSTuNBSJAZizpjq/BpVlyF7xJsFqvvEmw2YyMdh0SqsbfFF84WbuYyamFmAPxbRh5vZlRhvOs7liKCFZINInHiNH9gnPZAHeGtCKV/i1Y/b89Oiz0Xd8yO1gWjDYUnJR6iNbGN+GLp2YIILtvAxfpdYBV5aTE0OokFtp0QQgPbnhBCA9ta41miZro1V70l/dD6myF4/Rb1euDnUL67Jlrl
*/