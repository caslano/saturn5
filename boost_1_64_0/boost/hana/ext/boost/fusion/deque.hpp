/*!
@file
Adapts `boost::fusion::deque` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_DEQUE_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_DEQUE_HPP

#include <boost/hana/at.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/ext/boost/fusion/detail/common.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/length.hpp>

#include <boost/fusion/container/deque.hpp>
#include <boost/fusion/container/generation/make_deque.hpp>
#include <boost/fusion/support/tag_of.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion deques.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion deque is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/deque.cpp
    template <typename ...T>
    struct deque { };
}}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { namespace fusion {
        struct deque_tag;
    }}}

    template <typename T>
    struct tag_of<T, when<
        std::is_same<
            typename ::boost::fusion::traits::tag_of<T>::type,
            ::boost::fusion::traits::tag_of<
                ::boost::fusion::deque<>
            >::type
        >::value
    >> {
        using type = ext::boost::fusion::deque_tag;
    };

    namespace detail {
        template <>
        struct is_fusion_sequence<ext::boost::fusion::deque_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Iterable (the rest is in detail/common.hpp)
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct drop_front_impl<ext::boost::fusion::deque_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<ext::boost::fusion::deque_tag>(
                hana::at_c<n + i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_front_helper<n>(static_cast<Xs&&>(xs),
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<ext::boost::fusion::deque_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
            return ::boost::fusion::make_deque(static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_DEQUE_HPP

/* deque.hpp
nmiGf26JneJP2xwTuRnygjnEmOGshZhLa+C7X7HJD6KIHRahr1noKT5s2wY+J7QCn4LOdaE+4U3xfiZyRPeRYwRzozsib3xlFecTo5axxguRI3fcw8nZvBIGLs1lTeRvnX2Jc0bio74hBgE/j2OnDXxXwaj54o4n5XvgNMNYG/r8AP6nEsC+hs8fJpaD1fPofz8Y8Bk66OYefXMwk5xKEva7nTz/p8h1N/rT3CM+Z4tPXY69pwcjJ/AOW3gbf7/ZBFcCM8rY+7qu8Db6GjYc2xlOLPay8Jnk/2cxZ/auAG70SamJz3Bzns3698yAo/SFgxJz2Sqw+QlB3EVFf+CkJ+B3L06EB2/SuH9MziyU2Ix/l7D2A9zxf5W+FhWRJwnlLJ6YuGw3e7k5iO+WITZx46/A4xR0YO5RcrgLkAVnFQ4TZxrwoXm/ksPZjc2c49z6eWSLLi/pim+PxH8j/3r6fjsNjkw/C8gFmOzs/y5yk4vJo2IL7TT2Zzb+0IFM12HD+KK74Ui93wNnsdFi9iqvDgxBv05zpmwHGw6cYa3oUq+92BPr/WIx+UrKWz7Hs8g7Cfk9hW+rCOYuTC844CT0DRyK6U4OFNwWnwnoRR/f/gA/Zv/y2JOCL+kzl/7wT0HXISt8lQOMXJuGnmLjl7TivAsbGQfPChnEPQ5yMpUrwKYW8Lf16Ar3T57G75V0xodgX6lL0cEw+N5OfAW40/1y8oj7yPFx76x4K1g4Al52D/XnOMcCqweRe8rYB7+N4zznB3wmfin9R43vqdH4vhf+fpC8/jtgD/nCnEvgM61YPzxhEXJvY4MTsMebmqMrzPcRONphCxjZT3y3MWtHb6PHkQc2Yevx5HNLuPtQgd6PYO/T0UNyVENH89xhcj5XwCk7EBd1RoZ1Guf1fI61hnjhfmKS7zXOgbnDAP//J3i0jv15Cvluy2I/I8Hcj7mnuw5dB19TIzlLC2HPqzmr5K7X9qv5wdev50wgizUNR7fbkgd2udDBVfCiWPwrsdF09HIvdl1cjX7hd158GN2YALfi7834vHB0X8TZA1KYww72rANji++uQOZROfjVjuwDfmjqMO6OzsH/OtD1mYzTDd49n3HgiDX7sbNv6XMR8z2Cfzbht7CtY5241zKWGJMYx0WMdQf7ObUDWBvCfg7mnIc1Pj8Uvw1nDV6CDyskBgK/7j6MrGLwvRfiBz9kbejh6Gvok45fA89P/gbHho/cmMw9uOFgMLFu0CT4Tz53xNG3ULjba+jUDez7BcSN7Y8hSzjJgfbsiRVMxL+1Q/f+0ZFYLYPPq6K75WB6EHxkLn18CT4t36PpZ0LJ+OlrtmDb4rt3mMsVYEwLfOha9iznVfTpKHjQDV4P55+4lzwG6/klmyOHuehmPTElunVXAnt7DefO+PnqMvwiGJM8mHh2Fv66Dt/yFb5uFvl31vzOZta6Am4NDt8DxoyG986CE5Swn1FPiM+WwJ/A4E7o9amnwZLuYFMeOYUX4Pke1oAtTiGnV83+ZbPG0z2xh234QvB4mYNcPdj8KXOIWaRxpwCbxPf//BV6ZcYeqa9vQ9wUxOel0MNk/NeU98DE+8FDxvgcrpb7OzpHjunqUUHwGrAcbM9sy/zPg7t/Tf4PmR6tBEPg5U/w92Xvoluc86JiWtxGZEXMUo2P3dwF+RFr98d2TX3gDU7s/xDYPhfZggE76T+LXFCnR+B3jLkDnCkohHcTC1tuRz7vMi6cYuXLyPc+bGkyvPQN8Diez5f1JJdXzn58go8Fz1zwhfd7gFMjxBjI8HfstTWYlCU+wwqPexNesxEcXUw8+jB2MQKOQd52MX5gDrz114/A0XV81w467z6IXzo=
*/