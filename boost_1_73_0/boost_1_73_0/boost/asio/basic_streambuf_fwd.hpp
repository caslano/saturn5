//
// basic_streambuf_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP
#define BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <memory>

namespace boost {
namespace asio {

template <typename Allocator = std::allocator<char> >
class basic_streambuf;

template <typename Allocator = std::allocator<char> >
class basic_streambuf_ref;

} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

/* basic_streambuf_fwd.hpp
WmRngbdW59J8JuQ7blAwG8HZ/LgIt+Z6we98obnp8eWMFa6w1/sVY9B0cK5fKcKXKPRoslO2ilmOUHq0zX0/eF8/JcLRCj0a6oasxtJ3tQg7FHpH4RaCM22NCLsUeqPgVoHzxxp7vZ3IX+OnGftE3ytxK/RoRJ79LLMcIfXg5oI3+DkRVuWPlpZVzzWs9z5cDXijnrfXy4CrBed/dJ7qfqk+PgKn7VoRVtUH1Xv1WmY5QunRc/RPgHdgnQhHKfQ=
*/