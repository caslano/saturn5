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
ff+cnd+1F5/Mzq/PK23a+b1ji7LzC73ckaPE3/pE2/nl3RI5L/r550Wnyvmx9BGR8+NhZ5s5P5542UZr7A/m/Eh5mY8dT5Hz44KokaxVyopoJBFzsvaMk85Jfntz8uaFJ5uT8pfanJNHYqLmpOCljszJuOToOVk2TsxJxFiaTj/pWDLbG8uu/icby7IXO2ZHGnixI2P5V+/osfwytn07UjRV9vSPMFU27Ej1QA69X2SEcBsmRW6THelv0NPPyY7Ur9mRoqpKySSwNgv1wOBk+EuDv0wpMFiCawr8pcO9u2KcJAXGATmx9SVkAVnCdohAPRiVSl/wrbNRtd27IJGYBbZEpah/M3RLVFW3RB2eorrGP6tZol73LFqiNs5er1miNpYfRkvUBGGJijlG2BJ1sGSVf/MGrtEtpnstjIgvqFlMazYSwmI6pZdhKh5tidoOzNf99VQwf/mFk8IcXS2jbHdRi6es7oWfNQqYD3LCH8B5EMB5kBuuMAeDYL0PyqwY65YCYwHuY/PhrxD+gFkfVqxUDjqKEVbwWEWZQ/e2UB+EP8iktuV0N8gOM6FgQiI8nz6FTXCy6tr+tDYTtU+f0iY4X9gEuw2bYJqJec9H2G5GzIRhu/54z/Znol07as8Fp7Kj7v38H7WjphBCma4/bUf96lMazP711J+2oy58riN21Lf2+H9gR/31RsNAeszWI7qB9Be9I+yo3zEV
*/