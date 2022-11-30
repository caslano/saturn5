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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr detail::create<flip_t> flip{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_FLIP_HPP

/* flip.hpp
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
*/