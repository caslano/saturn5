/*!
@file
Defines several `constexpr` algorithms.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_ALGORITHM_HPP
#define BOOST_HANA_DETAIL_ALGORITHM_HPP

#include <boost/hana/functional/placeholder.hpp>

#include <boost/hana/config.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    // Do not call this swap, otherwise it can get picked up by ADL and conflict
    // with std::swap (see https://github.com/boostorg/hana/issues/297).
    template <typename T>
    constexpr void constexpr_swap(T& x, T& y) {
        auto tmp = x;
        x = y;
        y = std::move(tmp);
    }

    template <typename BidirIter>
    constexpr void reverse(BidirIter first, BidirIter last) {
        while (first != last) {
            if (first == --last)
                break;
            detail::constexpr_swap(*first, *last);
            ++first;
        }
    }

    template <typename BidirIter, typename BinaryPred>
    constexpr bool next_permutation(BidirIter first, BidirIter last,
                                    BinaryPred pred)
    {
        BidirIter i = last;
        if (first == last || first == --i)
            return false;
        while (true) {
            BidirIter ip1 = i;
            if (pred(*--i, *ip1)) {
                BidirIter j = last;
                while (!pred(*i, *--j))
                    ;
                detail::constexpr_swap(*i, *j);
                detail::reverse(ip1, last);
                return true;
            }
            if (i == first) {
                detail::reverse(first, last);
                return false;
            }
        }
    }

    template <typename BidirIter>
    constexpr bool next_permutation(BidirIter first, BidirIter last)
    { return detail::next_permutation(first, last, hana::_ < hana::_); }


    template <typename InputIter1, typename InputIter2, typename BinaryPred>
    constexpr bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                                           InputIter2 first2, InputIter2 last2,
                                           BinaryPred pred)
    {
        for (; first2 != last2; ++first1, ++first2) {
            if (first1 == last1 || pred(*first1, *first2))
                return true;
            else if (pred(*first2, *first1))
                return false;
        }
        return false;
    }

    template <typename InputIter1, typename InputIter2>
    constexpr bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                                           InputIter2 first2, InputIter2 last2)
    { return detail::lexicographical_compare(first1, last1, first2, last2, hana::_ < hana::_); }


    template <typename InputIter1, typename InputIter2, typename BinaryPred>
    constexpr bool equal(InputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2,
                         BinaryPred pred)
    {
        for (; first1 != last1 && first2 != last2; ++first1, ++first2)
            if (!pred(*first1, *first2))
                return false;
        return first1 == last1 && first2 == last2;
    }

    template <typename InputIter1, typename InputIter2>
    constexpr bool equal(InputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2)
    { return detail::equal(first1, last1, first2, last2, hana::_ == hana::_); }


    template <typename BidirIter, typename BinaryPred>
    constexpr void sort(BidirIter first, BidirIter last, BinaryPred pred) {
        if (first == last) return;

        BidirIter i = first;
        for (++i; i != last; ++i) {
            BidirIter j = i;
            auto t = *j;
            for (BidirIter k = i; k != first && pred(t,  *--k); --j)
                *j = *k;
            *j = t;
        }
    }

    template <typename BidirIter>
    constexpr void sort(BidirIter first, BidirIter last)
    { detail::sort(first, last, hana::_ < hana::_); }


    template <typename InputIter, typename T>
    constexpr InputIter find(InputIter first, InputIter last, T const& value) {
        for (; first != last; ++first)
            if (*first == value)
                return first;
        return last;
    }

    template <typename InputIter, typename UnaryPred>
    constexpr InputIter find_if(InputIter first, InputIter last, UnaryPred pred) {
        for (; first != last; ++first)
            if (pred(*first))
                return first;
        return last;
    }

    template <typename ForwardIter, typename T>
    constexpr void iota(ForwardIter first, ForwardIter last, T value) {
        while (first != last) {
            *first++ = value;
            ++value;
        }
    }

    template <typename InputIt, typename T>
    constexpr std::size_t
    count(InputIt first, InputIt last, T const& value) {
        std::size_t n = 0;
        for (; first != last; ++first)
            if (*first == value)
                ++n;
        return n;
    }

    template <typename InputIt, typename T, typename F>
    constexpr T accumulate(InputIt first, InputIt last, T init, F f) {
        for (; first != last; ++first)
            init = f(init, *first);
        return init;
    }

    template <typename InputIt, typename T>
    constexpr T accumulate(InputIt first, InputIt last, T init) {
        return detail::accumulate(first, last, init, hana::_ + hana::_);
    }

    template <typename ForwardIt>
    constexpr ForwardIt min_element(ForwardIt first, ForwardIt last) {
        if (first == last)
            return last;

        ForwardIt smallest = first;
        ++first;
        for (; first != last; ++first)
            if (*first < *smallest)
                smallest = first;
        return smallest;
    }
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_ALGORITHM_HPP

/* algorithm.hpp
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
*/