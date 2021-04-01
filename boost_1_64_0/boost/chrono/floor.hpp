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
U6Zi5XfK7ZtUM6Scy7Fr6u478vJIBpFCO93YBEXivMoVgwdkTs28I0ZgFyuebqaoDrbPGVVhHohCtybyyGfc1kXJKkRxLvDXce8gba9+HhfHoBjZuuos0WTzYKro7HAzJnUCNsJYxfwfqT8gSDWMsiwGxijBdmiReWbco+KhDvZHl9vYbagVPW7+yDi/RAYetfIiq2VbV1qRgsNOGWfck6ury7z2ZHnZ8jlKrlUsNkEfkkTH4glJdSiKXQGllR5ur5s+rKpO2ETjF/vk5pTMvWoNGsABVEq2RYmfWDRMoLFO/eZc5vPerCLkdV8y76+W4tnfPAsG9VeEi1v0h+IrHGbNLWbGRMfnbe4JhLsIIB3yl/OBYKF0A/YZXkfxX4TSL3zXacjxYLmv5Px8D8PIxuUtoiP63Y48qGek35etszBRW06aMYcUMTsO8RJGNL14xPKjsdcUYfbz0CCVAWsm0ArhK/JwG+tamwoV9Cnstec+YD5pgx6apDA0GW8XpGqFHxJnMDyCWtwwW0eCwZwcS5lewo9WhFdNOXdw/W8Jw+ErRk/BdbYD51qAEA==
*/