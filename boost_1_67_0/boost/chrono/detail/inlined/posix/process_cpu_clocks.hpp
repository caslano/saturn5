//  boost process_cpu_clocks.cpp  -----------------------------------------------------------//

//  Copyright Beman Dawes 1994, 2006, 2008
//  Copyright Vicente J. Botet Escriba 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//

#include <boost/chrono/config.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/assert.hpp>

#include <sys/times.h>
#include <unistd.h>
#include <time.h>  // for clock_gettime


namespace boost { namespace chrono {
namespace chrono_detail
{
  inline nanoseconds::rep tick_factor()        // multiplier to convert ticks
                            //  to nanoseconds; -1 if unknown
  {
    long factor = 0;
    if ( !factor )
    {
      if ( (factor = ::sysconf( _SC_CLK_TCK )) <= 0 )
        factor = -1;
      else
      {
        BOOST_ASSERT( factor <= 1000000000l ); // doesn't handle large ticks
        factor = 1000000000l / factor;  // compute factor
        if ( !factor ) factor = -1;
      }
    }
    return factor;
  }
}

process_real_cpu_clock::time_point process_real_cpu_clock::now() BOOST_NOEXCEPT
{
    tms tm;
    clock_t c = ::times( &tm );
    if ( c == clock_t(-1) ) // error
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
    }
    else
    {
        if ( chrono_detail::tick_factor() != -1 )
        {
            return time_point(
                    nanoseconds(c*chrono_detail::tick_factor()));
        }
        else
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        }
    }
    return time_point();
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
process_real_cpu_clock::time_point process_real_cpu_clock::now(
        system::error_code & ec)
{

    tms tm;
    clock_t c = ::times( &tm );
    if ( c == clock_t(-1) ) // error
    {
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            errno,
                            ::boost::system::system_category(),
                            "chrono::process_real_cpu_clock" ));
        }
        else
        {
            ec.assign( errno, ::boost::system::system_category() );
            return time_point();
        }
    }
    else
    {
        if ( chrono_detail::tick_factor() != -1 )
        {
            if (!::boost::chrono::is_throws(ec))
            {
                ec.clear();
            }
            return time_point(
                nanoseconds(c*chrono_detail::tick_factor()));
        }
        else
        {
            if (::boost::chrono::is_throws(ec))
            {
                boost::throw_exception(
                        system::system_error(
                                errno,
                                ::boost::system::system_category(),
                                "chrono::process_real_cpu_clock" ));
            }
            else
            {
                ec.assign( errno, ::boost::system::system_category() );
                return time_point();
            }
        }
    }
}
#endif

process_user_cpu_clock::time_point process_user_cpu_clock::now() BOOST_NOEXCEPT
{
    tms tm;
    clock_t c = ::times( &tm );
    if ( c == clock_t(-1) ) // error
    {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
    }
    else
    {
        if ( chrono_detail::tick_factor() != -1 )
        {
            return time_point(
                nanoseconds((tm.tms_utime + tm.tms_cutime)*chrono_detail::tick_factor()));
        }
        else
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        }
    }
    return time_point();
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
process_user_cpu_clock::time_point process_user_cpu_clock::now(
        system::error_code & ec)
{
    tms tm;
    clock_t c = ::times( &tm );
    if ( c == clock_t(-1) ) // error
    {
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            errno,
                            ::boost::system::system_category(),
                            "chrono::process_user_cpu_clock" ));
        }
        else
        {
            ec.assign( errno, ::boost::system::system_category() );
            return time_point();
        }
    }
    else
    {
        if ( chrono_detail::tick_factor() != -1 )
        {
            if (!::boost::chrono::is_throws(ec))
            {
                ec.clear();
            }
            return time_point(
                nanoseconds((tm.tms_utime + tm.tms_cutime)*chrono_detail::tick_factor()));
        }
        else
        {
            if (::boost::chrono::is_throws(ec))
            {
                boost::throw_exception(
                        system::system_error(
                                errno,
                                ::boost::system::system_category(),
                                "chrono::process_user_cpu_clock" ));
            }
            else
            {
                ec.assign( errno, ::boost::system::system_category() );
                return time_point();
            }
        }
    }
}
#endif

process_system_cpu_clock::time_point process_system_cpu_clock::now() BOOST_NOEXCEPT
{
    tms tm;
    clock_t c = ::times( &tm );
    if ( c == clock_t(-1) ) // error
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      return time_point();
    }
    else
    {
        if ( chrono_detail::tick_factor() != -1 )
        {
            return time_point(
                nanoseconds((tm.tms_stime + tm.tms_cstime)*chrono_detail::tick_factor()));
        }
        else
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
          return time_point();
        }
    }
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
process_system_cpu_clock::time_point process_system_cpu_clock::now(
        system::error_code & ec)
{
    tms tm;
    clock_t c = ::times( &tm );
    if ( c == clock_t(-1) ) // error
    {
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            errno,
                            ::boost::system::system_category(),
                            "chrono::process_system_cpu_clock" ));
        }
        else
        {
            ec.assign( errno, ::boost::system::system_category() );
            return time_point();
        }
    }
    else
    {
        if ( chrono_detail::tick_factor() != -1 )
        {
            if (!::boost::chrono::is_throws(ec))
            {
                ec.clear();
            }
            return time_point(
                nanoseconds((tm.tms_stime + tm.tms_cstime)*chrono_detail::tick_factor()));
        }
        else
        {
            if (::boost::chrono::is_throws(ec))
            {
                boost::throw_exception(
                        system::system_error(
                                errno,
                                ::boost::system::system_category(),
                                "chrono::process_system_cpu_clock" ));
            }
            else
            {
                ec.assign( errno, ::boost::system::system_category() );
                return time_point();
            }
        }
    }
}
#endif

process_cpu_clock::time_point process_cpu_clock::now() BOOST_NOEXCEPT
{
    tms tm;
    clock_t c = ::times( &tm );
    if ( c == clock_t(-1) ) // error
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
    }
    else
    {
        nanoseconds::rep factor = chrono_detail::tick_factor();
        if ( factor != -1 )
        {
            time_point::rep r(
                    c*factor,
                    (tm.tms_utime + tm.tms_cutime)*factor,
                    (tm.tms_stime + tm.tms_cstime)*factor);
            return time_point(duration(r));
        }
        else
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        }
    }
    return time_point();
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
process_cpu_clock::time_point process_cpu_clock::now(
        system::error_code & ec )
{
    tms tm;
    clock_t c = ::times( &tm );
    if ( c == clock_t(-1) ) // error
    {
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            errno,
                            ::boost::system::system_category(),
                            "chrono::process_clock" ));
        }
        else
        {
            ec.assign( errno, ::boost::system::system_category() );
            return time_point();
        }
    }
    else
    {
        if ( chrono_detail::tick_factor() != -1 )
        {
            time_point::rep r(
                c*chrono_detail::tick_factor(),
                (tm.tms_utime + tm.tms_cutime)*chrono_detail::tick_factor(),
                (tm.tms_stime + tm.tms_cstime)*chrono_detail::tick_factor());
            return time_point(duration(r));
        }
        else
        {
            if (::boost::chrono::is_throws(ec))
            {
                boost::throw_exception(
                        system::system_error(
                                errno,
                                ::boost::system::system_category(),
                                "chrono::process_clock" ));
            }
            else
            {
                ec.assign( errno, ::boost::system::system_category() );
                return time_point();
            }
        }
    }

}
#endif

} }

/* process_cpu_clocks.hpp
QI0VIaMWBsRs7acnc+zbQLrJz0gaTMAgUBNBgwERhM/vds0WEgdyPWnPWno/H367X7VUJHAo3lS1pt5P7uhlpBK6Lke8M7VpxNeiO8q1kGutcm+mo7HF+q9gd/kaDN42pfQ57BvWc/xOQLswjTLN+3Khq7mWen8hOxVVC2GaQGVMM7WghXkaxi2vObAQ7KOcQOosenRkC7NsVI2z/OjGrefV9c7ETK/A/sbKrQLVVZoh6bFGHUasl75XbvbP43TMtOgPcbzxcUbCCYHqrcZ4t7Zr8Mxmo4ocLDNsqvWOGyE4OUsWGbT0Kn2nt4UOxpprdc5XYsnTx9h/YaYalyaFlqI4m5prW0vbeJ6bbLdqR+5p2sHkvG96+ctse3gcqEZRy+6NczaqdysuVHVs08zLzPFsvVDg4RENRFG3+zbdWwZe/t/+n4ybKd7zMaYKZ5vac80mnYxMuf/qayvankAVpEq6y+Yg5Uxl/oVA8kmvQGhHjidmhDJwLzvPSxIukDJLHTZH0yYUbO6mGqLdkcfTQ+rNyseBX7RRgsPHVtGA3SFyYTTt2ot8BxG5i6r9KNcJVp9MwwUrw48Ac9j+WYTCa/vHWJj+lNK1O7XXhUqSElOCaVCOF0I0eyqDnb1lc9RqBIcWgtv96nE3N2Jv7g0rM+XCwa83ATq+03iKhn42jC6G4jkN3Yv82q3wHMQjhpiK6+oeptdMImvItGRXOu66WrM41IJT+Ysr4Cia1VoKQkOIhr7ubYDIp+C3W1smod9WjKtoK+s2he+b2dAtjKCmLHih9lJ53bskXV6j5UrghO6pQguc3k0xpcQLmpqBcRK8wObXwPrcIJKWcWqcqAN4p07YgYu94eRWZXCXtcYzwR0otEUXtH9CPKXrKQM9W52bSMSCQfejU9swYTSCZ+tFU8V4EM9HFUdjPCqQKwneNBLZ3PSiLJjw1iH3EP5/fMVci6cEcsMUKqqkgMmvMLQQ9sLRzWIQKCjlw6GkahF4lycPbs9Nx85Nu0x+dge6XncZKypj3eYk8VYuh2Q9h4f4nV3f3gOyEGF8ZqR1F/VCVouhkTbpznfav+IlYNG2s4UwTUnVPvDbO/IX1BXBSeV1YzFJnPppFvVcqfq8cBizGbFLj1iZe97xBI/kCZoxt6kzBcRUYKB/UJfgeHdtX29Api1pj8hhOC9Wnsk6srol1LIvVMmbYxbPTqarvAhQCyn6IyBc6/eO6/d+kd3twW44NgvNTQA6PkX2nvsIL7z62JGapHkLWaXbrxVVHQRSg6XtDyszys6xZxhGM4ilRW0OcU8624LN4CRoHscIa42oy03MdVDbSJndwy1QLNlx6urU3ILL/FjtEr67bfGpk0k1h0kd7/X6da//Tmnc8zPdEWIs8/pLA+Y4jHZBuT3X1hZ/aXQ7MrZXYKg31v7ZCjISID+KrqECY54YLZ2Q4b9f7er1jWC63ddxpiDaMPtfuggLLkhg8P64SKo6maxbwYTxwTzg1VHQ3yFawM+FR52Sy4rjVMKs7vIktwF2t/WRMrAYnZcFPiFqZWPYijDwz2u7kyhBydAYz+8vws3cxVJaKpa8eHb04D5RWPsRblE4pDI53v4EXz5C+UQFWssHSf1+Ndi2lCqMoY0uPd4nnYbUi8WqWOwgtViQpJ3+uoYB6r5WIOs9rOwv15mz+Gk9Qp82S/xCV4O/q78A/FXh7euvAH/XS+IqALgCVAAL4AJcAiiAB3ABLAMWwP0/0XdtJTDO/4K/FpcAIt3+uRboP+bi3RItMJ9/yDdGfmg3Qw39MW4Lf3FuDxo4gmKg9LHhgyoJECgw4QOHCSCmQEBg49VTA/0i3R4dMFhvnhGEFNWHKo5Uiw4n81cqCRQcgOEBhQf9WDdFiv1oN03+sW5v9z593oL7vVQEDFsYED4IUEDOkz74d7/cmyeN4IEffPVH1h+tGuixAsMBGm/uY10UKJ/tSrpVOdT0NvoJboXhcov8g3sgAT0LRV7YBYUxFFHT2reKooI5IsgvLlTuHFtJ83T+EctQntYZRm6n3bNdNzSricNE41cbVg5D9EelVBAeg9kgTvTHwR2zHOakOv4TO6tqLnchsxW08DIe1IMSNvlrZnmSaCdbYOjIhbrtx7L2x4LNS9H4PHn0M/su3wKx/k8tN7//iZcTUF3h7R46DJHKH/TgeZvCRiEsNzSsqId27W8S9z/Vvczw4VZ/R+8wY1khCwV0UmNsLMxmZZhRNMJY0hhDMVGCbmtYSEoqMbzWTebTfWHRCMqFopFNpEqEKuqv3072b23bdjtf37dP1V/fp9+Oc2dPP359ZzzznHt3X55zZy8+cwvtWJdb02TEnzjPxUGBD3rkH1BfX9rsQE/QJLQlLir5Xjh2T8yhFxqWOb0PA27oodo5BTTnSTXhx9NrGm7xUg4BUh1zDcIstAu6tPKISSWzhIopeK5W2VEldz5OeeOEztCdWu9X7LgiQvUxgqk4GeNbhv2PaY0Lgbpc5GMwWNFDTEhQuW7yq+JgFKsqjF2guewP46vbLPI2jpKfF/fJTz8riEO+wvP5KPZE8HVcbHSx5SPo6KiYssiVyGjIxKq6akzxWjVzPJasO63M3RZNbqDl81RQUIBoEMCQyFQgBneGk4qpgeakjQ1Cuhd2hTN8qMSTQqsQ2hkaNUDqInnPnMFLRYIMMpNG1vWm8Ou48mG294zGty1RaMm5Ai1DtMHvwLxtGfp7EAd6Kpjo3Wv/GCJ7aETWFRJ4zDc7qOvDWY6GHQc6J2vxWPqva66fyrgA0FgmlBgM1jrlhv5pZAcycD7WAH2wMBOzmCpuwc/tj7Br4ILsUO2wJVv7H637eNzBgtN35heHHGapF4GGjjDWCt12ZoeyMDjvLpVhru1giRKRdmnfRFMuM/lSG1l9YHj5jPrcecX4KtXVuMbXq4+3bYG/ifDQM7BwLObGBxMCJbtfcMi0UuV38V0bXaR5lSS4SWlXX8bUXlIbblfydPqDV38VCGG+1ALgArUfQQfA/cAC4uLvL8GwGsTiBbD7bEK9v4sSChOJgNyXY+fOfR+5nAoPEZ0UV38870mYN1TcncOHflsr5z8Ycw1DGPluEX9Ma7NAnwfrERDTAydzRmSGjp/boLOH4CvGLTe/vwe2xuhZRpO+fzJBCxdW+CxOCL8DATkK+ktg3C8GNb0JBRPd6wIctTIbKjk+PdEw9gSFMdGbdeyOQltabiBVW6a7k5G4nHCKg3j8tR4YRLzDY1+dYalkDZc7l6zt2CnTr8i9utkC4VME45ScpFB1d2234XNxQSVnaLnQXmzbWML3yUeHOx6Rt3nQfOH8bN7PNbzAsdml7LQr5MTcuVMtzVjOC7FD1QBB9GUi0LNEpzlOzoouGv92lel4Rq8a/NURRlIzUuDVamc5ddcCcwVKxlCYZbu2gyz6uRN+RzmaBCvlfp/MzGfzJLdDnEw15WN3n2ZlEcvqHFs+ousr8dtbqQpK9jCRw70YcezdCbEPy5nYd88bnZ8NPXgqn0kZ0t0BG4bY2tuQDiuuMGKC5lWx6GLvpSlZcpetlXP9erbb2vhoVG1enLSC00s40DrMooo7AHsO4HjbyFS2+wfQmD37/BM5CGhh1TbgYaMh7vvRCeRYk28plT2jy5vBr7BGb7d3tQi64j+o+6fv8MTByZPeAFXgI+xHFDTqp/7R1H6VfFDsOjczNDE10CJmZLoqQYMMvSVO7VsLEZCZHa4+zwMGsxFEIJaaCl+t2eXbs4ktIc7bOj3LKke2vjxiIQ7pwFNX13Y9HNDLEiyMrPjWScwPq1HvwLJCwfFzBPy0n3z7rHNymaWJ3Q0bpzwuAypv92k8vpJhBhdoAcTCi2eZR4hfk9Y02EG8CdJbRxaW/EXntCVjkG363KpTHQeSff8sIQ14eig3be358P1YKAne9LdtKBSXNsEG3YElPLO2MsAhNeFYoKcJNEwict1BLv58wvWvVdgs0JoQOBGuJ0KaV4dlp7rWlahXIUo60cHDSqWi3ClSbQtC8wKcVFFC0vcfCdeW2HZcULxALUfIBlkjr0SH7IUKUWSWFriXWXGM/sVut1eXv8sVHI71Oqxpu8QjBQj450pC44m97DlHCxSDMtKOhmDreUPYF3pvb0Al15BWnH7l2Y3rl2l4vEMXudXrAK0c6Ydq5ZqVqSwJgcranD3Yytv5vjy+NG0M0Jre6HSaIzIUELmIVf1UmuO3VcbjeShRT5X5bh65bkw/DtLlfIvMT0Gj8Op2LOvGkA076dT9wmtyMypTmCuOCNPVhXTY+J/d1+e9OZKtTms1ABrsWzNKGuAfcmarNyJ5GRY9fMQD+yyuzzmKLG+LCk+zsDKuX425n7IaWf/hCJN5Op7q+hHsk73xNKsNTWGhaGs7Hq4HA+YwZ4a5/zf41M8MFAl93/jMmGl3cbnZPUvjo5PHxfENOJANJrIo6vp7VZctrfijLL4VhnieYSzMu62Qs+/0Mqcu1LmSQHrQnRbUrzrosAtlgTSgLlSfNaXAT3wJQOxXHB/zX6aQgRgZwTB96MA/fajAQJiZu681Dy52eAtoeqBKdNRZc4NfSSyD25V/sn/ujYTSw4bg8xrz8tmiD7OtEGyPLn0YNVtUvLgxr8jc7Ep3ke527RqgLKeJeq9scvHYtOq2+loxeJjdyM3BvoOKZnMqMauZwK6H3h8BLKqCERzlxSv0Px1FXgNlMyBoAACTp5CY4RLubnax5GID9z7GxoohPrEdtYT12686ItXF1OJWkayvdX5qZB8RQ4f4XXQtyUZ6kq6XoZxesqNTWa/lZEIf68PMuAScg7xrfPa7ifw1oAASc1FL7yk2zbBjrsOl37cWJ9uyOzI6k3LHMb3IVwezfPV0lNVn2xaNklziVt+kezCq+TmMx+6gzfrjDd4qXhn81WB7DUhqlyhtTW98tdQ/Q9LjCu5njsXYUY05W8Y4Epm/n6p0/Gebn3nmMs7+3leeFWmpW0l6WzqTKAkLIavkhCSbEJ9Zo6uGfUGxJqPbeWXRzbRHdzlwX8lCxDWc05coTRM4/HoXiTn7DNOlZpOqAO6WlpP28E/OzLg/tRwNEEg/qHA6ZzdgZWCXgxsr2STvgpnhNIEATtpdO+iar3tkxf4gxef84MUQHThIsQMFDfd/UDG37ygxRn8QYoz9wYocePGik5VGD05WDihQseOFCRisIHDlYWLDJw5VGqKJuU5U3AgcIHihSorj1cSqiRQxXVRgpVVRKmMFK4xTU/pgxRP0gYoD3gxTHLAATKWAATM4AATScAATiHAATqRAAT2aAAQlGAAoPtb2TMAA7M5+iFFEDS4Un+qFFFjRH1wosbfB9dCrssodJcpQPLOLJRW+uRHQHOCvIq+erarOB+z3x67BbnHb7QLlQPgLQumTUQlUcd2x9mW+UZqojSfmdsEooutO45tXL8sBbCNT7F9YsabHY0YvVLioouI0K4fkCbpW6nsFB01AH84pUwsx2vEZMyKYi0NHdpuNs2WE6FG4U4O256Nxv5VaVFHE1myddx4TQvEJ76JKHhIFme9PXeOUaqQsRiJNbh7sMgNbl2WqbVJRu87/zjMEMfOLe3TndRdiY8jIwMzpGQ7Iee3IVtW8yce5Lie34N2WRNbGK9MX1guSlT6EcJbQzOME2zUVNwhT0IPCwoWRmEJYnuvPNsYtdig4v5Y8c36fT6hxw3doHaKddMtm5dbGUIENt6FE1M6PypWNc86XNyK9kSJ93zjeloWDBhmRoRyIbYZyOrSdYCWnLBPM04eWK8aHoo6Ecu+q3ipfIf5eD8O0No0Xf62KL3yX+aZliTO425h056eaxGi4RpPvrp9Ieh0TfDKQOmIts0T3VmfEnNw7IqNk0NcCit0OamzdSGF1Us061Lswy30PxkHXzHDKUUN31NQ7k0un5qfqasB58JwWPYQlbkgadUt0T/DkavamdE7MNT0q4T2vlOGSb0rrzc03gX0Mipjr/Hail2sEz8pIMevFFB6ux7SRYwtORM+O9K5fdMaiQ49L8yoLSVlnaUtcvzrMS5Vg3qtwvN9S2JyeomTnDmLgsSQ+GhEFBRe+lOlMKXehN4t+jbM2RpyXIzuCyD8oX0M4SSvhuA/fxhgS9avZS5hluIb/t3z7m2S4OAjOqy02p/712Zz4A3hUBDZS/VdxuSdLytcR+H2mQtEoG4RuUyhNM31UFiYYc2Ej8yRd93VqGBL7dAQZYYrURJ4JLnGKbppNZESSb7WESp/rVZ7318/tza6z/9u2c/8Zu/8MZ/7TDL5znnPeB8/8E9fd29nTXk1qg/+CSsNROfcv+7zu9QCsDX99xYPnBOC360d4ei7w3Hh/9DWuELggrK1V33CqsTjV4I49fSUKKN6SkgbWB2MzU3QWD0IQI+16kAI28SwM7GORk03Q3YNn1nIdcFBJ+OMQXx85njZkuyvdnZEeDSoDzxvAfP2Wm+mp1EYsiqvkAQn8nufXRleuV2Y4QIDzxByAZCPg7KADvjuh/YYWNrlLJw8he33cowh7S9vw9BbBZg6Sphe7p/N66wL6BZG7lGDeHMjjLMiUd6cZhy8Xhw14oN1Fp4KmJiSABF+IMnbxfq49KWp3CxhxwQ9HXdLtWdFFHQz+BRq4XCigcNZ46ffGarSUIxLnrVcCFLIYJQu7uHiny+h7UrPMHVfAlVyey+h9RPoaI8BAmky3y9PhwfyqhE9Jcj01jjn5Ec0OOTYuQL0QvnyzT4XTL3gnH/7ik3OiRBbuRKXcqaxLlkMuqEg41YkKPGMhpoYlu27K++7o5x8uzp8UKvD/qHE9jFgIEWqUAMKJJSrY5yBBgxYVuDeAgQkNOzCwiDk9owLDCxIxHnCQpcErlRQ4YlTAAAsPOVzwoAGpiQz4wx9J/FI/9EAFMFkDB+CkAhiQJdO3wtq20ldx6n4t7zSABDimBgf40O0jj3OAgZpBGuenjKPAuI4fWfCg10WZrlRjjqDliQ4oN3u/3m17wg2gOGX5GuEz99xQJGEcEzlXkP8G4z/NTB+4qb4lp4hPzd/xnq9QMlXHvPZnaBQsDd6xsJ25E3sHY9jw+NmwS7bEaq1b4G3OfessFhtqaQ87rwubXIpGng87dTZpC7+ZuBaQACrj0t9Rr1JE3OiFw1KAeYqCq6rPrUa4Urk9h32G6DBNa4pp6/mreli9uYhgjX8sPo1fa/IzIIPP+nzvA6jNbN3hMvkL8tTKlaLo9XvQCahbpuBAS5GpLjjwiD7NCCOnhJ+BTo1o0wVWmVzIEt+cPm+Yze4YvxlbdurNcUCD3YDef9dGf8VahRQpxtf0YLuocvq2eDNrk5UyId8UUxCZDeu8LB6EcbVDUoRXBGGc4Ug0Vnamb9ez5dcsxC4/F9sxaNTBlqYJb2B1gIT0y+DBYUDHz9SxWuZzf1Yd/YonvaOtXpUP/TGJM5JfE6PQ8uUELGsJLEtC/wXx7Z7Db0vEOOysbx9z2fyNibv/Fykbj0SLfAJfQaG7tyoCVYBBpqy6FHaNQhHOVKgIPXTrBk3d93ZzS3bL4gJ17LRh2rZHf2GXP0AZKyEqZyztXxzG/FDQA9aJyGunqL3HjBihyHfdlk0VSi43xoGzvjDkSUzayjMxMTDVXBbf1EDSUR/vVOCr63DwwgvH5+ndt/loy7UmO/pzJJJtSlrjNa1tdDzx4RNXDj99/DfRvCBOOu25C1/uwRulHZepjqpKFp7fkDZvMD1A2v+zUDrhRkbz3SgEhsn1rdORGj1ks4mIhi3gJLldbEp8cyS0N8gaeeyZ6PUnNx4wdlox0zjwCUyU+Kw7ZvPSCccWTb1/PpBWdX2/cLjqUm/1dUmFU9U9eUCaKCdFzQI3gcYphMuS2Kxh1Wqt0Cx/hQ3Lm+OYuuxfJK6lo9ckWX8NznXaFZMKMUg9VvdNNdl8lyMkNaFWNh2C7+j591WGhQUtqAkxJaSAFtSEkBJaQANiSkjxX0jN5Glr4rTf+y4N9lqgTZ8oW4CNjS3OHjUFfmiwP9pGGh0Ac9Pjpy/wVQG9SwY8+vVzxOH3leGutnuqVzG5NSnkYJR3GXDxW6rp7hKZf70RyD/4VdqcV4nSCxOvoNPsSb19p7sstxt/lelL8pJsm+lZDGDAgErcVd+AnJLb3chRT5mzm6I2ELLJe0mRyMDq+LeFNTAPO4VEA5sTdZaivJ8p7mKIl0w7SRq4QNyFWmXpGZbKI4/bS3Y1xQqTUz7zcGR7c/nfRGSlBeshCN+nk/Ap2c1kbj7eKXO3tznqzBXu9Ek6AoxRz9qJD5Hq2pGiV1QxdS47/2SnvjNkuX8nyYbeFNKuK7kVFQvqaZwNiQqHORfEi42au88h3tZC9pL5WIRNb72M1ugRLRSN7dnrQFtKtYzdzuXQczTVtG1oX0f6x8kZXsmNwnKiaZQPnNXjBQqChQjED+BO61OY1iIvoGsnxnhQ102i0g9n9Luili/mKykHE8cPDUn+GYgsk+vip3PIUhyz84qMFnca6vp39w9KkMCfs1+UgPWAgoYsCEzg2KAiVhYHCFqMuLVBIwQPGpC4Ed+dEtA4QaMFxLdzEUroD846yBG/vRIQoYADBJDG092DsttE+TwFQIciOsA2y8eKPHff5wUAwIQ7PsAxPzgAVEH/WTkEBNTk4xL/Rfm5fPoY/rvltx584/z0egAwXnWYpKhNfAHZqKlnvhv7xAl9MA82x3h5sfIIApB2Oi1P8CQ9HSbYDe7maZqD89/4xYoNZ5krrmH1YwlMxHrXs9RKJe3tQuvqiiy+Ax5B/gbtzi81s7aEjWm4cR0EG5dm5GGzS8YwDGadDP1PHAH34UlA2s0ouPxYWc9eNg6+Fh/O8TlGwak9oT9lhe1rj6BiYH6f8EIBSnq/lm5qkaXPbMLvYu2hHBXRjqPZKeemg3C0235oZSi0vFDrSB6BlMiSadk2S4yLkN7cO2oAGOaPlTqeklKbFx1qVJEW227ulowDEfeNcpUM+E6vz+zA+IRMyG6xr+lajovkfi1HtO+EjfVoxS0y/cvjuttbF+KzM+Tg7wZTH8nX2polEKAWkOO2Wx8guTv/DIxfF+NMI8nXM8WSZXhtO522wbrmk0Ho5zTt85o9E9lnZhMo7FMe7PD82uaXzx7tXH0MrxGUJulx9swZdLqeSzmsTp+VfB9WJt8Er2/Vqvg=
*/