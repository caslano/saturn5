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
I78Uwxbp9M3HKUFbZxhfeu4JkVtC0647ETlKNB9IRrPQU9SaGUkUS2O/3gbsoQVd/i4/OZ8DdiXIaQlE25tDiiufCJj0aNi5gvMQJvH44Wv1XtVeYHPMBpumCneGzdvswrjwXcQVzbk7PqjRuegLlRDF5AVMFbUQCU2A5nuFi3aDNXC5nV6wmxilwp+VVq3y4tJ+BESljWAkR53VDcB1JcSyqQlZpmJAv7clod8TPMU59I0PM9ReVL51qCtm7jI=
*/