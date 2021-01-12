#ifndef BOOST_METAPARSE_V1_SWAP_HPP
#define BOOST_METAPARSE_V1_SWAP_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class F>
      struct swap
      {
        typedef swap type;

        template <class A, class B>
        struct apply : F::template apply<B, A> {};
      };
    }
  }
}

#endif



/* swap.hpp
LfR/H3VA/S4N3m26eSMKt29G9kTJKlyvBdvZBnzdzKTfoknDFTO3/d70roR12BTdg4X9uY3pF5jTJWay08ji7+Dv9b3UMN1G0803XVUTTB0ZX2aW6VrsGX8vvVvCfjAqzCvNcGKbLEOT+uyva77zxPXGrUhIw6BouoRjKnmf6mjZPvqJdWyxBu+X7haZ0X1GKz9VN29/v2JJ+1SUV+nb/8xjnbSeJi2paWnjDk44HkaHcUYl
*/