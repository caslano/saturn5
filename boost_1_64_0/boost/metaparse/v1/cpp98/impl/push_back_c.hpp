#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_BACK_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_PUSH_BACK_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>
#include <boost/metaparse/v1/cpp98/impl/update_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/size.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_back_c;

        template <class S, char C>
        struct push_back_c :
          update_c<typename S::type, size<typename S::type>::type::value, C>
        {};
      }
    }
  }
}

#endif


/* push_back_c.hpp
NH74PuwedHPdhybln+CovbJJaCOnW871UQ1FBEObbDhcwOeYT1PeGB3z8PLm8y9L/0HQf+xaW+2SRuVHsAQs0DgMO8y/ptvBzYGXUt7Th6e3WceRGJ7Yn8KlaS3hyO+ROTbxHoF3DuIT6aJ4FbT2d4Z5CUoHtcsdBHk05ZeUvDe4GWuQnl3nTWkv3VsNLOOL4SyUlzoR7vacqqnXhjyzzhWhHJwSdr8vFVZSTXneqXK7DD8pg9GHDmGfDz7Xz+vHBCY4YCD54alfw6NVpkOhE7ACUKYZQ3wuGfuTWD7Gy8lk5cyMVJhWdafXzPrvrcZC6VRkVnY7awkUkUq1FOTA22gxtdIWKTL2DC9XHpm3XeYjqBaHgDeMuRf5g1m4NYC7hMZi77HnoZiblwWxjOQb6OGnegh6TJ+Tza8LGNiVJgLLGNORGFdfo0iYYoo2XV2KoTT6tHKMwm+8yDAmDoEj8+9Vb7eXcdhBge4mcT3B6IDB6Kl1qjAhUeLQpBXaoZ+WWMwT7Etq4snUsRHkfyMgnEuqiJ9NrYhpFxkrw5sG1fecrgQRrV5nBSayOQ==
*/