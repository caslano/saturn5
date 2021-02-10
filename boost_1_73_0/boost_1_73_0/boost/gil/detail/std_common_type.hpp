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
xrhWpLEhBKDhFrpo0fbu7oKFj7hyhlWTGcZpTNR9CHQ14XR4PSPqBE+07Cr7Gr++ErtfRvBj5gb9XWAMRIKhFX1B/3MyDEBAk9I3tSPldNCv+724RXxDtG5p7w+5HCwPKzIZMJ6wEwP2+PQ3T9d4GhrkMgerG2z9Z7TSG0wJY7TFZe+xQwhqPkSr1lkG9e9kgo5FqXz8Dgy02QB4ipp8FpGIjWVAAhQXC0Qli1D3bRPBFMlz1k5qvjdReMRDkBrm/AWrSXwEBbUkwzpUsY2b6z5MoG1dn+OoBNnp1eXg9M3gQ//D6fkno6PNq1MqSRSkHfktyQV1H8QzWNrP4kUXvevdvR8qHQZ/nyWfsaGXo4G+JFZtSB/MjNCdP69wGwxxuPz65qWj2251AGd3gQ7g9x79fkG/v6Xf39Hv7+n3D5oDwucfqeQn+h3Q71v6HdLvIf2W9HtkW3V3saRLY3VprC6N1aWxujRWl8bqOmN1aawujdWlsbo0VpfG6tJYXRqr64z1g/N5d7cirU1H53h/dQKIdUESLP2HdByJBVY+5RotA1WLKFwPZGjicAHjYGcPIhquSliQNxCNiRCPLQxbGmkCJhXYQ5llaWY5ACHDAnqvkM1fF+HhHIIZXxR5G1fQw728OKXVqW9jz59r
*/