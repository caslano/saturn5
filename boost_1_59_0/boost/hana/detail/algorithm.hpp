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


namespace boost { namespace hana { namespace detail {
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
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_ALGORITHM_HPP

/* algorithm.hpp
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
*/