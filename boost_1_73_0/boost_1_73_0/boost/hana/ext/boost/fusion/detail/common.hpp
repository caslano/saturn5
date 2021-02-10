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
eNyqmCK9RpEhs9AB+BJI+Nf+X7N3SoKhl/qGpEf8jkJYZ8DoQkzugXfJ9wt7SnlQSL3v+cCQlrCQcgZE8DPM85Dt90U7az5vjLCvZthdmsbVh/k7EgUKHhbCwuzL7TsPT2Z3yD3+koV6KI3smNl5X9cly7BYfzVZfHR+AaINSGsfLMBrDcfS8CZpg4Ix6zP2Si+Ql2/t0XUFrJ7Trwl6UCrWGpRF0opOUEVZhVrUiYoflMxCUirTVCZBKXakK6ScKj+pZlP25YGto6U8RvXTiBNIKZauo1t5x35Csea0ALCGQPGDs9HhfCcUnq274ewrZqj4gLDWeTpuSGMXIdlg/z8UKKDHW7tPd5892SeBlkqc3UyT/u5P5EuMJVGa0vK4FLF8FMrwvirUFMoP+aDSv23Aktwo2zroeimQqyabbYvla8GQNlfGKYoY0bPd50+1ER14xIA2H2cjfvpce/8xvAmj21CEKaoc61A6lC3cG3SoDxMVQJumSIiRJYO0oMM+bmv19XABs7ujz64KWXTu/X3lo9BcMWCSBiy9jrkuyn9yzr9mr4sRLfer5sTFCbHlCihDcsn0oPSc1wPa02DuFKS8xyQg37vHeU5W0ts8i7McPjbheypvB+YiAPoQ8dnSmGS9SNxPoFHhPYQe
*/