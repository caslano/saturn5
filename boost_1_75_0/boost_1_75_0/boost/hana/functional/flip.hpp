/*!
@file
Defines `boost::hana::flip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_FLIP_HPP
#define BOOST_HANA_FUNCTIONAL_FLIP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Invoke a function with its two first arguments reversed.
    //!
    //! Specifically, `flip(f)` is a function such that
    //! @code
    //!     flip(f)(x, y, z...) == f(y, x, z...)
    //! @endcode
    //!
    //! ### Example
    //! @include example/functional/flip.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto flip = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y, auto&& ...z) -> decltype(auto) {
            return forwarded(f)(forwarded(y), forwarded(x), forwarded(z)...);
        };
    };
#else
    template <typename F>
    struct flip_t {
        F f;

        template <typename X, typename Y, typename ...Z>
        constexpr decltype(auto) operator()(X&& x, Y&& y, Z&& ...z) const& {
            return f(
                static_cast<Y&&>(y),
                static_cast<X&&>(x),
                static_cast<Z&&>(z)...
            );
        }

        template <typename X, typename Y, typename ...Z>
        constexpr decltype(auto) operator()(X&& x, Y&& y, Z&& ...z) & {
            return f(
                static_cast<Y&&>(y),
                static_cast<X&&>(x),
                static_cast<Z&&>(z)...
            );
        }

        template <typename X, typename Y, typename ...Z>
        constexpr decltype(auto) operator()(X&& x, Y&& y, Z&& ...z) && {
            return std::move(f)(
                static_cast<Y&&>(y),
                static_cast<X&&>(x),
                static_cast<Z&&>(z)...
            );
        }
    };

    constexpr detail::create<flip_t> flip{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_FLIP_HPP

/* flip.hpp
ATOINMPPE+0vYu37Aj7ZgV7+bG4Rod/hFnaR9dloUuBBpaNL3QApCkhDUmdCt/34XDERendDdaJiOpTmW2CSw+kBbfntfhoi0hcbcNcSJ6Ddv4bv0HyDDucYCvilCDDgDEIBT4kA2gClgGdEACqGCo/rVU2GzgZ7jjnUZLslx4waPUZ9VAkxqyGHuRJiUEOquF4J0mGQEQKreBoFjaiGEH7POeDABlS2NuFEeIeF1K1NNMdbSN9aeSeFa+VdaFzDe/piC3p3EMw7STDvcMG8aMn3R5jcrI+hIzmmDTV1h+p0khYGOPF5sVd1rA2TZHchFD1ByZ5BtwAw+3CK+yI2SEn/dajOEOulfMRCdWZJi/JmXmbVyTS7edPJJlmrucVM1coOlWRrAuMRwIrskzDcH0MZ9NhiG8WuwGyFQ0IrVpzEUP2xxa7YbQg3J5tGXZ2Uk41TBK0qEnnyMA/LWaEmQSif6T9b7OJB0tYyu/xav8Yr9+8iD1XmjhwzbmOP7oYX3NcefQFecKN7dCe84JWI0d/BC96JGP0vpn1fPoPdQY/HbpPI9jA+eqPl4bGb+tAViWxmHCVDj+qNFJaMMRt+d+I3Xpj49voBTFvFdaEmE8LAUztaIAUHXT8gNoAZR+zpTc5U08WrHkEgmYoCpmM5rmODY2mf5bg+G7w8xQ1bKI4TWrQbftdm8frX1SVPYTXf8bq6mkxcW0BnSvZ6
*/