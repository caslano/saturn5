/*!
@file
Defines `boost::hana::ap`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AP_HPP
#define BOOST_HANA_AP_HPP

#include <boost/hana/fwd/ap.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/applicative.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>
#include <boost/hana/functional/curry.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename A, bool condition>
    struct ap_impl<A, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };

    //! @cond
    template <typename F, typename X>
    constexpr decltype(auto) ap_t::operator()(F&& f, X&& x) const {
        using Function = typename hana::tag_of<F>::type;
        using Value = typename hana::tag_of<X>::type;
        using Ap = BOOST_HANA_DISPATCH_IF(ap_impl<Function>,
            hana::Applicative<Function>::value && hana::Applicative<Value>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Applicative<Function>::value,
        "hana::ap(f, x) requires 'f' to be an Applicative");

        static_assert(hana::Applicative<Value>::value,
        "hana::ap(f, x) requires 'x' to be an Applicative");
    #endif

        return Ap::apply(static_cast<F&&>(f), static_cast<X&&>(x));
    }

    template <typename F, typename ...Xs>
    constexpr decltype(auto) ap_t::operator()(F&& f, Xs&& ...xs) const {
        static_assert(sizeof...(xs) >= 1,
        "hana::ap must be called with at least two arguments");

        return detail::variadic::foldl1(
            *this,
            hana::transform(static_cast<F&&>(f), hana::curry<sizeof...(xs)>),
            static_cast<Xs&&>(xs)...
        );
    }
    //! @endcond

    template <typename S>
    struct ap_impl<S, when<Sequence<S>::value>> {
        template <typename F, typename X>
        static constexpr decltype(auto) apply(F&& f, X&& x) {
            return hana::chain(
                static_cast<F&&>(f),
                hana::partial(hana::transform, static_cast<X&&>(x))
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AP_HPP

/* ap.hpp
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
*/