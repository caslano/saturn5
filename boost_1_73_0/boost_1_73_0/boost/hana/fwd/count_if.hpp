/*!
@file
Forward declares `boost::hana::count_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_COUNT_IF_HPP
#define BOOST_HANA_FWD_COUNT_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the number of elements in the structure for which the
    //! `predicate` is satisfied.
    //! @ingroup group-Foldable
    //!
    //! Specifically, returns an object of an unsigned integral type, or
    //! a `Constant` holding such an object, which represents the number
    //! of elements in the structure satisfying the given `predicate`.
    //!
    //!
    //! @param xs
    //! The structure whose elements are counted.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! structure, and returning a `Logical` representing whether `x` should
    //! be counted.
    //!
    //!
    //! Example
    //! -------
    //! @include example/count_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto count_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct count_if_impl : count_if_impl<T, when<true>> { };

    struct count_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr count_if_t count_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_COUNT_IF_HPP

/* count_if.hpp
kCXXSQCuQ3nS8/9qP87CiR94+re9Xhl+4NVoc9J0m16T1clxiX4Ec+8foim0AHKrG7zfpi0c4TXtaYky0iP4qvR58QC9h3JL2oZad83lfvtZSFYPz2eDozWPmvHWVbNkqnqJsCUBYfM1TmlMqCQquYKT0iZXHPQ3xobt/00KPfp/UEsDBAoAAAAIAC1nSlIEkfAMQSYAAI6QAAAeAAkAY3VybC1tYXN0ZXIvbGliL3Z0bHMvd29sZnNzbC5jVVQFAAG2SCRg5T1rd9u4ld/zKxDvmURyZVm2p2nHnmRWkWVHG0fykeRJ0skcHpqCLG4kUktSfrTJf9/7AEiAD1l2Mm33rNuJLRK4uLi4b1xAu9vf7+eJ2Bb3/jj0nwM/8Jt6nEfhf0svKW/tOF8E/w96fYLf9w2yK7IuX5y6uL/LF1GjLo4a5Wf823HuG+gT4ob/7GLPTw7+CU+gG/bshMu7yL+aJaLWqYu9n376q9gR+639vYY4dgNfzsUokcGljK4a4ucJPfnPmXt724zlq4aQiXDnTQVqPPNjEYfT5MaNpIC/574ng1hOhBuLiYy9yL+ED34gkpkUU38uRWdw/rHXP22Im5nvzRDIXbgS8SxczSdi5l5LEUlP+tcMY+lGiQin0B2AT/w4AYCrxA+D
*/