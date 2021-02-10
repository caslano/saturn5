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
WIoUPe9GPJTdcBu6laisjmKOHmRkBbxQoDiUkrZBy7Uh4xGL9YhU4GZRLlImk/beFTSUR10uQNI0RShUY1RuXKbg1cy0tRQU6C1TepA8l9rSXcKzbwSRQgSJS5GjGaQAZSKOBLehzCMqKtkq6K2Fms2K2hdSsvc1Ap6jJ2DYHgw8AxZEMtmGzwP/42Tmw2fbde2xP4fJFdjjOWJ9Goz7mG+GlgTQ+0JQiZYFsKxIGY0qgz/vQYNDTiJMRR6M7LEHsUB6ZIJxRFWADSVILmMusiAjX6jeClgemsaoXlm4MsA4e+iN7E9O0Ju5rjP2g8vB2HbnQX/grrtPRa1QwxitBs7TMqLm6zUbcZmHuiBNEkXoVV6SNCjIEmsgwFJROcloqwGATlMSJmZQnYHBGIYDz/fg7GEntdZiACyuZTzfdf6e2UMwUrbQJdyRq2zBU2m9NTaiAE3wChoykkJIZFVlQErFO0uaU0FUTZtVS0uqzECKsII/Giq6pYXWtSGaSmq2vgvFm8zcnnMYJcezhDDVQpdkvjRdZzq0ew4YGBS+9JE0INDDq53U/IelVDwLQp5hJiITi3qKdY0oO8i1UYfRm4ywxvogeBzjoTQ6Ha3CxB9HIqpKaxs7rt4fhu47U2fc974Vrn/7x3EvbX8w
*/