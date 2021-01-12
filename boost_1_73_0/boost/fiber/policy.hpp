
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
aH5M3FaRioCvnS/NGkae5Kru8WflXJnP0WPdn/w60dfFldaZRXPnLRK36ZhmVecN6Uqx5iK3Wxl6LnSNH/hSLNvXy+eXa0S0ZTMO/Ym4TdP+wMxRSwPM02tdKmnpbTdjZno6cgPyotVO6v8xs++X7rej7eKosTdhmvcQkk5GkmOtsyT8IZkizLuIuMze47irVM7N+OZzTHw9+p3IZ5dj7v1gNO3pNfSdS7qMf+xCbmvc3zfr
*/