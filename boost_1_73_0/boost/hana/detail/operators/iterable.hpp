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
qlorf1+NKDUtqmXLzqM5c7mKMpuO205NSUQ67TPMxu/iN+se4RIBWRNRwrdJp5jA7YiQnmolIoz4e7TMEKoO7vKXVOPXq3BX9uMo7ULyObSt1AU8/e76Sq/q69hwDiPXXM41RbIMsV/1xC6S2EFP7DMHi12isVOdN/qtAHbmV0rn1QHooTd7znCLEfp79Fnpv+Vwv2TcpXAvWxJbfv1CXXwvvN65dtk7wbRWT1mFu17Hob8k
*/