//  boost/chrono/system_clocks.hpp  --------------------------------------------------------------//

//  Copyright 2008 Howard Hinnant
//  Copyright 2008 Beman Dawes
//  Copyright 2009-2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

/*

This code was derived by Beman Dawes from Howard Hinnant's time2_demo prototype.
Many thanks to Howard for making his code available under the Boost license.
The original code was modified to conform to Boost conventions and to section
20.9 Time utilities [time] of the C++ committee's working paper N2798.
See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2798.pdf.

time2_demo contained this comment:

    Much thanks to Andrei Alexandrescu,
                   Walter Brown,
                   Peter Dimov,
                   Jeff Garland,
                   Terry Golubiewski,
                   Daniel Krugler,
                   Anthony Williams.
*/

/*

TODO:

  * Fully implement error handling, with test cases.
  * Consider issues raised by Michael Marcin:

    > In the past I've seen QueryPerformanceCounter give incorrect results,
    > especially with SpeedStep processors on laptops. This was many years ago and
    > might have been fixed by service packs and drivers.
    >
    > Typically you check the results of QPC against GetTickCount to see if the
    > results are reasonable.
    > http://support.microsoft.com/kb/274323
    >
    > I've also heard of problems with QueryPerformanceCounter in multi-processor
    > systems.
    >
    > I know some people SetThreadAffinityMask to 1 for the current thread call
    > their QueryPerformance* functions then restore SetThreadAffinityMask. This
    > seems horrible to me because it forces your program to jump to another
    > physical processor if it isn't already on cpu0 but they claim it worked well
    > in practice because they called the timing functions infrequently.
    >
    > In the past I have chosen to use timeGetTime with timeBeginPeriod(1) for
    > high resolution timers to avoid these issues.

*/

#ifndef BOOST_CHRONO_SYSTEM_CLOCKS_HPP
#define BOOST_CHRONO_SYSTEM_CLOCKS_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/time_point.hpp>
#include <boost/chrono/detail/system.hpp>
#include <boost/chrono/clock_string.hpp>

#include <ctime>

# if defined( BOOST_CHRONO_POSIX_API )
#   if ! defined(CLOCK_REALTIME) && ! defined (__hpux__)
#     error <time.h> does not supply CLOCK_REALTIME
#   endif
# endif

#ifdef BOOST_CHRONO_WINDOWS_API
// The system_clock tick is 100 nanoseconds
# define BOOST_SYSTEM_CLOCK_DURATION boost::chrono::duration<boost::int_least64_t, ratio<BOOST_RATIO_INTMAX_C(1), BOOST_RATIO_INTMAX_C(10000000)> >
#else
# define BOOST_SYSTEM_CLOCK_DURATION boost::chrono::nanoseconds
#endif

// this must occur after all of the includes and before any code appears:
#ifndef BOOST_CHRONO_HEADER_ONLY
#include <boost/config/abi_prefix.hpp> // must be the last #include
#endif


//----------------------------------------------------------------------------//
//                                                                            //
//                        20.9 Time utilities [time]                          //
//                                 synopsis                                   //
//                                                                            //
//----------------------------------------------------------------------------//

namespace boost {
namespace chrono {

  // Clocks
  class system_clock;
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
  class steady_clock;
#endif

#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
  typedef steady_clock high_resolution_clock;  // as permitted by [time.clock.hires]
#else
  typedef system_clock high_resolution_clock;  // as permitted by [time.clock.hires]
#endif

//----------------------------------------------------------------------------//
//                                                                            //
//      20.9.5 Clocks [time.clock]                                            //
//                                                                            //
//----------------------------------------------------------------------------//

// If you're porting, clocks are the system-specific (non-portable) part.
// You'll need to know how to get the current time and implement that under now().
// You'll need to know what units (tick period) and representation makes the most
// sense for your clock and set those accordingly.
// If you know how to map this clock to time_t (perhaps your clock is std::time, which
// makes that trivial), then you can fill out system_clock's to_time_t() and from_time_t().

//----------------------------------------------------------------------------//
//      20.9.5.1 Class system_clock [time.clock.system]                       //
//----------------------------------------------------------------------------//

  class BOOST_CHRONO_DECL system_clock
  {
  public:
      typedef BOOST_SYSTEM_CLOCK_DURATION          duration;
      typedef duration::rep                        rep;
      typedef duration::period                     period;
      typedef chrono::time_point<system_clock>     time_point;
      BOOST_STATIC_CONSTEXPR bool is_steady =             false;

      static BOOST_CHRONO_INLINE time_point  now() BOOST_NOEXCEPT;
#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
      static BOOST_CHRONO_INLINE time_point  now(system::error_code & ec);
#endif

      static BOOST_CHRONO_INLINE std::time_t to_time_t(const time_point& t) BOOST_NOEXCEPT;
      static BOOST_CHRONO_INLINE time_point  from_time_t(std::time_t t) BOOST_NOEXCEPT;
  };

//----------------------------------------------------------------------------//
//      20.9.5.2 Class steady_clock [time.clock.steady]                 //
//----------------------------------------------------------------------------//

// As permitted  by [time.clock.steady]
// The class steady_clock is conditionally supported.

#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
  class BOOST_CHRONO_DECL steady_clock
  {
  public:
      typedef nanoseconds                          duration;
      typedef duration::rep                        rep;
      typedef duration::period                     period;
      typedef chrono::time_point<steady_clock>  time_point;
      BOOST_STATIC_CONSTEXPR bool is_steady =             true;

      static BOOST_CHRONO_INLINE time_point  now() BOOST_NOEXCEPT;
#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
      static BOOST_CHRONO_INLINE time_point  now(system::error_code & ec);
#endif
  };
#endif
//----------------------------------------------------------------------------//
//      20.9.5.3 Class high_resolution_clock [time.clock.hires]               //
//----------------------------------------------------------------------------//

//  As permitted, steady_clock or system_clock is a typedef for high_resolution_clock.
//  See synopsis.


  template<class CharT>
  struct clock_string<system_clock, CharT>
  {
    static std::basic_string<CharT> name()
    {
      static const CharT u[] =
      { 's', 'y', 's', 't', 'e', 'm', '_', 'c', 'l', 'o', 'c', 'k' };
      static const std::basic_string<CharT> str(u, u + sizeof(u)
          / sizeof(u[0]));
      return str;
    }
    static std::basic_string<CharT> since()
    {
      static const CharT
          u[] =
              { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'J', 'a', 'n', ' ', '1', ',', ' ', '1', '9', '7', '0' };
      static const std::basic_string<CharT> str(u, u + sizeof(u)
          / sizeof(u[0]));
      return str;
    }
  };

#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY

  template<class CharT>
  struct clock_string<steady_clock, CharT>
  {
    static std::basic_string<CharT> name()
    {
      static const CharT
          u[] =
              { 's', 't', 'e', 'a', 'd', 'y', '_', 'c', 'l', 'o', 'c', 'k' };
      static const std::basic_string<CharT> str(u, u + sizeof(u)
          / sizeof(u[0]));
      return str;
    }
    static std::basic_string<CharT> since()
    {
      const CharT u[] =
      { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'b', 'o', 'o', 't' };
      const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
      return str;
    }
  };

#endif

} // namespace chrono
} // namespace boost

#ifndef BOOST_CHRONO_HEADER_ONLY
// the suffix header occurs after all of our code:
#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#else
#include <boost/chrono/detail/inlined/chrono.hpp>
#endif

#endif // BOOST_CHRONO_SYSTEM_CLOCKS_HPP

/* system_clocks.hpp
cuVwJoiLnUPUGoxgLXQduaw8+j281TlUdMa4frEqMHdUX1i7qGmRrdQZx8WKnhPmHUn9MT/hZ/FmHD/HRP+kC+lIc59Y9jVcRjr+xp0pcsSf8Ua+l1SOmKStlVnmPPTdB+T71jwxy3aPzI4sENL+qPzCkSOWRq2Sxc4CERPzqPzZlef7LafymtPzcbXkeQbRppM+lxLNzT6bFQMDxm+iPUbtYCGah2mPDKyizWW7dgB05vZVNGfYJv4C74xDzpCLVFOxRT2JZ6+pWKnNlh5zU9HdvF2cNDcWDSxT8FvWXLxofVrMs6WLh2zTZWpkY5EZ+bQw2xuL1vbZ8hFHU/Ge41GxIKoZxqWJKiGmhegTM0fudjUVpDvffzT9httEkq470+6lPnF5XEu8DTtWJni8PD7peZVUr19j7rUQgOeV6fOpnFixkOvWBbCY6nYQdUtDrV4S3+LfBFkib1Jp4jG1R0xH3R7QSlG3VNHZvEdIS1PR0lIk77Gmieetr4jFqNtvbSWoW5roE/mScNibik72ctStgXjD8aJYEdVUPB01V17ibCCucb4k0vF8Do4px9ib5qsj6VGf+orL1z5EO0w0j28cItoVVLceRCtiWgL1gQjh5fK66eWRfeZ7rWKatx33SZ1+Jcl39I4UDU2VpuvUacuNamHEXOVwzFErouerJNf1al3sTarqmaeJK68Nsnm9h5mZQXuWaCWgOQzaLEn9k37VfLRVrK8U9Qza/Rjz+rg6TZkvm+l9j2itkjT1nreKLmUrg7de0jaxn+k9ZYbeB4jeLGm+bBBfRX9BZvnxX6IGe92gXylfAJXXO1i1EY3qEEybjx4WTOtJ9QqiaTE1ZTVPTZpKqHlfVa9meSq1Bu0Fle5H0/dMKpGuXk8ViU5+669iqnNUYooYYZpjuky+bm5k+jFiqlgWeUwtikrQHojZrcpjrWpJXImmt8NqlssluXJfWWSTp4m2GHO/ddoubYjWyPqBsNlmaLfYM7U/Rt8mpjpPq7nuO7Q4b6lkObLb5yT3nNclftYamubLLeZP1Grbl/KmyC/kXMc9phTXo+rt2MfksrgUnxzZ1kpjlSMhViww3Wd6UuZYmkr8ppkiHMPk9CiP9lDMejnMnate8vTQWI761UUkt9ObIK5R09Vc04+W7+R3tplyZuTHanTUFWqLs4tmjv1AHYp7waifB7CY5I6gb3yoHdE+Fu+YlmtFtsby3ojPtDVRr4n50Uu1GPcr2p/ivhNt/OZfD5DcKm+sWKP2KJv2tbmFqmf7XDnsx0SE413tS+edFnp2mX82jTV3C7ff7/q3VEYLLz0z/Htqo+d0VxzpyL+P9Yj2vDceb27dIZuYPjWPFMMsY9Xztk9MD0d9Jx90bpVlrrfliNgJmtvvd+gakmtFv0Eu/n0oIZrDtyYkmpvGvJ9i6Z487v+mc1X9POKkTFCZcrKmabMs47STEW+IP0WOVN2i4rWrY5ppC2KPq05+vw2vkdxs2KWfzJbrVH3TSZlsGWIqj1wsbY535NdRj8mHnc1NH8XeXzWm8JjViMa2LmSLYh6bTlJZS6E/PedKr1N7or0HPhorSP8T1Nf2+2g0HjxBtm2AfktjgdLHglkk6xsHpOwQ4vnuUpMmu9V8HkWPms+y1jvE2JAZYqwZ6EdLEkNpL3vqcrS9JWAvm9poLT+bbxD/9Un6/taBc+xf7vTbv4yRvr2uobSvlYC0ifa6jH0k2gNLlb79LtonItlK4DUkOzVg7+sZ3vvqwnFv7QArwJc6ImDvS48R05vCf+/L2IPsQrwNeO/TJ5twlv271P419++Gkl4Xs177EgVdY3g/PwtwD/hKa+qVXZpTllMURrdbib8=
*/