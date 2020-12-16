#ifndef BOOST_METAPARSE_V1_IMPL_IS_CHAR_C_HPP
#define BOOST_METAPARSE_V1_IMPL_IS_CHAR_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char C>
        struct is_char_c
        {
          typedef is_char_c type;

          template <class Ch>
          struct apply : boost::mpl::bool_<Ch::type::value == C> {};
        };
      }
    }
  }
}

#endif


/* is_char_c.hpp
DgTGqnv7N6W3iArsts+sQAHxwX2+p9h+u2E/2eMzWh3EYp67V6yzZ+SV75o4uSEQmKz9FR63b29khO9hcY5sRKR9UlGBTkecjThr399rzp/Mst8oMirQQZB05W0RgTHT7Jt5PnjGPxCYMN+ZK3seX7MX5qS9ktPqiOc9pz57nJEcJL4+NPi9JvZfDbFvvK7+2m1v5pRA4IA9qStb+L6ElhF++8HrRbLxqLNO6jXO3skVzjBN/Vq8kNwMWSje9La6kKevgud8emnTM/alrXcGN4d9umvJwUrfryI+dM0NvuPqLBm70X7q7+3PfsKee/me0H8DHnPO70NyeMpZZnGhATfbb092Bjayf0cfz6ttD4b9hudt7shv/+pwe2/qFdZHrexBFdcZuDQq0Fb9Ntojn4dM/84+6/P2AdUp5+zcNVFXfndslHtP26Lf3feU6x7OF3XlN1++I7fd4qJ8r19UoD75/lAfTDPuu3baS6LMRXi4sr2UAu9X9yX7PewLSrSHjJ51bevZyhP2fuuH3zemA6PJfEIgkHyGnLhuz0b7PN8K7R8tMNYZlobG4EP7zFwbSHB24WFnQ+TLYpyz2rdY5xxd2quN9gSdq0L/fPYediDtC3v5fhTHSnZOMyoyEHW/SHlD+/dni+urUzZt20sXOi6xZ8c+6Ib2JsakRVw5D1jsmO+GiTcmt7MRnxor5R1DfG17kbRleSrZpCvV7yNPApSlyPZ+49KzrzOxN9sbXCNSzNOeXefFLwWM4fP0olTwu7XtN60mDhthX3MvfV7Q/SlCEt2/QEbaHSJrZewjfFn88RN6Qi+36K+z9scfHuq5xSryuMr+wNTQb0t9VcIesSJi72KZr2jHQ+TqOrL3KbkrT6afzMQ2uW9eFMJgm/BvYT/6ktXLzs2tO06XyfT+9fZ60/ESdL4NXU6xX+3kPPFx+x4HDROXLKevXDe4sxii8R6Y0/kVD8neycI+Znc2tT1ZjKF78s942TnUvXS2hDb11jZn945OtK/+B+e9FpEPNrPAI75b+07nSr5krzYGAjfFBQJry9GNwfpzjrJcdwOdvd6Z9v7PslW57Pe+jX0oKxZ/VBknnM1xVqFwRHAfKx0mi58r/9p7pC9jG8caB/JR1+9r1Slpn7TzJcUzs+td6EorZ+fEQVPVtd1mcfc6Uc6jB5wFcV/jcG0l4/q8MWPfS9rXWKO1uO5yOpHfmLSJCPS/1fkT9ai/W5zc2BQb4Mz6CPd1NidxE/sdqV3byIwHDt+ShY73iZnqm52P07sC6nNL6Dtsu5k3Zr2kTnvZPvbt4iW6H9yvt9PvWA1nX/TFuCLsrNhtzWL22rNHm0aTD+cduj5NNn9yjqY4XZ+r3+U5cZEd7sgOL9Ne89fCm9i5t9jAOtpTy1hGOPtOBu5dQo9fcM6vv/NVNwUCpeTZ+aa9b85ZPX3UHBA812ech11vD207ulQq9Fu5+8K/l5sfO6V9jk9xKPzbtvuC773uaaCuhdlpDyU2bbVn8A/23ZPJKXT85sz28ZHTlAfISSrs3yt4O925JCbv/G5zbXuL/HxqTDLe88tS6ffNKUZeACWQAzEoifZoi2C9OpUO1S3Za2f0RHekoDcy1FeB5k1tXe7ZQDGyctNC5bElo9jtWV3sHV/huwzU/1hM5D/thw7KbofE8H0z3idyizNF2vjs2H+vPwewS+vsLa5v3pA3w7XpeYP5xtojPS/7n3/eOVyXPvhb92n3F3WMJm+LRwf+6j6++9jv+4aumVM6wz0Ps0sn/3m/ZLxHw2VkePA/bsu46r474MJf55kfvDcy5n2Ef1H2aNQ/LK++33Xp1YpOl2DnO0UFlpb+x3J0+gT/ZME=
*/