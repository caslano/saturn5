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
KNAIeXQWiV6+EA33jS1jRv5F7kCOCjLRamNF81vSH10C3oMH7Ua+WnmOB8hkFRc4VpeA7uy1gEGpYKd7CJih2vvc9QYIWGToiFmE5JMPK9PWyVOvgf67SZ4KTnppl0iL4Ntd0mgK8XDGG3BAgNs0NmJt6R/azIPPdhn2jtTOvCQT40OkC7Rmnvaa5oF2xF4bMbZ7XuK1HXDE/kYm5g8AQzNNDE4kmQBkIhkT/V+5aMKWn9rt8aLMLTn3sOu6Yc+CqzrIbotZw2pyUtDqAPC3/GRIqGKg6WoYj/+h8SBgbK9tVj6gaczEPYvshOm6NOAjsPMuzVpxxKeqeEAsjSDUxGgsdcsvo3MdypX9AM4UoFn4hXd9WEbty3s0QKFrf3EAb9q7IvoCwD0qGMKAHq+Bsu0mSdEZhYYYQMDA5PZ6mPbRjG80GZ+ZoNjozA01DUZWQ3mdM2uFeewHBh9NNIeWZPi0F3KKWbIHEmMFANZAftlE2p3oth0t+EP0NL25GnDSPcobbWcIZ5sfw96jNCNxG8h3MtoLRkkZ3hnhRZCrEf5AVDv2Z0C0DhZwpQ==
*/