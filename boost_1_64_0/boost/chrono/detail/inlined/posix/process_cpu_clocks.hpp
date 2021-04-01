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
msy4DSAemTIk+2Ins8QUa1H0s8bbJ1O3okV5SIOsIj5jW+Xc1vbG184PwW9c+e96qfV7FqO23IecKTrgIdZr0P53hnVYq6sQ0mgH57GNRiPqpBu6RVsUbab4iqZmZziD+wy4b6G2a88Pw5cKzsteSg7UE/yeUc+hoCqGVXcTufvXBXI+TtIlxmLvVNbmdEYYYftvLO1UECnEdVNlRXPms+EV53NjId32leOukxA09SGxrtY+7Falld4wGFl30H/UtZiGDhq63CoaEkdv2vlReh0Go7T3Xi5N62UGPWtALK6xU+XsoAjKnYQr0XSR76KmFmejDLmB/oD1h8cu1W9F5RY26j3CbbdRLdISacMvFXy0jmH4oGShNWvxpOeAmgtFuoOZF6EpzvF0S0fmn7orp3Rqq4qKgxbU9mB2AuWPWhG0KAf/Zy2iTo2OdvYR8Ez9ZG5uPnLgeT6l+dufTwnxWZ3lvRatyB7lg2cpjCRJU+ssQ3DsQVagVaPpZiSHFwXm55LF0svC3PzdXWClZza9gERht45mNauSgUFRIWAbfMQWg6qBcfG6uCcjHA==
*/