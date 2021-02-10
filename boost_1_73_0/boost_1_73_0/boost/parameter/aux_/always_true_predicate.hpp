// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_ALWAYS_TRUE_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_ALWAYS_TRUE_PREDICATE_HPP

#include <boost/parameter/config.hpp>
#include <boost/mpl/bool.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#endif
#else
#include <boost/mpl/always.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    struct always_true_predicate
    {
        template <typename ...>
        struct apply
        {
            typedef ::boost::mpl::true_ type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename ...>
        using fn = ::boost::mp11::mp_true;
#endif
    };
#else
    typedef ::boost::mpl::always< ::boost::mpl::true_> always_true_predicate;
#endif  // BOOST_NO_CXX11_VARIADIC_TEMPLATES
}}} // namespace boost::parameter::aux

#endif  // include guard


/* always_true_predicate.hpp
GDo2dJLUhZgptK/NYC9ol0Yf3rZ9a2cIxnxBXCmd3ZhUYZLTCNqlOcH+wqez9vp9v/3+jwTJodfd96EPbt+lX/s82Hh+5T+TCk225zTXSmq6ehSaqkAqm4lqS9YSUc253rUzQ9b5rvv9K6iwN7150Q1Dc5jXnV83UtP/9DeQEpamyGiNpTH11MEwHfYNgDp5p4W0OjYD6QNXdpyZs/xwWA4eRkxjZVwcPMjUWD1l1JyOgyei+n5s7ZtM/wVQSwMECgAAAAgALWdKUtkVI72SAgAAaAUAACQACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L3Rlc3QzMDcucGxVVAUAAbZIJGCtk19v2jAUxd/zKU6hUmEKhHYv659VRVTr0Kq2KnQVGlMUkgvxFOzIdijV2HfftYGhTpv6UiOwce45v3uvnfpeVBkdTYSMSC5Qki6C+ru3G0Edr47Yf2MePDvBnVY/KLX/Do7jFdYfFo15fgURYadYxU28qlih4RXxhnHm1nH8CmbsEnM/kROOY7fknaDOup4qn7WY5RaNXhOHx8cf0MJR56gT4jKRggoMLMkJ6VmIs8zvXOTJctk2dB6CLJKi7Y2GuTAwamqfEk3gdSFSkoYyJAYZmVSLCf8REjYnTEVB6N3ejfo3
*/