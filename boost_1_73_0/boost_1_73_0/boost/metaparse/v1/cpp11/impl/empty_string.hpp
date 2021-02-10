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
oYmH0qc6QRt09wjMewFV2bKyNCzjZwR6gBqR5rlleCNVxHJrSzq5hNxxiq4vCUdhc4Ltwn8kgURmMKRWV0kIqLlP8FR9iNj4ffX6K56u48l8Neosf078Qm3rfs05T9V+73BU6SBJU+U1FLq0EzItqgzJGp3ZYh3Pl2HHTbZcrGLfCe8IewuCO6M4zS/S1qJ/oBabE9RmSzYWdS2w8wrkiYFPRAltkyvbZvxQ1xJEqZVVqSoi5hRoGl2s2WIzZWwI/8zTYu+kofe0peZkr0oXfudjulrPF28t9pSmWFL63r9vsRYNeWvBnXbQ+Imk8f/yVHT1lKsjVty/zunffsg/UEsDBAoAAAAIAC1nSlLv0j0dJAIAAJMDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMxM1VUBQABtkgkYG1TXW/aMBR9t8R/uEqFJlVkJoVNamYiVYBauq4gSLvHKU0uxCLYWezA+Pe7Tvh42F4S3w+fe87JjbBobJoYjJiQaq3ptcXjQVeZidhTHC+aBzxOY+Y/M8GvRcHbfnbDRIVlcaRUltgElE5zTLcj74jGa0F48DmAu34f5t/ZJLEYQlxjD/r38Kr3VAj6EAzD4X1ILY8/YrbCao9VCI6cb5qAr5MtsrFW
*/