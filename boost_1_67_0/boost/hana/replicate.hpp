/*!
@file
Defines `boost::hana::replicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLICATE_HPP
#define BOOST_HANA_REPLICATE_HPP

#include <boost/hana/fwd/replicate.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/cycle.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename X, typename N>
    constexpr auto replicate_t<M>::operator()(X&& x, N const& n) const {
        using Replicate = BOOST_HANA_DISPATCH_IF(replicate_impl<M>,
            hana::MonadPlus<M>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::replicate<M>(x, n) requires 'M' to be a MonadPlus");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::replicate<M>(x, n) requires 'n' to be an IntegralConstant");
    #endif

        return Replicate::apply(static_cast<X&&>(x), n);
    }
    //! @endcond

    template <typename M, bool condition>
    struct replicate_impl<M, when<condition>> : default_ {
        template <typename X, typename N>
        static constexpr auto apply(X&& x, N const& n) {
            return hana::cycle(hana::lift<M>(static_cast<X&&>(x)), n);
        }
    };

    template <typename S>
    struct replicate_impl<S, when<Sequence<S>::value>> {
        template <typename X, std::size_t ...i>
        static constexpr auto replicate_helper(X&& x, std::index_sequence<i...>)
        { return hana::make<S>(((void)i, x)...); }

        template <typename X, typename N>
        static constexpr auto apply(X&& x, N const&) {
            constexpr std::size_t n = N::value;
            return replicate_helper(static_cast<X&&>(x),
                                    std::make_index_sequence<n>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLICATE_HPP

/* replicate.hpp
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
*/