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