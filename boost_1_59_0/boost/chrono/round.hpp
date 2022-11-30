//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_ROUND_HPP
#define BOOST_CHRONO_ROUND_HPP

#include <boost/chrono/duration.hpp>
#include <boost/chrono/duration.hpp>
//#include <boost/chrono/typeof/boost/chrono/chrono.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds to nearest, to even on tie
     */
    template <class To, class Rep, class Period>
    To round(const duration<Rep, Period>& d)
    {
        typedef typename common_type<To, duration<Rep, Period> >::type  result_type;
        result_type diff0;
        result_type diff1;

        To t0 = duration_cast<To>(d);
        To t1 = t0;
        if (t0>d) {
          --t1;
          diff0 = t0 - d;
          diff1 = d - t1;
        } else {
          ++t1;
          diff0 = d - t0;
          diff1 = t1 - d;
        }

        if (diff0 == diff1)
        {
            if (t0.count() & 1)
                return t1;
            return t0;
        }
        else if (diff0 < diff1)
            return t0;
        return t1;
    }

  } // namespace chrono
} // namespace boost

#endif

/* round.hpp
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
*/