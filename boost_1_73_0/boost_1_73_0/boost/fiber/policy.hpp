
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
x/QJsVj5i7MIfRM5m5AoeZ4YeudgmwmccSHJi5Ve1LsJOPeFnPXwp037gdM/WfJilRccKexJdk9vDlAOAu/jFOf0PgtbSSpnv6RKXvsYeifg9MxOnPXp4qz3IpzeBpyibpLXK4ZeDpSD9d0529/TPb0Zae7pPQvbCOB16eWcH1jOp/Vy13sXtrnAy0t311uV7q53CrYbgFfS21mvE2xbe7vrnYXtfuDd2MdZD78BONTHXe9vsB0H3p4MZz0cmpw=
*/