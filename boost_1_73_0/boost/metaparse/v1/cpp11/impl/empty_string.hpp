#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ignore = int>
        struct empty_string
        {
          typedef empty_string type;

          static constexpr char value[1] = {0};
        };

        template <class Ignore>
        constexpr char empty_string<Ignore>::value[1];
      }
    }
  }
}

#endif


/* empty_string.hpp
ntmsL/EupqvHbuzGo/gHdufTPIbvsBcr+f6xHMnenMY+vIknhuWtFYW/UxjKJNcWq0S5UFb7t+zBpuzJXuzFiTyWF/E4zuHxvIUncHczPZn12J9NOIAHciAP4ynsxsHswVM5kKnM4DBWkK6RrMYM1mEmf8tRbMXTeAizeThz2JO5PJZ5DHUm/FbYct/nN4S6ZTdyT/6BDTmfvq8uT3S/L49Cfvm7ukLxvt7r8y524SL24D3M
*/