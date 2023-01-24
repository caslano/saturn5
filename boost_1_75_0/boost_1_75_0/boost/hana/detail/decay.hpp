/*!
@file
Defines a replacement for `std::decay`, which is sometimes too slow at
compile-time.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_DECAY_HPP
#define BOOST_HANA_DETAIL_DECAY_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Equivalent to `std::decay`, except faster.
    //!
    //! `std::decay` in libc++ is implemented in a suboptimal way. Since
    //! this is used literally everywhere by the `make<...>` functions, it
    //! is very important to keep this as efficient as possible.
    //!
    //! @note
    //! `std::decay` is still being used in some places in the library.
    //! Indeed, this is a peephole optimization and it would not be wise
    //! to clutter the code with our own implementation of `std::decay`,
    //! except when this actually makes a difference in compile-times.
    template <typename T, typename U = typename std::remove_reference<T>::type>
    struct decay {
        using type = typename std::remove_cv<U>::type;
    };

    template <typename T, typename U>
    struct decay<T, U[]> { using type = U*; };
    template <typename T, typename U, std::size_t N>
    struct decay<T, U[N]> { using type = U*; };

    template <typename T, typename R, typename ...A>
    struct decay<T, R(A...)> { using type = R(*)(A...); };
    template <typename T, typename R, typename ...A>
    struct decay<T, R(A..., ...)> { using type = R(*)(A..., ...); };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_DECAY_HPP

/* decay.hpp
LfafLsBjB3KLDw2pWGSdrsWH5wzXJ+qwB7XYWz3wtrzFXhvBa7yfJLbYA+fwLZjc4rsDIpaj2wp/Hr0+vWdjMqZHTe8zfLO/HqGAUoyXgoAdG/Hhw6OAn1HAixEKwPsv5dQYzLGN+PChJliehoAfbsSHz4VJKKA+Qh/t5SPwcXAjfexzjcTHu2voY2c7ffz2I/p4KZPDx3PX08e2PAs+nl5BH3Vd4zB3VFm/oG+ojFoy8A211wn0DS+tTKCkuRve8nHZx3cXvK3BN3vvPfQRAbVBh4aIt6Ya8KXop5Wp3O5G6M6hf1BjyduRwpzQwT6QyNzWLvpR1Fo5AqLOQaKHWhmoltvaxN4CLBDpH3qVJb6DJv4lC9/DwrEhQoSFb6LhAgt/nYVji4QeZOGlNPxeFr5DSQ8NEbqdhW+k4YtZ+ItKegzPYuFLaPh0Fn5MSY+7w6ksfAMNN7LwHyrh0GqhMKXRdhcN/yv9KKpX8sfwAwwERGxmbweVxCPQNwQD7eO2vsLe3mWB2PTUsACAdnJbn2Zvv61MwUDkhHA1fL9UUQX/n2NQ5IjwPfC9rWI9/H+aQZEzwrfDd13FCsASmYIFIJOE5wEIuaPiBnhB5qiciWHILOGxALovFh27kSKjZX5Bee52ZJvqZIiDXFM1opw0lmfZe8tt9kh1huYD0lYbBSlTCLSx8TRYfQNxSm/obYe8ifX6fOjUsr0LuvOE
*/