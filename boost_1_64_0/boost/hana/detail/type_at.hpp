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
pOB9D0ppdpLbfV2Bcs4EXfpDTKwc/6ViAq4EGBKdgtzj+beTiswjIPTU9l+LIgZGpn0mh2I12/JBvyKYQaMH0s2DUf9XWeaKNBxOzdbfzGkeZtimoJ5N+E+33FkDpT07z50VF1joV+ob301IvETXrcWtGQcg94ZUh2ajUdO+Jq8OHeuvM9zbmdfsiIpqzol+mW2pjqMgJKd1YRK5+sMw7bMkDkk66oUpi8nIwwQCpMZkaTGChzB9k9S0KBhLKwRJwzr1OppZZEInGPfG8JQXCExcRr7BT0+CmmQKXIRwZiB5FeTQJHZaLUfFF72cSrbA+Y2du4FfP5IfwN21GH1vv72oLBoDE0Jg0qcmx6f7F7Q+I5WA2eP0r5WXwQTrgeYmq5Vv+g0bgDD3FUy961nDFCQcAX5jMrwbT+pQwECyI50S/BOZ67xi5ChlEDR+8+OFeAlBlt3QOc7K0GLHO9YaqqABRov8+E0j8DKhUM1Yq1nfY7Zh/OzaR3bQywD7vemHiKtbc1xBAob54I8TdMmqSVUGHWJayHVKjGoz9qnri3mPXAZ0KTeOa0KjTg==
*/