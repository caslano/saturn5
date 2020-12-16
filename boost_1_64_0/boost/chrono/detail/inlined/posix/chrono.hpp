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
IwS2qxBqT0y3MfHMdCg4r1uHovOfzG9wHbz0DT8h3onA/ItioxzzTzue1hjEbxLNrpf24vRz+3nn40fmI5vlOBBuD86TvslHl8+KsNWDM36S1jQOEH9v1aoEbX2OxGkNe2qYz3p5uXDjS1G+tIf7ax70tWXYzLW33nNtuompM9TQn3Jaa+i3bSq9hh5xS9TQ79h0bhr6tszrCer9k5iqPNwdFVA+rrZmlkBmdlZu7vCs7HEl6HgZP8pOs8v9SbL/Nhzf4NpztFu69592rqdycj2+9t5YC01fMojzIAzn8bvmwlAlW1dqoTpQ26A2e12zjL4wdX45Bf6aqIle89jES5omLAfzGGeur/bT7OD41JXLsaCh8tPepXEdQ3xeVDXJBdgzbJ3Of0nrGDJeU30/zhH/4863HGXt6o9pGgZorpuKpoD7kZNctKCHVBnYZcJhE2mM74Xd1FNGTfWxkYZv3llqr6OaSpI0htr7lpnmJhWHuPVUKzttNo99odZmzxL/Qud7Dqeltq4CeI/EedbZwBGq/oFzlpNwQ7V/m+2UfabWW7M+75R0i51vOCqpJD3f3OiJGHY1KSd/ypjsHM+8c0+ul36Mfh4bV9NXDZY8LS/v+j1YAb4DbuBvw17SdCtQbx/AvxMOcc3+TVxSeRdviT99X+fWL8+V83v8Q+B365nbva01yc21btcTprXGG98K1CmvQ5i/Tnm1J0zrdh9FmL9OebYnTOuopyHMf73Dm9Zr3a4+3ql1gfre/TqslfjXaH9L8bd/+4+ZY9JnzAM/yd3A/uNa97x2G/T9V+KafG9LvLHe2lemjfdvl1oTVCz7e4k2tnlZ2C/hzPblbBzZAzMONobesEx4CdrYZaUYk2Y1R+WPG3z7oMYsg9RIJdsoPhsMYRmkecqgpDXfGK8hrw/pxd/Wpf1F+R6Bewl5jipTLTLanE4xspZ5iWFezzL+zz16HdOxcqwa6IUcZ7OuWYDeNM9m/kDl6W/t1pXj9TKuvd4U++31pm3WefSmtVDuyVFnrjdNWFey3jR2XaDedNUfpDdN5pihJ+CqwN3NOQTT3tTlabnmG8sS8fzajvivsdObMn6q1qpliH+qpd40Cf5Bsn8sy8advp6trvRy2Z8beO/y/ANkf6yeXzVX/MPRljro94cVXIdWlT+3+epKM5/gpDd9dW930H/K7zmjfxz18MhgdfIk4gzzek6aVJBVkGNdT4jnq/OdK/5ip+d9K5tl5I7bWNfR/eI/7LQq8zhw+PvmfoceU3WvxN/j/AwlWgHPG7ucDsbFk6bErcT6cvtDve61MXrcb/S7oj111FWLjBoSZqhCOfYHzkxYM5fgneRqo64Kc8xV9ZwFUuff4VrCVfZwJNeazHmS5pDTHMs5ge+jd0lYrPJasz1r/JjcaYrPLWMMlK/EaSL1EAF3HdpHFez/DBe5Ge49Pkc42V7M54pY/K3gNuFvA8xHPZT1Xesdjn6Lv5ubac5hveMZ73ueM/q8r3/b9TOF810dpp8B5hTp32kdr5cnTD8/FG8OHAu0DmH+zwUjeV5zZuAk+C93+6eOKcjMnTgxj/dMhueeEf9A/Q6eLfdCXVdeFepU/Hvgp+ZT/D3f8/Vnvq/j+47dTFCy3QuXDHc9NcEz1up7x2qdRP1e8azEu4r3kjtdbTtNMPb7ztf5mPjHWmqCzfw8Ifvbso9zp6/K/Yb6Vfwxyu7+e1n2h+jj7RZ/TWqIMaJY/ANxX6T7H9O2n3xa9kfT7z5G+HnvI0szp+fKtb59ZBH9v1cO6lnPh561r+hZQ5M6Vmix6LJac354qeJTHds1+HvqWa3m8HyJutXP5T2S+iY4aqvwPZLaUAtt1Vc=
*/