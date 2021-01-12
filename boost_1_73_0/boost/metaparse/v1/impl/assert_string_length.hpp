#ifndef BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP
#define BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/static_assert.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int Len, class S>
        struct assert_string_length : S
        {
          BOOST_STATIC_ASSERT((Len <= BOOST_METAPARSE_LIMIT_STRING_SIZE));
        };
      }
    }
  }
}

#endif



/* assert_string_length.hpp
n/eciZTtiJTtJ0IxwnXCTdJ6v62UzfownFoyTmBio9V73m4ZOK9zVLY4EtvmQp3p3nk13n+Nlfh9Q5ubev4eUNWWYRPJv6Fa7oT0cnMOHz/MUPgM3zN5btkNx4fbUpa2Mr8mUpZ+trKEREdyla6W4CXu2zyvDGpf49MSbNvc37zsyzSmmuMypahl4qpGLdLL3EvKSJkuPqNMHtXlGl7m30fKlGmies1liQ6OjvhT15VapooT
*/