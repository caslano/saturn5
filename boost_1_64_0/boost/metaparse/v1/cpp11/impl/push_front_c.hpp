#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <char... Cs, char C>
        struct push_front_c<string<Cs...>, C> : string<C, Cs...> {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
tu+66nedEDN9o9Y55Xk1vPcRfHpRv5t++qK9/rPPPrLGV34/HtXzvmYQ7ZBfzOj7dpXzCevovZrGLbbLwpMr4cV3l8Z7aHpZaqqv1Kld7LfJhWNOj6E3f0tPfoafjaW442/fEkPMtI85rlaHJ2Zhy+/wcW/2851ii9XiqTh9p7Va9VVpur3VSNeeG78XVB31IkzfIW7a8TW7rHFMhab6tuLgNTkYf2bSosnyEPZ/do9cV5sOEUfvqTWbWn8uYm7j6KVGMLGJOjaP2MzWXJzQYlXa4qDB1iXjMXwE5rwqh/Oy8wixuMoYV9ITXWC+vmNaC9yersczk+0+cY4k61XPy5/V8g1n5u2EI9bghRR8bY03Zl7vlYWv8r17XN++rBZYqhfTwZrGTt+F4eXVtcXqq/VxX4r42eAat4jfNGM7jMcWdLI23Z8enmCuX9nL2pZN5GjeH8xNX297qpovDxxtbJ+wNbGYzz67CXaI811w/9USwZ4RtVMxeq9n4Gvrxdfg7W1wWy/tGXHYb758TGSXTPaszDNnc7m1iu9daz9RK7aTv4vzir/O+saVY3SneK0J+6zX55+lZr6VzHwY3rygh/Atf9CFHVJwwmZ8OF2Ovi9+1bSJ86xdw9WSvxd3aoRZI41D3lwKX5tYm9qHX5+kc26coI7Tl2u6CdclwDrr8q3S7FlrRE83o2/9eytfDpGPz5aylqPuP8DGB/vCyk76Gidoh5M0z9Vy+YDYtT69ig66ui6s3aU2Nb9ldfWLytOq9su8c4sapaE1I7HbqAYcpGGL0a5taPTu6qgzJe2vpvuqx3vLcGz9d7DvVXg0K2RgdNnm+hkV8AotXiOb+rsa3SknO+i1DY3IEWun7ferw0eJrfjaQBf6nV2yxXvy9EDOPGy9XC1QX78jlY4Xy0e2RDlcP4x/StxhjNYpB90l/tUhZ9XM2f4QCbXtDWlkXLvxTXe4NL0+DKPxpl8O19nk+R9i1oftJ5jDBzPi9yrT4WqklFXyWPxkEyc5m8DOG9g6TV22TX7QJN1otUvr+J5zXdY0vtbGjtvZ7IC8OEwX8ffeW9h6tN4Efp70tHHni9gbJeZb+94gOD1Yn8i5Hm8Ey2DzEnFS7zN15dv0PWyqOcy6bQk4Pg5OwLtCxrgMT07rJye2G1d+dput7jPnXP3hbza9oTx6Wa3gw1S6vSXegz1zxOSeTLDWOFs2xhOwaI86a4Lavsklashp9L74PUiTLsB/KweLg3toethTh34ogI+ayavZy+i/eF+jGf/fIW7P49ERasfh8Ex9NY/+GZ9qjQSeFtAjehoX7TD2lGLWhueKbxjZSW5WepguwJ9pcG6R35Ormbc4az5dDr+A+/k57638QHs2sCepC+2w6pha/2uc/BI9MlSNNDd+/wA9idfz74Ivz/JNX2sa+ik3HaSNBxpbHnpeTLcXG3XosMawo3FLmtH5X71f/MC+xTRmG/lcrhj+SYNfOfBaXWOEnfPlesR8nuC/ZWqQY7ea8wx/W0hjracPO9GR8LSqnldKO1qrhvNuotnqwwR6O9lnU9XdM8r4vTeNX04+fCQv15kvfZfvFlwCYwMMu5mWuMI+mlRjeknctOaranTVDzC+s1zOgSt/ps1qRfQi9AhriIWNtEdvtciueP3djF7ktxLqtyp0ZIWs9AgNXCWdLqLX6jn/U8ac6/dB7UdjtaVbGsinr8TvXnX15Kj1gqg+DvyZSSfeiCdLujZeaEebX2tfzjVvOBe8X+f40i30eS5lv/i+2hI0H026RQxUc/2FOHxEQfGmvzlAH/9x/HKH2i63XCxm3ajvdTDgWvX2cvPztwcWOF9J+aOnVRYm5TyKnyL2BMA=
*/