//  boost/chrono/thread_clock.hpp  -----------------------------------------------------------//

//  Copyright 2009-2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/system for documentation.

#include <boost/chrono/config.hpp>

#ifndef BOOST_CHRONO_THREAD_CLOCK_HPP
#define BOOST_CHRONO_THREAD_CLOCK_HPP

#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)

#include <boost/chrono/config.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/time_point.hpp>
#include <boost/chrono/detail/system.hpp>
#include <boost/chrono/clock_string.hpp>

#ifndef BOOST_CHRONO_HEADER_ONLY
#include <boost/config/abi_prefix.hpp> // must be the last #include
#endif

namespace boost { namespace chrono {

class BOOST_CHRONO_DECL thread_clock {
public:
    typedef nanoseconds                          duration;
    typedef duration::rep                        rep;
    typedef duration::period                     period;
    typedef chrono::time_point<thread_clock>    time_point;
    BOOST_STATIC_CONSTEXPR bool is_steady =             BOOST_CHRONO_THREAD_CLOCK_IS_STEADY;

    static BOOST_CHRONO_INLINE time_point now( ) BOOST_NOEXCEPT;
#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
    static BOOST_CHRONO_INLINE time_point now( system::error_code & ec );
#endif
};

template <class CharT>
struct clock_string<thread_clock, CharT>
{
  static std::basic_string<CharT> name()
  {
    static const CharT u[] =
    { 't', 'h', 'r', 'e', 'a', 'd', '_',
      'c', 'l','o', 'c', 'k'};
    static const std::basic_string<CharT> str(u, u + sizeof(u)/sizeof(u[0]));
    return str;
  }
  static std::basic_string<CharT> since()
  {
    const CharT u[] =
    { ' ', 's', 'i', 'n', 'c', 'e', ' ', 't', 'h', 'r', 'e', 'a', 'd', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p'};
    const std::basic_string<CharT> str(u, u + sizeof(u)/sizeof(u[0]));
    return str;
  }
};

} // namespace chrono
} // namespace boost


#ifndef BOOST_CHRONO_HEADER_ONLY
#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#else
#include <boost/chrono/detail/inlined/thread_clock.hpp>
#endif

#endif

#endif  // BOOST_CHRONO_THREAD_CLOCK_HPP

/* thread_clock.hpp
+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
*/