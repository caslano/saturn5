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
t1f1lJSoSkLSjzur9zN6PEvvw9IgmId9rOd2l2Ce4gsRHzHLLwcxUfD3u/2hn3b+CvvB1z/BH6AcaDyO
*/