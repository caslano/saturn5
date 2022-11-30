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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_REPLICATE_HPP

/* replicate.hpp
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
*/