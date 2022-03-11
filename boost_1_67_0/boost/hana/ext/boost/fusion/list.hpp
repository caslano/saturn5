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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP

/* list.hpp
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
*/