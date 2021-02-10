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
CRZF28wTCnlOh3o8gFZkMGvnyNWwWqzuFzemqipzAQlCBK1BEsbcUFoY86blKShg8qXX6xAyIGRJIXptwHGjZHLwdRgB2GmeIG0Pe8WDTaT86A0X8XxsOvO2hMrPs2+axj+2QRmSQVj3PbFPOLTBagMhcGNQCZlLspTBcteRHSVXE7ey7Oh6CiY/tog9HU3cBxF9SZO4N8dzim70zeHmL7owXVPiJJ9nOE4IwXZcnLmaWeeJToq/IsHvSN9QSwMECgAAAAgALWdKUlwfa5T6AAAAjwEAACUACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9iYXNpYy5kVVQFAAG2SCRgXVAxbsMwENv1Co4tYOUB3touGToEqPsA1T5bAhSdoTul9e97dtAhBQRIpMAjj+9clh5fQdLozpTXHp9COA/DBa87iZemkYqmMWji4j6IfMjCPdbKP5u/Ky+VlUfO0h9S9xaUFq5bj2By5713A+UsGFvNUEZ7NAkPJvhOGmEMKl1ZCZFFTxhiEtixDzfRHFpWhDIZNpLXQ2mvJi3kvGHlVDSTSIdW9hsbt8M46R6Bb1RrmgjBrZVuiZuYSkj/ZmkMumNBwJTmmapF/B/1Shp5wpO0MSKIrWqm1w7eT2kh0Q5cDRSr
*/