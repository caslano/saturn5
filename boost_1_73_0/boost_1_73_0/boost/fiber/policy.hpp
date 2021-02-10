
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
tKtCrvc2Ylk7R3nbVBgOy4L7MomFH0JbZbwx+00hNlG6KpuSP9KyLfYMZIWooDcOYRr2IGFKqCF8nkYn/jKCz+MgGM+jFfjHMJ6vOn+n0/lH5IbAqA3w67rhClE0INZ1KXi2F/ynTrrjRicwWQYzfxHFi8D/soqnYbj0gokXRPHRzD+CF9B7/hL+aitD8h70SpEQC+CV++o3lxbov5gzdRMrrqnf+EVqKfQensB8fOY5mxB3nZ8fQt3I6xusoWox9zCcQcobLXKRMiRC3mAj13wtmxtISpkYj+Fq7i/Caei4Ve78Iqq0bDMO7wiG5WfxwTERU4nrd9H16QkcFMicEgn0w+SHzve1AhveotQZ9wQNDuh38NZxc2FgfvTCSTBdRFN/7iwYNpRBLUWliWo4XTuW1lU3zUj1SjOBRBZVLps1o1pCf2OKsB0l/uEDYIlsUU12ypN+hSvkECSiYriSMc2Iywwm472qopQsvDPHendhauluu0ZsxkLRZAHLMkFrrIS04OidXRAwbbbXHNHseHXQEEeQnNrhuuQNzrnZ23W3myv6nkTRIrztPSLKOFkRjIo7WC2ZCkbTZBKi9d0E0O5SZPg0udmB7tq5vIuagKH85G1Jia/bUovDkl+iUC9Op1hz3pigUCECox6c
*/