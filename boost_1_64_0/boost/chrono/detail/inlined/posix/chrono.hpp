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
/RYh/F/bq/MryYg22QqHRpvbPIybwI8JFWtewELINAfJaERhzcMAhzoEOai7NyZ93Eai4M0QwM7PsP01/cz1uiRDn57PMmUqY/TF+kCWKmRM1zdakHnO9Q7EUN9f01EDJZV5A0HqqGLamQGgc20WnsP4qFTrQqMUqQsIwcmRz/dW2AT9e4tc/Gs6qgXe/wAYGlvQkWs+WK1rDq/HuS2eBPLLeql3JR1EUaQdVJF1y60TIL7ZrTJPEEnVDJKPUCUNrBKJv9xrI5ysUnB0qjDG2gT/NAEOFRYf5DRSFwfKQe0AS0xd84xDn2XpUI21Ho1KV8kw8+cnOc7J4uSvdg7qz1kMsIVqLRjVMzrYdn/tCOOfhZUrx56y9cIOuL/o6uPTv/WmKI1AznSFzIldbWKf+pUPkIV8/YLMQ8D3L4iqGHbzVXmf/8h5r+v53eaJIky8iGYRazHJsT41sZ/JnL/lYEvyMr3qsIHbgG7mYia6YEFRtAKs0emgRvbRQ4MXYO1cfjK+zUm5Detu0truGvEE7tIKSzroo0ilDsvoBZynSO8/U4/rJJztHFfpQA==
*/