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
1GQeBhPoTwK/BhuC31BLeYxrxn0LDgO/U17aUx6/g7+Wh9rOaM7ZeQH4JY+7j1rN/dRCIZxzEvIbIJhtMSdheYcrf8lgbWr+6oOVwXRq/bqA1cC+YBVwAFgVHMhwalzx/c5e4/pPlsv31Lj+4LlefG87fxrXDNOx/JIsNEMnDdfxfgNDwXCHKz9lQfkeCUYxvDzDeVx+X8KxLI5r4HjxYCi1m2XAWmA4524tS41YBDVSUQbrx8FvLPyWZB63h1k//P57KbVWA6i1Gkgt6BCu8Xc1OJnaqmnUVk03j0vNVTa1nyPABdTmPQuOA5dQo/cqOB58A5wAbgYnUpOWB35O7d4RMB/ENakpYDQ4DYwHrwMrgNPBSuDtYDXwHrAueC/YAJwJpoFzwJ7gXHAUOA+8BnwUvAOcD84GHwOfAxdwzcrHwffAheDH4FPgAfBp8Dj4DHgSXAT+DkIPKlrP58By4PNgIrgUrAi+BFYFX+Zal6+Y+QSXm/kEV3Dty5Vc+/I1sCP4OtgVXG1eB/gG2AdcA14OrgWvAN8EB4PruWbmW2Am+A6YDRaBOeAH4ATwQ/AGcJtZDuB2rq25A3wR/AhcB+7m2plfce3MY+Cn4HfgHvAEuBf8ke1squJ3DvAGtt8oUD5Ucm7heGoEK4AJYEWwKrWCSdRwVgAHgclgFlgRHAVWoia5MrWOVcBrmV5r+Xj+URb3z8/sL09yrth/UYv6b86V+gv7Ofil/f/HS+up1tlrPaMcrv4iBmwDxoPtwVje17MV3zHBJ5g+BryN6asj/6lgDWo+a4MNqZVsAl4AynMN1+RsCHYCG4E9wMa8Xy8Ex4Fp4ERqRa+jVvROsAV4N9iS5ZXu4HsZ3/1EB+3SWMvWnXPJ9lbUXoKZ4OXgNZzz9lrOeTsdzOQcxNeAj4D5nIt4JOcizgWfAidwDuJp4DbOOVvMNVD3cU7Zrzin7DecSxZ1ru6iZn82eAH4ANcangM2BR8CO4IPg0PAeWAO+Cg4BpwPTgUXgveDi8CHwWfBBeBzZv5A5E3Wtn0VXAa+Bq4E3wLfALeA68Gt4CeGq1wOg/3AMg753RMN6JVgE7AAvAycDA4AbwCngDeC14N3gwvBe8CN4H3gIfB+8GvwBbCc0zVXczNwGdgPfBkcCD4G5oALwHHg42A++AR4LfgkOA1cBd4Bvg4uAleD74JrwaPgm2Z5g+vAb8GN4Pfgx+BJ8BMwJMQ1FiMM3K20lpfvF+iDLbS8bcz+jxrk2mAH/s505O9WOjXbXcF21CD3BbuBV4OXsB/ozt+jHuA0aoSvB3uDKdTcrn8fGky4krS3p7Cf2tu/xRzDKVsi/hStbdqWiFLrbc9Wa9sd5xgNdxfcYrgNcMVwamuESoVrDZcBNxpuBtw8uBVbgxrb4BbcgltwC27BLbgFt+AW3IJbcAtu/5/bn6T/B035/7nN/e9e/3/fs976fxya2v+5XvP+F1BrUQMumvqihyvj2/cKt65bpLHmNI6iMcJ/10zOmWSr8e1puNNW1tq63Ngz1kXJ8RwqTOczxWGdzxMW+RSdQOaoyVn5WRMKcnJs83niD8jnBuazHvNZizq/1JW++cRUcP4lapdPpD1/+WzpLk9qun+Ao01SHTC1Sit9xiogYWZe1ph8HA95q8C8Ncn01uoxTX3x94f/HvEXSZqaykwjNYJFk5tInF46TQetdXpC/HN8z9PUc54MnaadXqf7MfH/w+I8TSXOZTpNa4/OSPyrUJZaB63ncdvFPKXiXkuiLuMkz5mgIlUdVc5S35EMJrxqxnPQb6gG4o/Sdarkejw6+IeYd5/9TTzzwz0n++dzDkUZyyEu18uNL+XYjiT3nG+i72c=
*/