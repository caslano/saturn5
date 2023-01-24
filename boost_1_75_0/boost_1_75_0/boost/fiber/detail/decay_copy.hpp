
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBER_DETAIL_DECAY_COPY_H
#define BOOST_FIBER_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBER_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
z0xFMoqW29IC6iXLl55IMlGALwZdJSBeppCyDE+hiPnEYEIt9YNVSdCNA+nRl07CQvucOukzHycXPq92QpbBJl8tdgp5pl5Q5F+eevpvxi7PPhaDjFHkP9/iAFzRgPKiM5iG8HuQF8kflUAqqCopyx5jKXdFcXHRwCgQ0yj5AOQxUWCBnmW2lF8AiYR8lw1CfcOeBNsLF2Pzx9pYA768JQ5yeHUpESNUgFiiAkQhiaRdrCwbSEzQeuNVEMgb7OV+wIbzl+CmmoZE32mSrfvy6ghK6sC//UgnhBKoNN0qUkJfQoUwGGKsJM+so3ie7CE0XRlJCRDGrEChbC0IZbO6WsqrEcp2K9cE/4aUo+WrkZsds4ztyWXKVz8RIzAqEmw2xlSyvyrImR60vnQlWfA72Bu0IgFJ7u6g9akrSeYJ6SlYa9dHgnY7rwoOgBJI/lfLsH9+GevyMhpOJRqOBCuhP5jklbV965VkPdgevprlqbSUx8Lbb3jYMFZVZB2JuFJkHblDwhzd0OQiNkOPLqGIl2yGTkHASErn3Zn1bBGBbEYVzNGYRdQmezz7QhiDR3fM7AtgLuwJkxuALHqGrQEM5bB7osjGAitcSx19K438I/58AxFAldIlH7zymxhuuHAju+pNOtcry0iHPO8mWGVsbWAaClCXEUJcEaws5vgGqX9ikXQJypdxDs6zjEYUCGMdlUcsAZV+eg8UKcbY
*/