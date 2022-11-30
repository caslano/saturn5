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
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
*/