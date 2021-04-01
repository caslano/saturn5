
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_IS_ALL_SAME_H
#define BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename X, typename ... Y >
struct is_all_same;

template< typename X, typename Y0, typename ... Y >
struct is_all_same< X, Y0, Y ... > {
    static constexpr bool value =
        std::is_same< X, Y0 >::value && is_all_same< X, Y ... >::value;
};

template< typename X, typename Y0 >
struct is_all_same< X, Y0 > {
    static constexpr bool value = std::is_same< X, Y0 >::value;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

/* is_all_same.hpp
TtKQFdIR9KNSq5qDoChj847efFqjtXAFTfH1rT5m2inBw53YHNOm73f9+8bFF03G30Arlicpav8IrcsIOKMO5XobLKKBtT9H4ymMx8nN3jLGRAMOg0eqZEBZO6JO2Bf75avCgrmQE8LqQ1JnsvfA1ZvIxY9PGLjZosaHv4sW4jtKtf99bQuMN6URvBb8Z75sNDVZyjopBee/1ViaOeA/oJ6Owid8eL4TROBVB+5JnK1/XOhuuhzuTRBjsMGCRf7bf5rk+deOEWEJ8OrA4R/r5+enL1aNevsB2FtZAtJSIlQzNR4G0gnrRFjfaXIOubWqpV/F/izxjWFaJjvBpBiDXd8kDGGVEC/Zd1ldKR6DuMQ9+ebh+c3fB4yhH0J519FL43sj7ddM3RuigeZdz15kVIMzFfRIOitEki5HWQoB1ShS9Rbi5JvFhYej6JA5HHO34uJACd4lXgbaNH+JFd5p0HWK2Qj8B/5wXkfyCYOdmnxzWQo10sEDYFnlOkAlhKt4Y+rCxQCMKgeQzFa9ZfYvosOKhFoxkbjBdQ7ARfF2A+pZfzLJGyI9yZozhQ==
*/