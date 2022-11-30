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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_AP_HPP

/* ap.hpp
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
*/