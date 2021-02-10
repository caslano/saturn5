/*!
@file
Forward declares `boost::hana::back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_BACK_HPP
#define BOOST_HANA_FWD_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the last element of a non-empty and finite iterable.
    //! @ingroup group-Iterable
    //!
    //! Given a non-empty and finite iterable `xs` with a linearization of
    //! `[x1, ..., xN]`, `back(xs)` is equal to `xN`. Equivalently, `back(xs)`
    //! must be equivalent to `at_c<N-1>(xs)`, and that regardless of the
    //! value category of `xs` (`back` must respect the reference semantics
    //! of `at`).
    //!
    //!
    //! Example
    //! -------
    //! @include example/back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto back = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct back_impl : back_impl<It, when<true>> { };

    struct back_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    constexpr back_t back{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_BACK_HPP

/* back.hpp
uuTQqElh7I2uWYH+iUcGQzK4dcesS7XdUUHbIW991yiskU8Ng4OHdPxLBF5H01OvG94V33vqVrq5yvg+5FtfteGfgUeK/gU900nJe0dcKV9IfppkZZzhvQRpXFzT6aaJpPulyLGdo0PMh0R3hK/Ce0F2EkHaT28Y+00YOslv3s0iGsdJAq0AiH4tWL0VbUTXofTbTfBZHUi7GY2WkE3qWR3Gtdh6NRj3WR2OLfBwn/hZo0tNQ6tnutR8VmOimgrhBvXVB0EQV1X26iDuwxq4UlXhFtXDJohVBXVueg/rpOK0C4oh3w/Bc7IpisoJCAmJftYQEsfQr5PoPmvCaRux12jMPmuH0pZlLwCln9WhXZOwTqv7rA7nmHS9Oq3OMwajd6Gu/6P5o3fy8Z2k/Z2dsPYzZzrFy23ekhR4MVLqQOHbuX67OH/TqH2Xp3P4DNUfDU7GV8fD0aUPgYcDYV6WyxDM2+HH8fnIB7jOVlVaBmuP3p+Na5XLr0kVqvvh9eC0gXoxkbMW3MNRrS4spqF6Vx9HDbTFqmzBenE5GDZ4iPtRbTw8eXc8HA5qACVu8cECE+znYHQMVsX7WkdlGadJ9jUE8XpwfNWgaSLjQtNUSvg/vTVt9wMoCbpDqiZtGNEq6Yi0ullKReZ2zftE
*/