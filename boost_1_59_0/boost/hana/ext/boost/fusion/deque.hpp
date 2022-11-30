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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_BOOST_FUSION_DEQUE_HPP

/* deque.hpp
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
*/