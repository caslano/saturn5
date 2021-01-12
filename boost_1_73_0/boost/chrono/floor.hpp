//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_FLOOR_HPP
#define BOOST_CHRONO_FLOOR_HPP

#include <boost/chrono/duration.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds down
     */
    template <class To, class Rep, class Period>
    To floor(const duration<Rep, Period>& d)
    {
      To t = duration_cast<To>(d);
      if (t>d) --t;
      return t;
    }


  } // namespace chrono
} // namespace boost

#endif

/* floor.hpp
Di17zKRzcpvRzBbKbNu9vndLPPUIn4qUvb7P8/XzJcg8d+4Jx3Wz1cqXI+f2HukTJP6CIYVFw+Q+rt5LKkFq7pdvLJjTTVX3Ht4MpLHYh9TOErtLxS7RWQs7Ic3LrV9qp9fI8bxkqpupJzse/c5HZJlEfJtCwk+mVDNOuf838j3xzE1F7kjTd8Nj2aCizll1Lql1q+w805U+Ga6dO++c5Pv1+2G7/4f7YefEnv/JGGlr5gn7
*/