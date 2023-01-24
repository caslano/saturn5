#ifndef BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_of_size.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/v1/repeated.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct repeated_one_of :
        repeated<
          impl::one_of<
            boost::mpl::vector<
              BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
            >
          >
        >
      {};
    }
  }
}

#endif


/* repeated_one_of.hpp
oXkF89UqVpgRJWuv9JvTf8X+WQZdzsBf7zPAPIv5AYvrLU2U2r35PgOpzhb/Qj0Ggso/Y3Ke5cZquJ5b7z6aM7AKjjyzRd/AV6CNeuNLGCCNk7Rv4AuzMF7I6J/FmoB+MJbx43TcUruaq+XA41spjeB/MNnIA2oNOtPygTdD24GLnb4rrp5m0FnKRw+Hn+WjRbi6fOB18Nflu1KqwwWzfF5Rrmsy6i1h9UuZ30Sr7XWoT7C2l0tqYdteHN7pL+hKRj80E6tKsxonfrMOzhz+iatl732dykriEcU8sVXVNZkmWkRVnXk954SokHrORUIZbZvD2sikZrAkLyDd5C8XKQpvz9DKZ3vSGi/mSdPYdA+mpDn+Oz1/ycdfypQndrBqFZlqCZDxP6gP3bWIZyYMzCJtwIZ9h3UsBv+As9nIn1Fv6uAlLHbLQY3tAQTO0O7Uin/kvI51OPP06DdhVT9a9oG0vuR1rmd8gi/7cMbz8wKjITntpa+1tPaf9KXM86S78bqC5ErRqt1oGetn7WPSoRDghJmElJYdrWqOGWiQooQESw3mmPn1ToSjjfg0pEUeDM4a7Bts8EeAAl1jdPLDfjACQIb51PjILfKwhUi3bXLCHdgdLHUjaFVbYZB9pMf0VlzvMsqHinS64dVa9TCpKKxMJPoY0hkzAiMCnPUPal2dAo2xlOi33Q36vPzyrk6eIv16OBcqtnMJqAjX
*/