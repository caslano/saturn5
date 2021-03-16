//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_CEIL_HPP
#define BOOST_CHRONO_CEIL_HPP

#include <boost/chrono/duration.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds up
     */
    template <class To, class Rep, class Period>
    To ceil(const duration<Rep, Period>& d)
    {
        To t = duration_cast<To>(d);
        if (t < d)
            ++t;
        return t;
    }

  } // namespace chrono
} // namespace boost

#endif

/* ceil.hpp
oORfod1ezDjzxRq3n3DzyauZBYylZu8VcTNjh7FTtQEluU0xtbmROZXZK8fof16coRg/rKu7AN1dFA+pXcruORGXI+wgzSm0X+oTWTsANTJH0+UVROdqbw2RUpRCfIaayB4iOLVXzEks4U4jqdVbtIKsvdyaPStN19TSWDAn0kSJBdHkadigitu5KTyLQDSFfLxtSC2LRy2z40TSui7s44ikeNIZQzID+zwk3yHPzHq/U4yha1EssiuVQME/FYs=
*/