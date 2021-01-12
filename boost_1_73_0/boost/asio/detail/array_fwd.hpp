//
// detail/array_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_FWD_HPP
#define BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {

template<class T, std::size_t N>
class array;

} // namespace boost

// Standard library components can't be forward declared, so we'll have to
// include the array header. Fortunately, it's fairly lightweight and doesn't
// add significantly to the compile time.
#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

#endif // BOOST_ASIO_DETAIL_ARRAY_FWD_HPP

/* array_fwd.hpp
NAenWfcucUCbdheMZMqEgrgJmf49J9Aqg3eyf4/CL+P8e1Zj5yC/JXvW0IvU+icdHZEXIxqb8fP08SyPKJhiYqBP5xez5kTLY5zyIu4ws9yeQz7EMpv2pGsBLgr4F2vXAh5VcYX3lWSTLOwCQSKJEjWVaKJGQzUhUYNARKW4SUhCCwKtSreRKoVdQI2QuEnIclmkb2yppda2tlJLK0JAIQmRJChWfLWorWJt7Q2rFbVCAGH7
*/