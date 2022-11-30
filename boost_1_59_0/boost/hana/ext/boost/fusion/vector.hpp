/*!
@file
Adapts `boost::fusion::vector` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/ext/boost/fusion/detail/common.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/length.hpp>

#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/support/tag_of.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion vectors.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion vector is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/vector.cpp
    template <typename ...T>
    struct vector { };
}}
#endif


namespace boost { namespace hana {
    namespace ext { namespace boost { namespace fusion {
        struct vector_tag;
    }}}

    template <typename T>
    struct tag_of<T, when<
        std::is_same<
            typename ::boost::fusion::traits::tag_of<T>::type,
            ::boost::fusion::traits::tag_of<
                ::boost::fusion::vector<>
            >::type
        >::value
    >> {
        using type = ext::boost::fusion::vector_tag;
    };

    namespace detail {
        template <>
        struct is_fusion_sequence<ext::boost::fusion::vector_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Iterable (the rest is in detail/common.hpp)
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct drop_front_impl<ext::boost::fusion::vector_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<ext::boost::fusion::vector_tag>(
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
    struct make_impl<ext::boost::fusion::vector_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
            return ::boost::fusion::make_vector(static_cast<Xs&&>(xs)...);
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP

/* vector.hpp
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
*/