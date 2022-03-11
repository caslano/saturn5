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