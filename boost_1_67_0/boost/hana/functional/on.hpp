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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr auto on = infix(detail::create<on_t>{});
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ON_HPP

/* on.hpp
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
*/