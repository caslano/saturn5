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
7zTMx/Vh7h89zFgYjlLel6PD/CgbZpUN8+tsmNNf9dGhsjev/ikd5sL4MJuVYjbAdGjZMCvqFn1gEwc6LaSwegZ4Bs73Fu3t0hv0+kPxAd6k0HYptI9gjaGtvrLf5mej/P9ojB/45agx9sOSowOsF8EB9vADkyBzfdg4go6lUPIdW/iVCQufzgl7j+Adwj3/oNKQxRZ+Flv4x6j1HC+fhoUfG9420aw6YYBsB6mRpXLCHlC9eLnIukMJCb+hAwo9nqpM9NE1pyXLL+AvF+18N3b+QYXOBfkrPtBnDHw+xdbFevoGnxUXEevdcLx3/2Lzz2dzZZPfFMhX6TodZp0EU5P1kzLkU3FIA58a6fNy896H7ZTGQE/hQbDP1zAXM6pLDQN4eas0UOix9vmhfaWG2JTFo/pv/PKZhGl65rxp+oQ+TR/Vp2nPGqPyDq78n7GRV06oC3/l2/nyf9gtJn/g86n/rlf+qtDNQp9aVB0rNqtUNqvkF3CcOdZB8gsYCayVPqNq6IQjM+gDo1abPt2W5oeVowHNrHwd7cgv/hmGLpQ/m1qk7I934rUGNu/otGWTDwbzPALTplAtdIXuUjBzUith7iER9AuNPwGiM3QCqJROu59k8Q334HYVumStyXPJCmFbure1krMK2+Z42+AXhx3XYuAzo1vlr2Q4sEoR1+J/Ig+FiCg0G5wUvLuhmMp7/U7OqqNngkPr7/bj
*/