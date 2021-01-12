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
Lfa3IdXHfACYUf2aSr377nilv/zbQZsb9tu5JJ4nYbiMsPinCVrBaLY3HCRm7m9RZle/nxlYq2PoPXwraAd4XkFnrbqDJ73cyPDgAI438Gc0Q2YDhoEb958A/veVz717cOVfQb9E5qj7zdm475aVSm4+hA0iu6M+7isneRoWa6TYZt0/AL0zvLTPPx4kBL4bklEuCkS8RIKqWC5UhT85RlEQx8CNWqsH6yEJxTqJcUYuDlcU
*/