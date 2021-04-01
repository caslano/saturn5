#ifndef BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct back_inserter
        {
          typedef back_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_back<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* back_inserter.hpp
Kg3hPLARLLu5OdeFlDgxbzZvcn1SVPGdvUQOYjg4PrJhVvNCuz+NlWXXBFKSO0aevSo9ycmEaw+M4GD6YLI5oF6W/1ux3GEsdSth5tj1E6paVDNwWsYePwOralnQL5xXJWI8Usr9alenY+RxtpT2pFKcQsX1N7DwPSefPQ/i2k8YT5cuA6BdtsC90mPOzT4Gv/V/C8/yNaYtHs14Yz7XcRFA5b/xLLa2fwwW/EjZ4JWA66UsnJ+Mo+0wBydekDWgvabVou3OlM4PAYzAFKPMRWK4kxjt97kj5a79mEa8eJdp3N1/IBtvn4ggIVNK2dfm8CuV2Ex6S4T1z+KILjFGnC5NW+TaHKcoIMAyaShdCKXAxMymNO/gtol5oZdKyd/KHU3DdCId/NR+VcTjjwLjZxJemkWoMOihM9GGmBC6GN9ZPTKdkrB6nbxW6IvUWob8HXsBEJAHtAF25Jz4Tu+JjB8hSZ2GplxlI+u1ay76TqW4+LwNyin35gpIj4sXwgTAWEotgKuXInjJdnNRXqb+EuiayVnoLZdFkmPYHphnQaNVDfHSmnxvs0wvbQ==
*/