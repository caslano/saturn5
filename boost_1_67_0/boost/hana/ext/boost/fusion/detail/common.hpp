/*!
@file
Defines common methods for all Boost.Fusion sequences.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_DETAIL_COMMON_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_DETAIL_COMMON_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/concept/sequence.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/integral_constant.hpp>

#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename T>
        struct is_fusion_sequence {
            static constexpr bool value = false;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <typename S>
    struct at_impl<S, when<detail::is_fusion_sequence<S>::value>> {
        template <typename Xs, typename N>
        static constexpr decltype(auto) apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            return boost::fusion::at_c<n>(static_cast<Xs&&>(xs));
        }
    };

    template <typename S>
    struct is_empty_impl<S, when<detail::is_fusion_sequence<S>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            using Empty = decltype(boost::fusion::empty(xs));
            return hana::bool_c<Empty::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <typename S>
    struct length_impl<S, when<detail::is_fusion_sequence<S>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs const&) {
            using Size = typename boost::fusion::result_of::size<Xs>::type;
            return hana::size_c<Size::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <typename S>
    struct Sequence<S, when<detail::is_fusion_sequence<S>::value>> {
        static constexpr bool value = true;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_DETAIL_COMMON_HPP

/* common.hpp
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
*/