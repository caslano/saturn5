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
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
*/