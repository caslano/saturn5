#ifndef BOOST_METAPARSE_V1_OPTIONAL_HPP
#define BOOST_METAPARSE_V1_OPTIONAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Default = void>
      struct optional
      {
        typedef optional type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Default, S, Pos>,
            // is_error evaluates it anyway
            typename P::template apply<S, Pos>::type
          >
        {};
      };
    }
  }
}

#endif


/* optional.hpp
+Qgof4cKbktqKkviOH5U3XEcwxlcvPtpCX8Foesh6JstijZ9C0XkKG7+K6b/Ga1bKum2VTGJ+3UhvUMrbtFcJmyPpbZBNGG5cyU53F/TJXJXGaQJeTGfz6ZMmE3pNFnsHlLF1zjZDRqEYdZSXEuXQ2X9MJUo5FJiBk8hQ448Q0Px2iB7sMilBd8U8LsGVJbSwMEzag+8gaVPUOeyQFC40k6SQtSqHe89wFtU9EoL9Z+CkAP/JTxH5OyZsKMoWlER1fWR0OtIVKZol7Iqiig57h0TiXq95iqbsPAcgu9RJkkAYUV4KOmIl9zaOtvxE2YQfKnUDRbSb0GTk1LunxON09lo33M6u7hcUKphj0h6yEXHbe8I6Wc0crkB33LgS4fGl9tymHML10gEBDbXLmDpbWNLAUqjnRa68KLHupCKhL9BG0xY08MmI9xLl0SsrRvBM2Ad9snTebYiLCNoqNn//PZyPr342GFnQmBJnw+jwx+OxlOp87IsthMe3YV1XYdLbdYhhUQldIaZ1/bvYfNzr4382gR9GHzfC6+2cdC0heb+l34KXkJl5Dhokjc+ttTKkk3/ZNCNT04H8TDDXvc0PjkeDhLeP+XipNvtJ/3gz0lKkj9i6ZGmSCn3nfaqeWh/tPvj/AZQSwMECgAA
*/