//
// detail/throw_exception.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP
#define BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)
# include <boost/throw_exception.hpp>
#endif // defined(BOOST_ASIO_BOOST_THROW_EXCEPTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)
using boost::throw_exception;
#else // defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)

// Declare the throw_exception function for all targets.
template <typename Exception>
void throw_exception(const Exception& e);

// Only define the throw_exception function when exceptions are enabled.
// Otherwise, it is up to the application to provide a definition of this
// function.
# if !defined(BOOST_ASIO_NO_EXCEPTIONS)
template <typename Exception>
void throw_exception(const Exception& e)
{
  throw e;
}
# endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)

#endif // defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP

/* throw_exception.hpp
psBIukV+B+v1sATyOwiKh8zbqUlcUdXDWxegjP1960KU0l9H6H1VCGWui+z5QmHp+H5icKBt20oUDe1UJMcUqMsw0ly09q0TkWAO7MfbmSRfCxb0+kWKAGyu40Cp00MWQxqZxol+IyzrYMjQWPIBQa0ZVtYu3MjgrB5OEjh9P/EGeG39O553iOKo6WPVCUjT+g1yHFpEShUWK72DLZiFKpJPWhT97q9VvioExdFmq8KBROrQxmjKCFsVepdgrSbvpUK571DYGowwWgwe6R0K29gQbLZty4FMUmgqj1vNuCZUEb9qyjC+yE3KUnE5ZE1l5GB7d74iXp7Ax4mXl/B28fJUvk+9YUlmhkosFHyGxBQ/yMzziXkiZUm5KGp/S7Xu7aWq3W0i6nVjFK0zAUkdXe0qbbSepMUhcCZWNO194FxjWWqGherhjjY+yk1ijuGw3U+z405g62+xNS+hFZIPkev2qAQjATfQNUArNFTyY92koRGKCCTqsDygw0KWYzmU0uX4ZXoeqPY3mEd5HSmIPIbvch1I91S4HwZ5Dqq6JeETpqCB2X2XfSO9P3dkjrXj+MjGPsekOAwpqCO1p3Ag8RYQ96thAOW3R2CEkb/JO4gszlf37KLyPxzrNZTEcVwGLAee/Qclanj7ZvZVVoMzHvUbb6BjmpF+vFtAdsZSjYcfeDRwgNAH8AKqCxGbTa5unCGJWQPSWUzOs7OD
*/