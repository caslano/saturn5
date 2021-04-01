#ifndef BOOST_METAPARSE_V1_CPP11_OR_C_HPP
#define BOOST_METAPARSE_V1_CPP11_OR_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
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
      namespace impl
      {
        template <bool... Bs>
        struct or_c;

        template <>
        struct or_c<> : boost::mpl::false_ {};

        template <bool... Bs>
        struct or_c<true, Bs...> : boost::mpl::true_ {};

        template <bool... Bs>
        struct or_c<false, Bs...> : or_c<Bs...> {};
      }
    }
  }
}

#endif


/* or_c.hpp
2fkYl3bXw7ia0K+jBiaeC/K2ktr9rnjgfMeU0C3rt11+rinDOGZnmed3hZQHgOqngdtzT460tNmkDoh+ZM0Wrj4tiVL1Bw7NhFtA4KG+a55HV+2+oIp9wA7qYPiNTxpko1HHUcNCzPAbfiVXo7UiEIvR8oaE6VeW/q4Epm1fDN+0I5iXVFsGEgU9xbMUkwHO9SSGo1m4/v1side5MnxgN/4NITmj8e861XUmcwLreh9XhPyE3I86+mPwnpZ/SA6EARgCd0fgNW+IsJhcTUZsRniodv622F5ywil2CUJxYqAodMsl+ZFK6NIgKudcvanCFsQFspq5tbfZq2WHhbpZ9NjlzoEXuiKRMLqG+NqENXMmhY3I9chmT7ioy5JPEXmxgz+A7lP59hWfl/YklWOtXWwvcT+NTOuVAUG+BTYfdnnf3o6Fm0wev4dXtXaDJj9FP0faY8KWipgaNBRDK+QQOGVlI1lZAZt3pioHWrFRWPI8lk4w/tE5QwsXqw8BQuvMDAA6OKakP7fZUlPaIVagHVp5CrZ3x2gM6hcv82QPbpwthVs7zko7FD+efQ==
*/