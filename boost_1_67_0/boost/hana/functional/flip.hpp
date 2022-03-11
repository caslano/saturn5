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
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
*/