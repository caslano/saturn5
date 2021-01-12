#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>
#include <boost/metaparse/v1/cpp98/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/size.hpp>
#include <boost/metaparse/v1/cpp98/impl/update_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_back;

        template <class S>
        struct pop_back :
          update_c<
            typename S::type,
            size<typename S::type>::type::value - 1,
            BOOST_NO_CHAR
          >
        {};
      }
    }
  }
}

#endif


/* pop_back.hpp
X8bIfPs5OL78Is9fPcI++Djzi9t7dijtPZtXjXYfWGHlvm5Jj6s/Suu9wNne81dt78nBfqgrBwALIYmwjnCUcJvgxgGhCsGPYCYkEaxtL36cfEUQPFjGEMK61/iNreS3h7cJLf3+nHYTW3vJ/0c7yZ/RRuLsl9o5OAfn4Bycg3NwDs7hrz/8W9v/rf3QWj/jbXsA4F9q/5e+L3k3St4hlbIXIbSztlueUe5ND4i0aN8hBgf3
*/