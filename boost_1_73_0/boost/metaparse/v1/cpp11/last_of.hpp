#ifndef BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct last_of
      {
        typedef last_of type;

        template <class S, class Pos>
        struct apply : impl::nth_of_c<sizeof...(Ps) - 1, S, Pos, Ps...> {};
      };

      template <>
      struct last_of<> : fail<error::index_out_of_range<0, -1, 0>> {};
    }
  }
}

#endif


/* last_of.hpp
qhvvo90i5zX+jfX4FhvxbR7Ad3gi3+MAruEYvs9JXMtz+BFn81PezM/5Mr/gCm7k6/ySn/OrUMf1a+7KTazOb1iL33Ef/si2/IldaEWm9tgB7M0KPJU7MYMVmcdKvJa/4dOszL+zCjdxVzZw3O/GXqzKXNbibNbhYtblMtbjZ9ybP3Af7iMPG7IZG/EENuZQNuG53I/5bMr7uT+f5gFcywP5A5uxteOuBbuzJc9iG85gW97L
*/