//
// detail/win_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_MUTEX_HPP
#define BOOST_ASIO_DETAIL_WIN_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<win_mutex> scoped_lock;

  // Constructor.
  BOOST_ASIO_DECL win_mutex();

  // Destructor.
  ~win_mutex()
  {
    ::DeleteCriticalSection(&crit_section_);
  }

  // Lock the mutex.
  void lock()
  {
    ::EnterCriticalSection(&crit_section_);
  }

  // Unlock the mutex.
  void unlock()
  {
    ::LeaveCriticalSection(&crit_section_);
  }

private:
  // Initialisation must be performed in a separate function to the constructor
  // since the compiler does not support the use of structured exceptions and
  // C++ exceptions in the same function.
  BOOST_ASIO_DECL int do_init();

  ::CRITICAL_SECTION crit_section_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_mutex.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_WIN_MUTEX_HPP

/* win_mutex.hpp
Kf6N/LtyjU0+ZChI0TAEDbqPrYsx0NucCZyb8FS1RFTteUuinnD0H8RB8uh/5B8+sSwXRUN9YT42/TokLjTDknaMt/YiHdnYZ3yoZK/S+p2K7TLyNEtPzEoGXDoTLafJvMhmNdthFoXTzdokqNZHVkubDfw5sTc8gKlEMWpkMycrIB4cyWuW1uvoBPxu0EuVPT6XHQkmmBitUm9yw5XxhUYtjvuqvApM4PCcjxk+pi/B5Q8H8iAf8EbEQT+G9F61nxpp5Mxbc0AOykE1vQoXBS/lQvdL9ZpsKWcocl5ei9R4yYUIeeQ9XwcbQK5wppW7XBrFj02yAmlVJR6x/9n7dXg4ipFo6/ZmeG6whciqkcf0EShU4qMBC7r5b1On39Erjl+dgRsi1tazUUVatnWYVujMgfTl4zddgKY5SoWaS1VrhH4kSyZDNinF6i7Vg7dmoI/v7eFjh3mkt6XmpUIyD/yKEdCbAIC90WpOiuOxQ4zoNziSTgbzrtwgnVgtdIUJs01gCA8btmLenjPch55Y4mRCJBzrIf+jsfIbKohm7k4MleZc5ns2dZD+pw==
*/