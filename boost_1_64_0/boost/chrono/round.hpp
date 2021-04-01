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
nAH1oY/eR7rK+w9n7BPP10pkm1JAPlpjKbfjLHpKKwLxdjULdJ3OMJGunNtUCI4EjN1X4y7EiwQ9BxCsPji2r9KKBcATttFeedolqpiXKeYtKbTE2lXIPGOg8hNBPGuhIa1us+Pcx2F6+L3LYMZqoAuUT3Geor6msXU24fjR8PBtvq7N7lYnk2cxoMvlFPiHR5Qa/JskuViREBskBlgiXtuuJsig3zYgcx7cbbxVkPzjjtX5wphH2crVRsDYKiR7urftdpUaYADoVbweWP6cf42OkBqVgf8gFXU8QSgUb7koX7xsP/UQawhZxuuehfSQ/9Ehk7OPaDJejcWiFX7wlx6G9kYXqXSCeruoJ7AQVPjrua3rf/n1/evxJDGcCUiP8bb4yrCqKGVZd9YXzoJ+yqRsJUAFRrFwSPcI0VKQkc7bMLad9153VEu8aSt6wfXV04cRun/rkIgYAyFWvE4VfiCZjQrEgBSIK+hqY6s0ICPtkVelIzwB16NF881dKAV4Vq67T+nfEA1QgotWGiWgWO+k9KEijDjdXK2PahyFO2fjUG9LaCMT3p5bsw==
*/