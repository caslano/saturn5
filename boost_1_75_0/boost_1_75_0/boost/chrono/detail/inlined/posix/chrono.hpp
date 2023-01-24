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
873/8ey5iY6n9/WNx6wdz+kJqvFc0PuOZ6K8PnfI4/lB34DxbAun4zm33/94nouk40ENTeDjuVuvGU979XiG+xnPVGk8zel46EWiqIaMqLgrLaT21yefYrjGSCrYNP+nGEgxPLvpKUau5hQD/bF8ZpEEkfctVDTYGy7Hv7DIdjfPW5A73hCOD1NzmvWdcDnDdJphOc1wshmLl6hkSKIZHqcZtrMMU5QMUTSDnWZ4t1ktceDe+alOPvyZ0bUdgSx4Nk3nTEHzNuqYB7IPGx0It2Avls5AvJ3uzGwqTda0prX70/zzuLl2W+Diu7xsgeOmECprJz2MnzLW0ZsCQVWYTrn4z08YSyQi/zATPyVdKpOnLZNeR5mJUhmXtszEOspMlcrcqS0ztdYyu4an6eM6tEwK1TmsXHwHkYidBAs8YdfIi5CUDXrRsD8SQyVb5g4/w7vWlvmltEC455W7fG2Z6XptaeLl44ms05wI2V9F4jG1AHGJ48/5RGtvk+Z7KAQbo3ME3J+/E+BrbGA3iC/uVEFVOrAWU6nfCdbXFk0k2AqV38TGvvebl//oBV3aK84Zd/p2mICYs39gvbxrp/b8D7uW1Vgd63hyv+vUHxjV+gN79m5nMLKI27mLP7YrdFUYTTq9cQHGSvH6gOPWnGUsPL2aKrPdR2Vldi5qqM/RiUiHiUhHO/hRdCLSlYlIJ92mljutTteIeOktg/LI
*/