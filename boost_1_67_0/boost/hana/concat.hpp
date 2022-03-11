/*!
@file
Defines `boost::hana::concat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCAT_HPP
#define BOOST_HANA_CONCAT_HPP

#include <boost/hana/fwd/concat.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto concat_t::operator()(Xs&& xs, Ys&& ys) const {
        using M = typename hana::tag_of<Xs>::type;
        using Concat = BOOST_HANA_DISPATCH_IF(concat_impl<M>,
            hana::MonadPlus<M>::value &&
            std::is_same<typename hana::tag_of<Ys>::type, M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(std::is_same<typename hana::tag_of<Ys>::type, M>::value,
        "hana::concat(xs, ys) requires 'xs' and 'ys' to have the same tag");

        static_assert(hana::MonadPlus<M>::value,
        "hana::concat(xs, ys) requires 'xs' and 'ys' to be MonadPlus");
    #endif

        return Concat::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename M, bool condition>
    struct concat_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct concat_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename Ys, std::size_t ...xi, std::size_t ...yi>
        static constexpr auto
        concat_helper(Xs&& xs, Ys&& ys, std::index_sequence<xi...>,
                                        std::index_sequence<yi...>)
        {
            return hana::make<S>(
                hana::at_c<xi>(static_cast<Xs&&>(xs))...,
                hana::at_c<yi>(static_cast<Ys&&>(ys))...
            );
        }

        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs&& xs, Ys&& ys) {
            constexpr std::size_t xi = decltype(hana::length(xs))::value;
            constexpr std::size_t yi = decltype(hana::length(ys))::value;
            return concat_helper(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys),
                                 std::make_index_sequence<xi>{},
                                 std::make_index_sequence<yi>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCAT_HPP

/* concat.hpp
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
*/