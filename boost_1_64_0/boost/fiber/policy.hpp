
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_POLICY_H
#define BOOST_FIBERS_POLICY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

enum class launch {
    dispatch,
    post
};

namespace detail {

template< typename Fn >
struct is_launch_policy : public std::false_type {
};

template<>
struct is_launch_policy< boost::fibers::launch > : public std::true_type {
};

}

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_POLICY_H

/* policy.hpp
2Gespp8dYUpq7qWx9sM1U8beW5tpw101LLjYzSrxIfgmz/szwv2Xu6uNUuUxrZo/9i9gXheUDdLNvgQDeioNBWQbEMLncIwXg/BTD05Nyc1QEwXcI29RLPP3UXURIob6uAV0rHySG3WJNktlx/uEk2V104IoUeoGZzKs9YwxeufxOxq3fI/rmME3LmnUrG2ZC0APQS4a89rAXCsAMi5wPFZsAg8jRIFCSayVphSjfKWtA6wVOcymv9NtG4xd+FUN6O90bLUQnFAFxKWhl6jqaba20ggl76zsKypT5sWlNcZGfBUA61kXJO6KA3avRqplo5b20l/6KwvoLTX7x4Z+M3i2xttsaqSal/+I4OVLaIAk7f24rZly/WxR7ERbM1J25wkENNv9AtyAP7h9B/f/noFHGDgDtipfvaFBPTboLE7Bk1VONZktQ9Rvxq/E3GjMabR/NE9LfIeZt2PYh7DAiwc0Us/XfT+rxfshh9Xyu3JS9rF+54KkIk1sWapXD0mwOuAMfaDMwNs+ZYw9Mrn9jnQR14vx5cAHWlsOczZrbKA4KTC314ki7lz2bQ==
*/