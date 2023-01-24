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
8SJAuQ3WUnPXtfuNeEgtQ7wMnKLqOJ8GcxU/XLxs5OPI3YP0MbGqDWgQJuNY8dzVgEk8aJTmrgtEiRQsBW2cLCXBC7j+udyusHFF3dh5+5IhV9TBIm4xc/xwZb1ZiYt/nh1/q9xinrIY2heN12kmt7aH7vacj7MmDOlpXitpuswiEG/KbcSEBaLAwA8Qp3BCv+lt0FQQ1MiAuWGXg6K1vpucIJCWiJfpWLQANH/Dsui7lfzh8jXjsqnHuDx9IXQe6+sLlHc3fgfNPA/CAll2AZdAXgPQ4P/iEM9XDzoKNmIfGOYNcjGpm9KhkMZgUJGzV0uRcnaJlGUGAJRLKmqgVY9fDWv9BIa6s5fCGo54Wwd409IMYnzmj5dUPmMl/7jE2tYCWQ/S9+vym33fhdpV952q8x7XTc6XcxJyqZ91KzBvdl98LMr86PeufcsIt4tMoLdgyjln5Da5PLFK2TLYM58MMao7NjeIXUr512k1re0oESnK5ouyMwnnuSa8VBc3Qzm8IcSZBHMWWm1U4fEARwf0jHFhay3NY9hCbfDxDhJY2m4xg5jd4sshaH1mZVL68wBKilhOjKVf+JzfTCn4hj8N7d8+y7DtIH9s+8Cp9lLz1GPr/yLWGKfE8zWBrwDICTT5H9Xkv5eFMyz5kzS5Zeox26PoR4xlqQh8npsL8nOLNxrvyWaSLu4sotSXCMm2zGYm/hfEoLF0us+a
*/