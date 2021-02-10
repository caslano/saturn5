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
O2L3c4sR5ynqzRun/2ydIUPdrzFk+iPukVmJD9R7sR/StjqZpp97OZoTLVRBAdGgGorYCS29bHDQ/4Jq0i6KBiMNx7U9G4W4fcyKvWs6pTfa2hoEza9D6IdAaOkiI9drJ8/UJIGYdi/BAH1d/myihvzeyGCM6PykXVUQ0rwqw0YTfeiPH+MfN8jdf98gd/+wQe7pgzQY4C/o6Cy5nnBUBVGP7i+gcUTqkQRne2/D6ECdssOlpK2sUAOVNSF1lbnwvMhceMxyTcKX5i+7ebDReM4F7UAwpn08xqExeilu5xgVgCZmQzevVGhyxQu72QYntakk9Zb9tS/uyk97XS//seh+5IuDz0Dx5JdzqbMBdcPPcn3vj9IVdcObdCTC5l00mVm0wOEAX3SzqkW3I65P3zN3HS5MNj9YC/78bumRzcGiZYqX3EahY+yEitXGo4sJiA2wBjvL2Kdb8nzUqfz7KnuIZmnRyTJoskiX8ooDqsVOLiPJnJ2f/vkXOxKvoySVbqQA/WjMhTvoaMJTeJ2mywksiM9321h4m0oLSZ8LyKfZUFhaAEIjjlEKmt7uix+xt4hSb4LPsnjZ1T1u3L61BTK+AL4QXaMTQtTR2U/PMhr1w2cTULrJISLO+qTemi+lzqiBEo5+fBfaDWAy
*/