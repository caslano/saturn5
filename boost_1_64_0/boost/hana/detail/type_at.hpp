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
3gHwp9OcfIQoS/H5vijrTCb/EULnP2B79Bidgds7iCGpu3LnbCMX0d8r9n/n2DbQONBAJnm2Dh+1oRPvAiCIj+6CSXadaH2u3cgHMM78dJ6Xib+qWyM+YWrD1YSvs+siVo5dsxg/Jj6B66dJzkW2zprnVOGXuBj4ZcDX/BdkKoxYrhrnZ+B7CMqd/D8o11/2ZOdS4c/6oIrwAWNKwRaL/v0L5Od46TO8gvhjbPh8H6uF3+Yq0Mmxc7UYW1GB/7UoGzQ+/LVijBxfGdynC6JPX8/2IMDR+yfSp1iT3yhkkHEyf2fGB+FfZm3Ky7xZ7E0Koq63Mj6rqC8oXE6Ms9uJb1icz95J9oXvbwp0n4rv3+4me/QHtkcYDMl7X9Af8OyMGzS6/PtEPQZFPR6weI17WeAfIvkBp7vBfGx8tnGBD8o042PDY+NRsceCLFY26ftdFVCXJ+2ezOIhN9cX3jFPckaw5im91nDfcIv2XS/ecCOt75Qy/a8PeKP1IpOP39fals2Lr4j5/1Wk+d3W1yj9HP4b37ON1S7a900jD+GkDv/E5rz14t7p26J93qR9qLnPMwvrT34HaDLSvO9JW/a+sBcv2PMEc06m8Tm6d/Y3YTtfI9u3r0gbfo+G/OkXjW1lZ/lcnn8w3TwSYFv/KfS+JMTKF+/ZFhe5Rz+qxn/fQ5YxBng97jWPV8PB54Bja3hZGi/LGmfKIhqpz/GMx3kR42PiazzstWvYWlHMT6sC2nRzoke9aMxSfey99IB6oz6VNYxvgF2vAl6uUesCzlEn1rD+K/rXJFbGywFry8msjFUl5o4vGD6ktzOFDrZmeDNncJ/ftsDbfmPH62ik/Wfsa6q1vupq9Hd5P29qjeg7bB7F3FxyHp1W4583HhF1mA78U85n8SklO5pc1xD3KcGNu6uiMf6kjpbkbJ0ea9Op2cx3b2D1BjZO+zWSC33++2Si3eG++8WO+r4J7evbYwlANH5TTe/utTejvfaMmpHvtY3P7V3YtqJxckVMCh8EjDZw39cN2x9vXxBLuLkD4LTvnlmj+wuzuaiRfmf2ReDs3VqiU/CZDL5rjX9e2a3GP152Z30EOGs/LqE7nXuwsbZLjX9u2JPS9TXD37XVE+5Beo/0JTbuACv6Hm2fGm/PtSetX3NIDCFdq/+zt+3lzrwaPa6iNcPftTRweVGXRlNX4j1GjNkY8WoO4DVfjMMFQheP0DoGfH1p6Myek6m2eZ/HThZt01rjz9NW4/drXxoxdbdpa9vRXoHvXZLgsXj8ZxnjQedz8F8y32mZ8HmONTQOH+PK9bg/HJx8jDfFCMbHufWljrdpFUMkFgfhe3bMAwQMymRjXsScn8BgIO9oxHVGg9uM4Qx3vx+5cVESVfD7kVX0DlSM5AhZGDm8fb7kpvj8WNKKRP5kCzc5mF8ZTkLUKcl9y52tBmrkmKh12WRVx/3MgEPNPvgk0nND53ybxfM5u95l5m+OJhvjcTgtmx3P39yqXtjFEtQmXyAYVcvnb4aL1/pRtyaY+s0ev7+5Fa3QEW1coPNuS7DkIsRTa4y2g5b5nBvirdGEbc8pxh9PPuE6yot+YPUzlWBQJ6Ru9el/O4NTQom+sr09V9Z1n0a0GgIa64NW6om1tRBsujh73lH3zQTc8lCbruMMA4u2WN/7TgbWHE8kiW5nDWvkY+uL5sxBO7i53zkKiPA3Q4FR7zx7FsmmoTrvbAvz+NXrvFphVO6uCkaVUOnd6KyjEeMILeDCdvfD7Hn7HJ13SSLuHqgsaUvo9tpD91HTMh37t+v+P1fXO9pKfvU9A85i9tL9tc2k93bTzfCq6zxfsudSsUZThy9b+xGzfXAfsh2YZN0=
*/