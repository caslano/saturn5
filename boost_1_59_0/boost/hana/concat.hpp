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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_CONCAT_HPP

/* concat.hpp
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
*/