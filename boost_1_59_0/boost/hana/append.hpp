/*!
@file
Defines `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_APPEND_HPP
#define BOOST_HANA_APPEND_HPP

#include <boost/hana/fwd/append.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename X>
    constexpr auto append_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Append = BOOST_HANA_DISPATCH_IF(append_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::append(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Append::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct append_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(static_cast<Xs&&>(xs),
                                hana::lift<M>(static_cast<X&&>(x)));
        }
    };

    template <typename S>
    struct append_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto append_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<i>(static_cast<Xs&&>(xs))..., static_cast<X&&>(x)
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return append_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                 std::make_index_sequence<N>{});
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_APPEND_HPP

/* append.hpp
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
*/