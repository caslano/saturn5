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
LCfqPozj3blh0xVu02ds64z1DpvlOeE2OD0aHGmIY+WeNh33i3G/d9j3UnmfVgKlDPq26pVmAm9oxvEO9h5MNPiTHNq1RaYt8DctWbuo+5K+NUD9UFgWJcujfRyByqP9dWR0oDGDvCuWCbXrZ7sralaMfLZG/DJIh+YlHcdv5XBo3hZQj6TzOQ8+kfCo/TSIhE1woVZRMFO33BQ8y4oe1sD5fOpcOlxApxbbTi22neq1Tk26bT0dH0TnltrOtSo=
*/