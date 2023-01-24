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
lEXPIKMr7GHSecZ0YJvSs6j9Ag/ljn9qFNfd6FMCaH4WgdRMlvceUJFdIR+nejLF7AtZKXhsz/Etz9G96LMQneJVAvw7S/tEd9UNLIpB7KKJWAq1VX2JF/MY90n6MjAxKtMxEw4lYuiFhqz91N12jnwO8eN2A0YgyJH7r9tP7Qhwbgba2d2WDHlrUrt2TpC/Jki6sUHKGYgQ6tPcoz7NvVAWpKvcdg0DNU2lO5N2r1qK6wYg9/M2ai26Gm9bE1LKzyKS9ZxoPNkCcSW7Md095rGns7H6/gyLt8mMLil0PHpEAx1JeN/UG0CGpNYBIP9U1gYgq7qrAWSBPOIx5+sDkIleAJLqBSAekwpAkvgihJFICiPR9cDIhvpgZGyp96J9s9V70Y7vU8FI65H/BUZ+2+fd3HCf5h4jeSq3BAQjBYUaGNEeLBOQuD+UgsY97Dk6VPZ34A8+Rv6ggQ+7X/joOKIO+PjhVG3wMb+bf/iIPftf4eMxgwo+7Aw+om8QfPTb671gr27xXrDNJSr4uMj9F/jYWeLdXDef5uwlAcPHG9/VDR93hFC4uJ09+4bUCR89DgYAH9eG1wEfX/9WG3xM6eofPlqc+a/wAUykD3zE3CD4aLnHe8Ge+tZ7wd7arYKPI8n/BT4+2O3dXIhPcz13Bwwfz2yuGz5uMlG4aMuezU1yPGeJ72r9vcx3xaTye8CuwA1cr6sz6eABpwXG
*/