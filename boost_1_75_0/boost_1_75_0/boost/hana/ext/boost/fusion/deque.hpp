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
H1g3uRk+qlrIrk7c1C0tnstrLNiNVwMFBmJZ9e60qn2vGhrLPgYOyWNZZR/amC3OVUvoSxvfoy29FP9Ky7RMOZwmXiSHBTFVDmdusMvhCRvnucinzBOG5iBHO3ErAJBRA93f4DZvc+k697YONOoLwBIcR9YbYlLrrRzwLAcANXRb8LHP0S3f0cUBsU6DpgdRJt1U9rF8xxGu1fERx6yRuiE1Uxek7sXxth7aC5lgjViVZp/jiO0g6i4+1uxb3t64/KOGg4K3iYn0x0NBC4A9hmDht3pnJIL6otgwsxzmpenKtbzP0SX/hOfsQ5KdtKLIk/M59hE80LVx6NEKEr53p7kBh9BkujOjkQbafY7dMJYz5NssHIyjFvwWk1ClrNsX8y1yJdVobuekOwHmPJLzD4i82+JWyo5EbdSPVGr5MCio9Fr1bpPjI5+jva72Y442Igcb0eIalXtUY7LQw+i1aOKeRvz70MnBPl8pbF/k0S85rkU3EbaZt8AkgU481M4U4+OTDBNIztnwhWwho6vNNjdavFN/rmTMaNtIXeq2cV941BIKRorSldL16HEhGDEojbifxz7qEj8ejn+4YCcrnbmy/r5QF1oXpShjYU+ABKN8H70jKR+JfgeseA/wXmQL+j+jb4FVrozTa3SfoTzYSOeEeNciy1UA7A6lZD18rcT3sCqVBxtYYjZ+jneSi4DdimzDEmQgh4o2Hqwb
*/