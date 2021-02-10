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
KI6tzytfD13cUAU1P4BpPHgDrcMMgl8GtRGyDCNJQbBpcyVdlZ1KoURaLIwFh0pRKJom0fUlI6wHZbLgBQ1VK30YnNEuZNpVph45koQUpGytpjQkAfkIQwJn0GqBtvPtmj5mGNTspH1iSU61CjCaKoEXyzVcrl9Azp10Gfy8vP589e81/Fz++LFcXd/A1d+wXN1QrC+Xq0+03pIyWcB9Y9FRZguybpRE0SX8fc+MMq4rqlpAjn6HqOEbv8OuNV53El4E8JUacnO/97NZzTX7tlyt4QPcziAsNEPuDqxQyHXbzN+OsWibisJQvMhAO5U3Cd2gl7o0MZZa+pjR1qFdyXKyiqdtmtdJksGqcZ8EbThtxQSiLY2tY0ynZpsyh0lQhzqpkNyojIR6i9YaG/NWT8vVNneII81jt1A4FyIipcXYaTOqO3Igo+A+Iqgft79RJudqYhsMhmgJH1FWY51anFNjKWtZI6NWwgUVYyqOTzFW5DFGXRg61zEOW34qSuDRHur5WKCOVcgpsotx1HnHpkK6Ng+9JfP9YbSidWOl9uVj0iovgzQsOWqDyTm50QlO16rnpYiU72g4l7S/uZiwyNQ9PTQDN0ol0GJttvhU+clZGbAp7ibq7DHjRffSeso6UcTE4esNnlbBtGmm
*/