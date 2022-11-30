//  posix/chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright Vicente J. Botet Escriba 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//----------------------------------------------------------------------------//
//                                POSIX                                     //
//----------------------------------------------------------------------------//

#include <time.h>  // for clock_gettime
#include <boost/assert.hpp>
#include <boost/predef/os.h>

namespace boost
{
namespace chrono
{

  system_clock::time_point system_clock::now() BOOST_NOEXCEPT
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_REALTIME, &ts ) )
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
    }

    return time_point(duration(
      static_cast<system_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
  system_clock::time_point system_clock::now(system::error_code & ec)
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_REALTIME, &ts ) )
    {
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            errno,
                            ::boost::system::system_category(),
                            "chrono::system_clock" ));
        }
        else
        {
            ec.assign( errno, ::boost::system::system_category() );
            return time_point();
        }
    }

    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return time_point(duration(
      static_cast<system_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }
#endif

  std::time_t system_clock::to_time_t(const system_clock::time_point& t) BOOST_NOEXCEPT
  {
      return static_cast<std::time_t>( t.time_since_epoch().count() / 1000000000 );
  }

  system_clock::time_point system_clock::from_time_t(std::time_t t) BOOST_NOEXCEPT
  {
      return time_point(duration(static_cast<system_clock::rep>(t) * 1000000000));
  }

#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY

  steady_clock::time_point steady_clock::now() BOOST_NOEXCEPT
  {
    timespec ts;
#if BOOST_OS_CYGWIN
    // lack of thread safety in high resolution timer initialization
    // can lead to a timespec of zero without an error; was reported
    // to the cygwin mailing list and can be removed once fixed
    do
    {
#endif
      if ( ::clock_gettime( CLOCK_MONOTONIC, &ts ) )
      {
        BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      }
#if BOOST_OS_CYGWIN
    } while (ts.tv_sec == 0 && ts.tv_nsec == 0);
#endif
    return time_point(duration(
      static_cast<steady_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
  steady_clock::time_point steady_clock::now(system::error_code & ec)
  {
    timespec ts;
#if BOOST_OS_CYGWIN
    // lack of thread safety in high resolution timer initialization
    // can lead to a timespec of zero without an error; was reported
    // to the cygwin mailing list and can be removed once fixed
    do
    {
#endif
      if ( ::clock_gettime( CLOCK_MONOTONIC, &ts ) )
      {
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            errno,
                            ::boost::system::system_category(),
                            "chrono::steady_clock" ));
        }
        else
        {
            ec.assign( errno, ::boost::system::system_category() );
            return time_point();
        }
      }
#if BOOST_OS_CYGWIN
    } while (ts.tv_sec == 0 && ts.tv_nsec == 0);
#endif

    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return time_point(duration(
      static_cast<steady_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }
#endif
#endif

}  // namespace chrono
}  // namespace boost



/* chrono.hpp
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
*/