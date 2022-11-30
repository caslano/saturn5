/*!
@file
Adapts `boost::fusion::list` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/ext/boost/fusion/detail/common.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/length.hpp>

#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/container/generation/make_list.hpp>
#include <boost/fusion/container/list.hpp>
#include <boost/fusion/container/list/convert.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/version.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion lists.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion list is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/list.cpp
    template <typename ...T>
    struct list { };
}}
#endif


namespace boost { namespace hana {
    namespace ext { namespace boost { namespace fusion {
        struct list_tag;
    }}}

    template <typename T>
    struct tag_of<T, when<
        std::is_same<
            typename ::boost::fusion::traits::tag_of<T>::type,
            ::boost::fusion::traits::tag_of<
                ::boost::fusion::list<>
            >::type
        >::value
    >> {
        using type = ext::boost::fusion::list_tag;
    };

    namespace detail {
        template <>
        struct is_fusion_sequence<ext::boost::fusion::list_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Iterable (the rest is in detail/common.hpp)
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct drop_front_impl<ext::boost::fusion::list_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<ext::boost::fusion::list_tag>(
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
    struct make_impl<ext::boost::fusion::list_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
            return ::boost::fusion::make_list(static_cast<Xs&&>(xs)...);
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP

/* list.hpp
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
*/