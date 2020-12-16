//
// wait_traits.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WAIT_TRAITS_HPP
#define BOOST_ASIO_WAIT_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Wait traits suitable for use with the basic_waitable_timer class template.
template <typename Clock>
struct wait_traits
{
  /// Convert a clock duration into a duration used for waiting.
  /**
   * @returns @c d.
   */
  static typename Clock::duration to_wait_duration(
      const typename Clock::duration& d)
  {
    return d;
  }

  /// Convert a clock duration into a duration used for waiting.
  /**
   * @returns @c d.
   */
  static typename Clock::duration to_wait_duration(
      const typename Clock::time_point& t)
  {
    typename Clock::time_point now = Clock::now();
    if (now + (Clock::duration::max)() < t)
      return (Clock::duration::max)();
    if (now + (Clock::duration::min)() > t)
      return (Clock::duration::min)();
    return t - now;
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_WAIT_TRAITS_HPP

/* wait_traits.hpp
cST6W8w4lTuWTQW8i3Sn8FCY53t8r99e5wy1l52JF/CMhQX09QgfC5ufLUV1v15f9znf37D4Pl3O3OiXHaX/Ke+3FpBJFtDbK+/qw3Rsp/1eu+mzT56NoKWAJ5J2CS+FGZup1zbpmKy5Eqzz0Fc3JSZe0zSUKeC3pH0WP4V58vFpsSD5OJd0Hwm3CzN73nOacc70Qjy6nHTPWvYtK+CHpP7l1hnurONbrtm5U+qmPaingFNNOklh3ty0ECA/kK/wtL7LoLJICqsbV0r1vXeH67RYMTYQM3e4Zlp9a+fI8jVxrBn24nAsLeCTpL4VllzJNASmNQXgpsxTq2UOSZkyPh4ey5UKeBLpYsOLZGN1/b2E2HoNthfwYtKddh0bwGMnNOME4uRd33bV1G9JnDJZwol/MeSzO1tbwD2kC1fa8nyLi6XX8T0NTgrCdH7Ww8QGGrTn3MqKAv5ImjJ5U81IjSbdODUISkez8Uuj0+v6Ah1YXcAY6YxVSs7WOElj2s/nyKoC3k0alzw2Nr/4gcfFcdyo+HzVfaXrUDmmgJ+TVh1jvY8P12Mx7tML1I117OWLbBP5v/4b9Vzv/7/3bfups4CAGKw+v8FTA/xuH1bAhjXybWpM68mC9ut7Tingg6RXCR/BwvlIO2xpxpbRRO3eYcP2Zo3o+AKelftStfOwIbG/83z4PKqAR59ZwLlr5R3nYnFzd8pKiyZTjz+ygC1bCjgg/BUmvpU1HlveguU7SjPeaZi31zb1b3btESqbC9j68AJK64S/wrz6NwO+5+uPA/9vBLsJfx9GOncLuOsV3Z47is8i9S2F+UIdemIBryGNrLf6JADX+fY9oYBbSdeqfAoPLXf8SQV8jfQrlV/jOh+Ydiypd4OdT+P/gf1KNDtQX9zd3h0FfO+pBUzX3gU21lBstrr1/W/79frVnCnXtTmP9A2G2vTXt705jM1OJBt655myxHS3Y95WnlvAU3cXcMNx0s8a0/yUD//gs6nzUzh/No3had6Lm2jDY1l+fltV2xdljsarCngpafvxUi+NxXrkvp06/wocm9HaUt372ODwyZJPhnzSrp8So9do9F5Ed6/RGYveaUTpnUa41296fgGDfbX3Vlj9ebP3jQWcRrq2z5qH/Hh0n496bt3LOYAUv7+ft8Z1vr63FPBY0iaVT+M639ClnOtJoyqfxnW+3GUFnES6TuXTuM43tqeA95OmVT6N63yDlxTwfNKSjVY+Px7NzlHxnWLbNO/leyq+Gtf5KnzHX5CuU/kEv4/WoqP0W73vl2mS+35WnMqcHYsw3dR3eQHfJ11ygnxDfqxBm6O6PpzVt679sA+nlc9ROUcduraAd5BO7Ze6Cmb1XcRnw9bzyocL+BPpeptnIA6Nsa2C42UCnr+N/vujPbYOto3PQMy2Vz8ee95bwB2kVSf2CD7b52J917D+BicFYCq/afcU271N2t26qzTwoQI+S7pSeCjMa4OIz3rytmcrlWgK8rvXl4sQj9/I7Wc34+zRpMSbsmMhj3ONu4p0ktTHxuraOMi8Leux950bmcZbw6tywTb7fK/VXX9nPsL2/2gBt0sdArA4wOfhe36eOvzAXx17LU1bKP6yz9dtVLZQjh5pd9WCrWb7ORGnbnchshznyXKLG4dz5vMFrP8C578HyHspzNMLmggp5hyF5+v7OX+Q7jZ5i5y3Z9uQoQzTyjaAekb8+LV58emqbaWfcftkmxcL3WnLTxSQvb6AnSfb50lxF9tFGiEuMS8WIslxxPq5aa8kXWzSSUGY5kNMlSnyXF3/r8E6kXA7ShNvYjRhy6RDai0M8U9lbBaNz2X66hrO0edylvfR6BN6r2cBIP77DC8=
*/