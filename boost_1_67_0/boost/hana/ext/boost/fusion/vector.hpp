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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP

/* vector.hpp
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
*/