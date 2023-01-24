/*!
@file
Defines `boost::hana::detail::type_at`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_TYPE_AT_HPP
#define BOOST_HANA_DETAIL_TYPE_AT_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <utility>


// If possible, use an intrinsic provided by Clang
#if defined(__has_builtin)
#   if __has_builtin(__type_pack_element)
#       define BOOST_HANA_USE_TYPE_PACK_ELEMENT_INTRINSIC
#   endif
#endif

BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    namespace td {
        template <std::size_t I, typename T>
        struct elt { using type = T; };

        template <typename Indices, typename ...T>
        struct indexer;

        template <std::size_t ...I, typename ...T>
        struct indexer<std::index_sequence<I...>, T...>
            : elt<I, T>...
        { };

        template <std::size_t I, typename T>
        elt<I, T> get_elt(elt<I, T> const&);
    }

    //! @ingroup group-details
    //! Classic MPL-style metafunction returning the nth element of a type
    //! parameter pack.
    template <std::size_t n, typename ...T>
    struct type_at {
#if defined(BOOST_HANA_USE_TYPE_PACK_ELEMENT_INTRINSIC)
        using type = __type_pack_element<n, T...>;
#else
        using Indexer = td::indexer<std::make_index_sequence<sizeof...(T)>, T...>;
        using type = typename decltype(td::get_elt<n>(Indexer{}))::type;
#endif
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_TYPE_AT_HPP

/* type_at.hpp
qIrE3YBEKT8FsnjuAq6DxVkRb4ggNk2jLoXNdIbN+hg2tY/eoPMa0TNIviUrH8YvXGdLANpASPbQkCNRDFuPYSQ/DxqiOl+e4Vt2rwHNOmQBlk0efbjPYw6f9ugBgnff0NdLSrgXfb+Ev4SZ+Gl4s4S7Qy/hge4tMvVKkgoZjIbfRPjNhF8W/ObC7yb42eA3Dn558CP5y9Qy32VlyobhZV51hTLXY5nXsjKfgAyegt8z8HsWfi/A72X4vQK/32NZ8NuJTzxKLp3CMWxlhjTjAra3yTsKOZEJkENlodEtqM6XhWzN8KTxDyrxb7pk/NuV+JU0vurbTHrMgOpcmt8u4/1F9P7Tk0kODrklufPnsVuSk/fi62y8vUi76pjYJclUj36VC9gmH9q/THMrhpUy93KlxO9IrlRLcUnfff+iUrKHlrJKWwq6ScFrQ2dwgtOuCqQJ3C7H7FW2dm8Kho1A628hSJmjQ/8mTfFUR88NZWRMO7rc5pjtTXVh+Gm0JhdmDoboNZ8SclYS1+p0DW7zW+g2h9t1tNyX5uIRvznF6NH+kLQBM91VMsfW6B2H+P4AMuHea8LbncJI9OeIMguGjJjnceKYRV0eTcN/4/AfbTgp5QI9MvQP2eEtayoLccBHZSE0lHfFVMtiqe6Op3qNpsITvTVmPSTmE6QaHeOYRpzva7IIT0A1AiuyohVGxzT16/v/AxnF7/nE8lml
*/