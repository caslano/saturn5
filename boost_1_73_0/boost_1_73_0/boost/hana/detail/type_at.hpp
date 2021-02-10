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
opzEm/bwUCRk8YYidfnwozfZ374zeJAAH5Kcenv2qmkigcBgMJg3BjzYfbzPFtklaz82+9+GD/zLRlzE0T+om9b3tu2vhP8Ho36Df9dNckCKIV/tNlk/5CtpsSG2mOU1frftdRP9hrjhXwc48jcbv0ILDMORvWh5H/vX85S0em3y4vD5C7KP//zUIedO7JJ3EY2TLzTskNd+OIt+WUDj/lw0dj16XA+Ejf5CLCfwk2kW38NwGPmlm8iGX+bLrhstGoYzHF4875ATJ/RpQKyUhlMaXwMYj7X8Mnfu7roJPe4QmhIn6IrlTOZ+QpJolt46MSXwPfBdGibUI05CPJq4sT+FH35I0jklMz+gpDe6uOoPzzrkdu67cwRyH2UkmUdZ4JG5c0NJTF3q33AYSydOSTSD4QDc85MUAGapH4VdmJuSlMaLBGHg9E6QRMS5cfzAmcJETkrmabpMXh0cuFkcAPYHXuQmB65cfneeLvKVXAESC+eeRMuUpBHJEtoh2LNDFpHnz/BfIAg0LrMp0HTeKbCBqULvIIpJQoMAYcE4nyYcbUosQZ4OdiNLwNhP8Z8kChOc6nYeLbSOQEeEMsviECYCOkAnLwIyd0gWejRmndnK5RSCpozAjVtT4OuRKARkyLZhkb61TaZO4icd
*/