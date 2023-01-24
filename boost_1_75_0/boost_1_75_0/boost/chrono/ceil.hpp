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
vw6B5Qn80yJ+Nv8LTz0xMKByy6NsHmjwELj7HRgXsftFSxZ1m1vrKinW7HIr1BlOjHaQNxh92treG6IxYaZdbVul8Psz9+O2yH5E5ab3bG5PoYudycIivTZ3ZK9NaatDgyvb42c3jD0pb/DGppN1a2hGddZDGNzBsaA6kEDzv6kjfZzhbYNzpY4+P5/5AdG7DHPvIgHmbLdn+PbnjW32w1B0UD8OSRzA6+ZVkTIpNl01xmjaC1DB7J0Ho/owb+PJoFOAhgQ3MeefUe0xIEWnBVLbPYyC1PWSyTiYFgTD6R+PaBLL5EcY1zKqMUJArCeAbqP+pKzZojVPwIpsoWnudT+ur0ebh4ix3yLm/p0N7Y/usH8gDlHCcvdv6MhIKgab5rzQPOdvBLWxLAxG+JtFnP+PNuNpJJLaNkQzsEb4lQy1TLVNPRO6cWKKxsxKwcd3Mqsgb1Nrw9+xte3HA+lEsMv81YkWpe9+IGw7mLDRVD/V0JFBvjyo9cFJ2+O58eYIewZJhOCLGNeFDe1NQNmM1NIYv6ts0W4LasDn4nDQXfOLSYGu+GW4viO9/T23jd62gSdv3xTVV39qaURH59S319HWXcvvUNduym2NLVExe4x4lqhCSjT6KOXKjTkY33JPZOie79YbViLAKctNjqW7gAlUVc9yxJSc8l/9jkme2F0PrwWWa5NSvrLkIIXG8VQN1M+K43eyCjiAi2vp
*/