//
// Copyright Louis Dionne 2013-2017
//
// Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_DETAIL_STD_COMMON_TYPE_HPP
#define BOOST_GIL_DETAIL_STD_COMMON_TYPE_HPP

#include <type_traits>
#include <utility>

namespace boost { namespace gil { namespace detail {

// Defines a SFINAE-friendly version of `std::common_type`.
//
// Based on boost/hana/detail/std_common_type.hpp
// Equivalent to `std::common_type`, except it is SFINAE-friendly and
// does not support custom specializations.

template <typename T, typename U, typename = void>
struct std_common_type {};

template <typename T, typename U>
struct std_common_type
<
    T, U,
    decltype((void)(true ? std::declval<T>() : std::declval<U>()))
>
{
    using type = typename std::decay
        <
            decltype(true ? std::declval<T>() : std::declval<U>())
        >::type;
};

}}} // namespace boost::gil::detail

#endif

/* std_common_type.hpp
pL1T2As2eGtfU9eza6cAjEoo6JMmPLkI8dhBXH2QYutYB28heUYV74xAS2PanKhq8zuOQ8UxLKwNu/Jx+FPEew/rBWHqsGNgbeB10gi4O3rWkpOgQMh6Fa1Gy0lvl8zxXDr+0g2czdfdvCgB3CsdZPQIUQ4qDt6bSQpNtuqCdp1Tj3If5epRIu1uGAk6ELH1mr3cT7H6b56/irTze53MX642Uwa4Bv1ueOfP2BFvj9FqMS4Olcjvjgh3Ccj5dsQKFzD+L5uFkagt9MIlxgkY1GbH2/EPBtqAi/l8tmtqAhgcrCaFqlN3elvzKLb4zhtVbjs1uVqEK2Brh/+JTxKolvzXOIc2d+9/f31IpSPbyWTzJ9VWtNpd16chtIHoT+mt/Y29EzDVJn641ycV/k/GEDTTRbi1r4aapz5PZgHiaKLQLAk1nwKTp+SLeExT9vwTC7m1lNuK0QGdx4Htdss194790vJqkUKyCa0bQBB8CtpxKYJbAWG8R7u5u7sVdkcnMM5qBYHu35eDmfXjtHXF/2E2GlGaj95VczbMejVFBDH4LOeK1hjkmjAQ5g==
*/