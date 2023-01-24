#ifndef BOOST_METAPARSE_V1_GET_REMAINING_HPP
#define BOOST_METAPARSE_V1_GET_REMAINING_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_remaining_impl;

      template <class T>
      struct get_remaining : get_remaining_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_remaining.hpp
/os41cg7gmTn1qYsR2HkYpvp3GvLpaANXrS0tMDkfuhko7QGKnVmRNZ3mc0j63XPRbP7ZSOzvC2F+P1T63gNLOoZ0MP+WJuQGUi0SOSixaegTnuhtYkdtbb8ZdzzZ3n0KiYg9XscBKQqefWlFSQjActuHIbZfRHYFNgtpKiSyEWVsY/bCSLWwDWGn0nCoh/67WEvSzEFU04YRbX8jmIK0IsZJ5WtuivttPo6nRR57AlmCqPFFlX5qiHZQnfVX70UyJBKCwhILHLm6bz9A3kEQxK53811Ar/QotbDEIDgD0XR/s63yWQecQEGlhrt/N60ISfjhjxNbMhCqk/iVdN2UFSBKf5tpl2cgDIlnrDSf3+yG9Aj7yj+U5GeeCSYvjNl+EGYBv7xTMxCbXzfeAbI71bW8PGgrWYIGsyw0OCTM43sDiYf+Cb9nC6yFGME4rp32PQU3PH8l2IYNeP+E0Ac0J0eS4PYrR+eTS9uimXfnQDfzYIndOcFYXfKlkfgRDVgUYTrGfE19TGPD7S2pxQh9+SHFU2FXNVuMh7hgsfCS6SdPgBhLedyE1pou1Rou6w0mxm5Z8h1VEHiDOqKEYdgqdUVXN2vAWLB5x1IJB2s1yucUovjUKY5hgHDB9NKZrCpF7Jlej6XLbPzeSoxyFIHEQFzdK7uXAKnh67BIH8oIwQ/FPyxE3Xevo9J0cUzzJY3mIvOnmGumLyL8cX1
*/