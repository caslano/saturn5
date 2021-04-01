/*!
@file
Defines operators for Iterables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/at.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Derived>
    struct iterable_operators {
        template <typename N>
        constexpr decltype(auto) operator[](N&& n) & {
            return hana::at(static_cast<Derived&>(*this),
                            static_cast<N&&>(n));
        }

        template <typename N>
        constexpr decltype(auto) operator[](N&& n) const& {
            return hana::at(static_cast<Derived const&>(*this),
                            static_cast<N&&>(n));
        }

        template <typename N>
        constexpr decltype(auto) operator[](N&& n) && {
            return hana::at(static_cast<Derived&&>(*this),
                            static_cast<N&&>(n));
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP

/* iterable.hpp
cFsqXokWz5INMXJmmANlTMn0Zehbn2WkQIYVtihFkQMjM8Ek54nqHWytvH5btsSKork+dIimeeSLTuI5kCNTSNodQJGyEC7pKel9M1VI61Er1khpRyuzMym/ozpXlYsTbL8rM2Qze+nRq+3SwcYd/jXzifu/iBbmQLPRtdg95A2YfU5gM6kgaFP0yJVbe8rUb70IWYvy6IJm+3FG8t983dZUr1bnlvpOGQ11SglzVGLnMrcYJchPgPc1grcGyNK4U0hI2Jb42cL1+TMmc3F9974SOIntbjf8EtbcjYdWt5/bzIDroth4shLuELhWqjdGM3ZuGbJ+TGpRwB1o4sDrYT/MLnPXvdfyq2hGv2vdzN4HDdWl4j2SUEXHu9BjT3ogYexBFFbYAx7MeCn+LwFhvBYMGQWBPm4ZYXVWR4vmJvIRu2YxxQanllSfx1ZMhtbqQUsFtUObMJOsifU3FKmymP9vV94UXML0WW3+kmctApSfSK/OykQr/dcSDsePGsWOgZr2MCO/+xjOLfrui61zPn/nRTceYD3x33A5mjuA95mnNs3Sug2qRxKDhQ==
*/