//
// detail/cstddef.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CSTDDEF_HPP
#define BOOST_ASIO_DETAIL_CSTDDEF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_NULLPTR)
using std::nullptr_t;
#else // defined(BOOST_ASIO_HAS_NULLPTR)
struct nullptr_t {};
#endif // defined(BOOST_ASIO_HAS_NULLPTR)

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_CSTDDEF_HPP

/* cstddef.hpp
nOtPscOwSWbqvR1z5aPUJhK/CeWMJ2azsAckYeIXBKBkFGyRQWchKyWr/JO+ud69tfLFKYv4squHkQBTlCpzY2AWJsNAzZ8ttjI9x56EO9NdLxflNK/aMRCYkwqazI9j08SSJd5FgvOjlSmmn6J2TwD0bD9NlTbSndZScTz5NhDNEASjMmGS89vK+vjRZu9uf6MI+hXJEWd9kh+32N9hlx9v7bKbicO/Jx68QxC61/vflP+YBegVdJ81Fc3zSE379r54mTuduyp/LUuq83E2YzXkS4QbiBw/32PTEjZupMdwKcoAaB2yHJ9i26jRfPeIA0l51M5HOPQ6J5j/ZUO3UTsdhBa1cK3Tz5rPxJcoAN1WbOF/rAvRihevXcWgo2uP+9VZa2dElsBb8Rq8E0nkW0lA19dpwC7M8sq7QcJiaZcTRYFX4fConsb+CTis8i9zqQbiZBvS7isRgSc/5iS/djY57Oiy4bluw72HAiotvujIdYcccjm7U2/YeAcF0lZmwQIi2vOTWWXOJr+S7PDXoYTNDKbM2V+ads+Kq/fZQbjtcXXibS92SNyOmg==
*/