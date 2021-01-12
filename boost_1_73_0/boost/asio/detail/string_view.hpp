//
// detail/string_view.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STRING_VIEW_HPP
#define BOOST_ASIO_DETAIL_STRING_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STRING_VIEW)

#if defined(BOOST_ASIO_HAS_STD_STRING_VIEW)
# include <string_view>
#elif defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
# include <experimental/string_view>
#else // defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
# error BOOST_ASIO_HAS_STRING_VIEW is set but no string_view is available
#endif // defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_STD_STRING_VIEW)
using std::basic_string_view;
using std::string_view;
#elif defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
using std::experimental::basic_string_view;
using std::experimental::string_view;
#endif // defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)

} // namespace asio
} // namespace boost

# define BOOST_ASIO_STRING_VIEW_PARAM boost::asio::string_view
#else // defined(BOOST_ASIO_HAS_STRING_VIEW)
# define BOOST_ASIO_STRING_VIEW_PARAM const std::string&
#endif // defined(BOOST_ASIO_HAS_STRING_VIEW)

#endif // BOOST_ASIO_DETAIL_STRING_VIEW_HPP

/* string_view.hpp
x9CTM0+prh6Gt6zs6uHV1SNOra7OqT4tt7p6ZB4jnH7GmfgdVX3W2dX5eBl9zrnV1WMKzju/kIFjqy8w8rxQPS4qKr64pNQsyDi48ZeUlU+YOKmC35P5M2WqhF1afVnlNHm7/Ar8fMdbXV0VrcF00MfXqOfAq4AvuDK4q+AWwGlwD8I9C/cW3OdwL3zP5jl2tc1zyiybpwQuF+/vw12N95/CzUT4JXBzZ9o8j8L9An5PwA1C
*/