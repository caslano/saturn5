/*!
@file
Defines `boost::hana::on`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ON_HPP
#define BOOST_HANA_FUNCTIONAL_ON_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>
#include <boost/hana/functional/infix.hpp>

#include <utility>


namespace boost { namespace hana {
    //! @ingroup group-functional
    //! Invoke a function with the result of invoking another function on
    //! each argument.
    //!
    //! Specifically, `on(f, g)` is a function such that
    //! @code
    //!     on(f, g)(x...) == f(g(x)...)
    //! @endcode
    //!
    //! For convenience, `on` also supports infix application as provided
    //! by `infix`.
    //!
    //!
    //! @note
    //! `on` is associative, i.e. `on(f, on(g, h))` is equivalent to
    //! `on(on(f, g), h)`.
    //!
    //! @internal
    //! ### Proof of associativity
    //!
    //! @code
    //!     on(f, on(g, h))(xs...) == f(on(g, h)(xs)...)
    //!                            == f(g(h(xs))...)
    //!
    //!     on(on(f, g), h)(xs...) == on(f, g)(h(xs)...)
    //!                            == f(g(h(xs))...)
    //! @endcode
    //! @endinternal
    //!
    //!
    //! ### Example
    //! @include example/functional/on.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto on = infix([](auto&& f, auto&& g) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(f)(g(forwarded(x))...);
        };
    });
#else
    template <typename F, typename G>
    struct on_t {
        F f; G g;
        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const& {
            return f(g(static_cast<X&&>(x))...);
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) & {
            return f(g(static_cast<X&&>(x))...);
        }

        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) && {
            return std::move(f)(g(static_cast<X&&>(x))...);
        }
    };

    BOOST_HANA_INLINE_VARIABLE constexpr auto on = infix(detail::create<on_t>{});
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FUNCTIONAL_ON_HPP

/* on.hpp
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
*/