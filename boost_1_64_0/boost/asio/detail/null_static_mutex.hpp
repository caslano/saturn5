//
// detail/null_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_NULL_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct null_static_mutex
{
  typedef boost::asio::detail::scoped_lock<null_static_mutex> scoped_lock;

  // Initialise the mutex.
  void init()
  {
  }

  // Lock the mutex.
  void lock()
  {
  }

  // Unlock the mutex.
  void unlock()
  {
  }

  int unused_;
};

#define BOOST_ASIO_NULL_STATIC_MUTEX_INIT { 0 }

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_STATIC_MUTEX_HPP

/* null_static_mutex.hpp
HTs3WSZMofmsA9dAkO3V69L5DK3ugj20+2PJUg4z2D6AN8ASOoT3QR4dxcdgRK/deckyDY7SLnz3x5Olh21ieNJU5oRWr4RVtLpRocN47DTuT9qDN8IuOox95zPntInDMEhH8JRPJEuMVtdO5x5mzOqbIJ12XpAst0Mf567uvTBZIrT663CYVj8LiTcz5hnJ8kwmY6VjFzFXF3Pdda7wLMii3bgciukA3gAJdAhf/mnOi+MaeB1M1THjnZBLR/ARKKNlZrKcBUm0Ew/O4rrwWc8lnAscZA4DuAn20ybuhV10GPfDAB3FQ3CYlku5n2Ev7cAZ0Ea7cD700B5cC9vpAG6CHXQIvwo+zt3mShYvGLT6U7OTJUCr28GkbZdxrcFNu/BSyKENvA4W0ybeCR46gg9BJh3D4+fwHqBt+FqI0OpLspIlSqufA7mFOZ/LfsBBR/EQhNlGsjlf2EM7cAakfpnx4Hxw0B5cC410ADfBetrEf4KsNXz2cq4dDOix8G9hKuttOcmyAvazPohfhFRdP485gb2sd+EbIUCrz76CY9FqB4RoD34EEvhsBK/4DNeL9SY+MzdZ6ljvwufOZ/51e3wU3LTjSp4X8LBNEA/CYlquSpaPg0GH8E/BRzvcvGcgj3NU3w8+Wr0ZAnQEf2gBzwht4MSF3A98Vt2fx3nR6hdggA5+Lllegiy2t+Xz3IGTsTlxNrhoNy6BTNrAayGHDuLpi3insR8PXrCY+aeD+OKrk2WYDuFfQGTtZMy4lnBcWn0RJN7KXOGXYRKtXn0t14hWf7GA86VND/cJpPHZCD4Ck2gp5FmDNtqJ58N62oNXQxYdxFtgJh3Gz0MxHcMTlvHeox14Fqyh3bgcVtEBfEURzxEdwvtgKh3Fx6CHthXzvEAu7cJLoYw28DpooE28E2bQEXwEttPiZfyQRzvxfPDTHrwaGukgTirlHqtnzPix65gHbfxSOfPJ/IQquO4GzwsdwI/CKlr9VBU/C2j1PthOe6p5dmCHPju4CfbSJu6FXXQY90MbHcVDsJ0WP88m9NAOnAEJeu44H46y3oNrwa5ziJsgiTZxL4zo/nE/DNBRPAT7aalh/3CYduAMOEi78PkreEfdxvni30KYVgfq+H2FVj8IMVpWJsulcPB2rgW+8waORUfxsVXcn3RwNfcG7GA+w/h52E7H8IQvMU7agWfBUdqNy+EgHcAbYD8dUsMMjqt+FWbS6hU3cn1pdQMYtPo+aKAj+AhMoiXA/QB22omvuolzZJwm3gm7OFYEH4EBWm5me0jQ7fF8SKM9uv4W1vNZNy6HvTpmvAEO0yG8D5LYPoqPwVTatoZrBM47WI/Xfpl3Ix3C49cy1+xTvRQaafVN0EOH1fWcC+28jecAMmn1vNt5b9BqL5TRYdwPMxlPFA9BLi13cA9AFu3AGbCeduF8aKA9uBZ66ABugjbaxL3QSIdxP5TRUTwEa2hpYP+winbgDPDTLpwPebQH10IxHcBNsIQ2sX0dY2NO3Pgh6KHVE+7kXqLVtXCADuPCu7h/6CDeAo10GD8PDXQMTwhyjrQDz4I22o1LoJg28FrIo4O4Hfx0CO+GMjqCD8ESOobH38050jY8BdbQHrwa6hvYD94CATqMn4ccWr7C/QMu2onT7uE60ga+D5y0iXdCKh1o5L4CGx3Cqffy85E28R/BpG1NvCfBR7vwUvDQBl4HQdrEO8FBR/ARcNNyH+MBg3bi+dBMe/BqSKeDeAsspsP4eaijY/h9zTw7tPpa2Eurb4YBWn07jNAhfARs6yaL+rz7OR9aXQVOWh2AHNr2AL8/PMg7hzbWJ8vTkHrnZMw99hDPFK1+DNy0+2GeR+hj+wA=
*/