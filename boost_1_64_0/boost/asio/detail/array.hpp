//
// detail/array.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_HPP
#define BOOST_ASIO_DETAIL_ARRAY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <boost/array.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
using std::array;
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
using boost::array;
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_ARRAY_HPP

/* array.hpp
0Ah542EYDBXD1595mSd83FPXTPSLAUxxRTiVX2tr2ODRDCwF1negEOtkANcu+iTQgQY5Bbjh5XRegRuUFZnZoet555xC7nufuZq/pONNP1lr7bHotUkQnT2A59QLs1tY+7uk4ueq5ndbViM867hGrZpvXEhFqlVAB84+EstOXOZvlk+cWItCOdE5KsJ+lvzZ4ca5KpdtM47akD7sDnqpYtopCcWBMSKoeLLu0JYuDNh1WwLylV12kbFkWe7JJ/OzanMBRkRtn/jei5blzKp8Dxq6ONG4U6imsnFtINoW0PI57rMcN/C48TGGY4s/LsUaJAJA077EmUKx3Pk4C6ydCdPSWmHdu808sm+lTA8yDbwZJVvnND2iy9FQt2dqwTjW4M7N9eFEEdMaQQfWbzMe2vTrR5fJ8DLpUagTSeDGcOZY+kjYFYDuWQuBQb9Iedf7Vrvl8+iBRcNUs+DbGKvq6WdbNvwdCcshltp4M1pYdklnGZbTjmeFsl3PnGRx0qsptN9WTEmhsxzS0tF5i5+w9PgTrF8rNy47qwUZGuO9bbyFlv8BK5zIJcXAFQ==
*/