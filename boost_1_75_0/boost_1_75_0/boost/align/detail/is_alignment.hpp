/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

BOOST_CONSTEXPR inline bool
is_alignment(std::size_t value) BOOST_NOEXCEPT
{
    return (value > 0) && ((value & (value - 1)) == 0);
}

} /* detail */
} /* alignment */
} /* boost */

#endif

/* is_alignment.hpp
JaYeC4EV+sX+GsbfVy/FroAztMVeqdtKhpcYeRrG0KCZ9/CELYJ0NP6HpjwG39fACOVpyXtrmIXNDYxYviIBkgZGondll9InQQ5VQaukJ3oidagg0WPWEaAf/cLaM1K/ARlHcUHvSqhhG2zSSPAe0gVxHqmXGmrFSfgpQewy+4dLk2XpLQxSJqg/YNiKtNIxdNNfuDibjoY5ZXOn4u7Ti36p4QcOtzMPcpFo9XCIrngOUh5xHOBB1/aNZp/Ppm6DfQEbfA/fIXLG/l+MGEcP5hJsEHHHlekmTE2564QXHTred3S+C16MBNDNLx3dW4p3XcZI6JX72bVxKdiBJYb9eDeATtqPTeTPDVlZx86PWoZG4hZu47r34H6Br40YCYxNJMq+52hnG964RzOgpkkyIJZUV6CV+LljAX6ELFyGH43L6Zx7paJzQWYBuG0kBlUzvhHfoGQ7Df1YTSTSP8FmDmQCXM9qvJU5osKAJIDbzwzVklrbLqDeQJd9F6gETCMpjcS9K9tXwz5epi6NRBPvAL9xpbH0s334ZobfwZLxZF9dXDS4CEfIJc6OIZcDgO4AGOheHfDDQ24UNPtr7KBnPCgAQOggnsR9wKQ5QU7bLQaYX4Cf0I7FvfEGiE1Nh8HQ4H00NOMh3/k6d1ZFRsKg0H8Cjl9ytTztzD4cCE6V4B3cl6+q7L5E2gFMRMwuJuur6aes0xHv5yJPW7MP
*/