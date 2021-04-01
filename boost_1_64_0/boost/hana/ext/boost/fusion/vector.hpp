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
zr454gD0deJkvL5MINSXHYegwEMQoTW4XFYfDe2zqgd0KZFNQ1G7S6E6uHElyuYsgPFADUSc4wUTUEV9AnuEX3X/dOIgvYYf1BQGs01HBwN9Jc9K6Yn69AEvG2VW5gPUOEk3gHqhOtKGn/m+7XAKypIg1jqfw1aCIcVYU37mmZmjzdV1ip0zRWZrZyjophlXMkuAKZYqzIUp3rGoaVLCa2Oif9sOObRPUtIW14Wzgw6Wlrf1FzI/71UOJ8sSwJTahcECKG/eJQPhkuTw5KnIyCYzaFZwC/65YgsuVQN8XWptwcbU03FU60MSsYa16DXD4G3l2mY8nRIDpbao9i98tRpK+0GWL0LFjjGS3FW99KsV4YrXk/KFyWry0i+Um/n0nBOWGexCu1f6nxOASXCw+3PYNLzb2Uu6BCOLrn1FaB9pbny92jyV5svcy+hH/L2c177rFCBSXkqgINEao37oo/yONIRPbNEiC3jUBdGM3G4maNYD3V2gb+GCGyCh+CoicoxKke05jqrrdGLnDs1bQ4wgAL/DXuhkfTa3QLaBrzvaJutj0ulUITou0w==
*/