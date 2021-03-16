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
jMxB+EjD5Fmhugom6Q4iddv8Xgrf0t3evoTnGGMxdBJzSHyB39BLYgG2RrTH5fPzMRbGAyZx1pG5NQY9Ro1c62JXumWo0O8W4RmW9wphLdR5VhkPw0UC2QoZBlR7TRoOqg1RQQc7mn1WG1ftI9JYs5DedgkTWKSGUgg/i4DJ+HxLCJM06TdoOKuZ/MKaVKm95s2M8EYpMiFzBAf3Mt6Yh7x8vZvd/7e1OXKzJJPCN44iA4hPrTvsCbiYepfnSAA=
*/