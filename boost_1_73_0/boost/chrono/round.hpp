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
9s8NP6uv7zBcE3K+NzUPGvvZhINR1z6ZvmKCifmMUFv5vthh8T8uVFuvhaGf2fox5robzSHT03Sld55jVTV7rB5cCatNfa1Lww7J9wPZ4TrZmm9V545WFfZ7xrPPsI65zneHyfY/aLJ1/XqdpFHN39rsM+24yq60rmE3REUrXH+nHJG9PsxKq7j3As8Tuwkcsd9kmX7uuvYHkr877XY2VhvF8Z96jr/C/g6W+CkKhfvblaJf
*/