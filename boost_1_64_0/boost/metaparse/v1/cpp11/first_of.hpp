#ifndef BOOST_METAPARSE_V1_CPP11_FIRST_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_FIRST_OF_HPP

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
      struct first_of
      {
        typedef first_of type;

        template <class S, class Pos>
        struct apply : impl::nth_of_c<0, S, Pos, Ps...> {};
      };

      template <>
      struct first_of<> : fail<error::index_out_of_range<0, -1, 0>> {};
    }
  }
}

#endif


/* first_of.hpp
7AKvcw7gZPFWUbuAWyxsOOgVhFF36JVw+6nEu9MZE/nN9ROlHlRryHo++T2U/wHkkXXV6+33KH1HZUJ5cJ8FuH4dgkvr158ovhIOJ/1nwLVJ6IQEvlmnYq9KjS33x9yz/BeUuGf5HxtHYTvG4Bwt7m/Woz16Dsl/1iDR1Eg3RcxhbBhfHJHzy/9AzKezg3RiXjz161rXN7CzFidG+TO7mvAE7yA8aPukv+b1e/ous/7f2bf/Q8KmuHkMvv0lndvz0Hk4hM4jgs5Pi6QTHxdO57EQOo8LOsvHFUfnyjx0/hRC58+Czo1F0rk3D9+eCKHzV0Hnd0Xy7dd56Pw9hM6Tgs6fi6SzJQ+dp0LoPC3o7CiSTjYPnX+F0HlG0Dm3SDpn5aHzXAid5wWdC4qkc2EeOv8OofOioHN1kXQuyEPn5RA6rwg6VxZJ56t56PwnhM6rgs5dRdK5Kw+d10LovC7o/KJIOpvy0BlXNZLO+Cpxu7hIOtfmoVMSQmeCoLO7SDr9eehMDKFTKuicXSSdM/LQeVMInQMFnY8VSef6PHQOCqHzZkHn9iLp3JyHTlkIncmCzveLpPO7PHQODqFTLuj8rUg6T+Whc0gInWmCzqtF0qnLM54eGkJnhqCzssjxdE0eOhUhdN4q6JxcJJ0b89B5ewidSkHnriLpfD8PnZkhdGYJOr8uks55eeRgTgiduYLO5UXKwVV56MwLoTO/au/t0V/mofOOEDoLqvbe3nkyD52FIXQW7UP/mZlHDqIhdGKCTrxIOZiRh048hE61oLOgSDrL89CpDaFTJ+i0F0lnR572WRxC552CzoeLbJ9n8tA5NoTOcYKOV2R9KvPwbUkInaWCTqRIOmfnoVMfQme5oHPBGOiE37tN0Iq1vW+c7E32JflMc0g8fOOtILrjMG8+vgpvXk3Am1f5zrnD90xQ9kZR9tIxzNHXO35s9Pk30HDvxOA+Hr3919En3p9z7+fUwK/NalGesjHM9eeG+9WBzzxa/Tcs8/htkrW6vp1DKfJSjENNIOFG5s6PPBjjNf/mKl4nfBrrhPl8/LQQbIl4a+4ECpfiPHxQ1kmirMvAi1bJi+Llw65Hklw4ewLtVaLM5+bxpVgUX2jNrMpdR95QJdf7cf+mqoDfRisaySxd2AwqpSNztE4CreBuQXxyIOPdzrm0ky3vGEdOPktMfKovTfcuUtnenfVL6c4l/IGeUjW2e2kz87wPcKrN77sKWAZ5S0h5o7qmt4bUFtG6vqF6okgchmcd4NkmlNvegVf3Y2snm7Lj7Nlq3vvtNLKq+Qj4SZ5/f8WAHweZ7XJklpoRKMX1VR1Z4J23HUcnamIJq2VS3UF+Fcn1TKKeiwvgsjLiYkIU49kMPP0F+NVDMDj/27gccVssr3wpZB4Z/+1ejmdluKMYhMtZBxoe2HupKcHD6UX0D3vuDng9r8Pjdu3MfZfi/uJi+BvZKmhNGiOPYg5ftsL/hQnbt79jHDb0iAKFV4BeXwi9NGmtjv6BPnoZlqnqBNBuLdS2W4glXcSRVMZ4e8luH2B04el8T3GgytXh/p5tGv7uwFPTP/pw9sHWw2A0eHBP1sIMZM0TC0anEIr9txWpU4w+w7jaHtzFHLQ40l4whmWkTimij4TeJ96LNrDnocCvU8P5BT070L+sI5PKODzMpmXcsK+nOU7zEXeGt4+Rj0c6stnnBTwtEXp6h6/TvFbI5E4pk/soS8H+SgZ3NOjn7Ke9m2gBhnpO+B7MewgG4zeNY+6e2nsRNvHaL1angn0/wp0M69yXAW7gGu99oMpJJx3n7mF9SKVvUekfcdK5PJ3A/9EqdSemhH9yX+3jLh6kM53zff6QLSDeb6s=
*/