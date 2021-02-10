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
R3/QH3tXnRcwukwQMW53XwHk0QL30/cpDQssl8IgIqoozusuDRMR0oRoR0EJCtqe7yEs4XNTm+l7Qlr9jjfs9vqlh78DquNi61vP/c7UN5OnN6vDjMCWriHX6Vwk0jkmpPPFn3gG9izuOngfek4aQQlt8Kxxh2XJdV1uj+cJGNr0trTg6Zwumd5oaZX7eCXpqAdFkPNIR9yEQiwWWOONBoLx/k0HrHO4sC51vrrd3hdzPecYjKyE/BDyKUYpi9BI91Jwu90XwiIVfLeSn2Pg/A0PF6Cj1eGdPssDqYSRKTV49w43dJnWYXMLrCODJxVt30iBJYGFcfo0ey8yIMgQaDCpXNYWQjS/sTAWGAa2e91KGwz2pTtz/jhsnPxpWa673P92hqmpLLXa0PBzCVrvjdQWMji5NIBcHiEvbG1IacxFCs9gxl01FBmKoLsE8ijtv4qX2DMvFMgVNhNGw1hfAHUC7U9LqjtMwRaswPdy1+lTyncQYmoW8x7GLLxtMCrX5TRdJYqT/ugqaI0GYyz+iSnTcWeC+u2VLV4qWGBXl8A3LS8Ry82XBANW6EdiS1sjDuvQGwSarNv3rrS/Rm60iziDqmUFVc1Qw0n9bJ+QXTBPa05XY6CNgWQKr4qlutvUuXNb15M+tqcDfL0q
*/