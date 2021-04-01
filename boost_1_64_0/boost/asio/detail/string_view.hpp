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
AeHRap2CKn0o1nng9lQcChCyW4nIGMujNA7OLoTsYnqIU2Uk170kyiu1gxHnhadSHFGfjlLtH9Oa8qz5Zyyy+pDnMD++dcSujBuH0EaCJ8sww8UBA8nGhF1lnTVX8TuATMq5oGgjzsAgVIh0FtEOqoAPX1SYCM6L7c7pP0csgj0LX1MbFp5TabWHNN2GbPb9D1uQDY645u8Kt95DN5/84fDdg3+2ARrekYenl3NmHkDYwbaivYWJu3bUYTpH7cFjDfXlYySijw7kweIO+jK6md9mHnzlN4NyPuufrnXFTOTnhqhLNhX7ZzcyoEb/OP+BaFIvwzk1FveIRbWjx/zxGjMPleDlkK3nnzhVBd110JPMo96V6t4FskkRJOz/SGtq/XKxf2nGmuJghQ4qLe7br3KAZy42jN6WowiOZMEyK0mtwjru8x+LViBZvnaiQJ4/0tFge7c5ahb2NBpD37Y68NY6t2MVUMtXUe9t927rh4qdzwSrH1hrf67ub5EQEbaAnNOZ69q9YY2Efi98yTB3cUwT7Fyj9WL23aqkl8e+iTKaAWX2JgViwTxRnA==
*/