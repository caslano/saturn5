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
avXwV7YQxt9DiuS195P6tPtl/VwqXmYE8yTzbDLvF8k8jOuzXzu9h2Swq/E1fZo/qa3MF8Y961Z9Xy+ZH4xr+LPL/iBl8do1f2j6WPKSBOO59+pRPFBqgBm4Z/uOSq8ztPvlNj2q+okHM77f+ZWOLjI/mCfPvduuqcpCYDXJgnYFyfzitGtuejvQQlmids3nh+oPkBpg1mR9R5mbSg2wMmSfl/+aIhmEcV8GNc38/t20u/GzNPabv0MyCONrTtnxq7vUBzMnW+B2dqOyMBi/6zZsvhGhLBxWlKzy2CLDlUXCCpNZDk6zlFzD6tL9EjruqirZhfFOLyn5dJSyVO1ZhlSdnCz9hFnwNf9a1F/6qdX34fpCeZefg/E72Wx+UhHZB+3cqcDzrsoea+eGrOpboKxAO2eyPtJaZtTD+DPutunzF8oCYTy/L8MvbJY9gvmS7W67Xt4FMdo5x3/52ytL0M5FVguaK/3UnsWpbS15z+do17Ra5/dPZfmwymTO1kMsJGdRxp850/683UdZEIyveXfixZqSJRjnus25cs+kPhjv0enSNhWVJcFKkhWsrLRXWQrMm2yo1St5zmztOf+1xWem7BisLFnV3CHdZH49jX9O3dzV8ndlTjDO7o6D9X2V+cL4flNbLbKR/YM5kb15UuVv2SNYaa7vVC9HZXGa5V6yPKpsIYzz2du3l53sGIw/q+IzL6+Wnml2LrTbPsmLZt7/9B+rLB1moM/3ovuuNJBea9ZmntlZ2TGY6vW3QHdf30KZSS/sNJnhWTXJvAFmQzavSZ3C0muYI1mH2t2bS69htmQrLzgdl15r57oPtLolGYSZkfV5kllWWTxM/fvzXy3l/LkB0heYJ53LuRcWJznT6quyt5rkrABWhuxeudj6krPe+OdVZL89zeyqLBBWkqzohXtiITA7Mouo6jWkdpi639fd/hJ4QuYeB/Mm61HvxUnJEsyFrKaz6WxlB2Dqff3Vanc7L+fSYa507uYJm7vKrsKK07mpcwvmSM9gfnIOFj3ksjL7PsbnLKsnBCtzh5Xl+lbb3pO+wEqQlRtYqa+yMFhhuubc5fd2KwuHBdA5u7Knf5VMwMzJlsweJPdLhJUjuzqxv2QpTTsXXPrJdWUZMCuyesvv+inLgVmQ9Rv4j+HSM62+vDpNDJIz7Zqffu/xizKzvsazjQ0/sl92DOZONrtlP7lfOEz9Gb+vtu3RIdnbZBjXZ+ocLu+sVJgP2d061iZSH8yX7NTef6nvnyjWOJ83La/3k+eElSdrXXl9R3lOmBdZtM/sDpJ5GOfMN+f+FWUpsNpkSZ7pPZTlw8Ko9uX2dW5Lzvrj3+XnDNr2LZC8wGqRWZWZ+6NkAsZ5+THowkpluTBLsqy85DLyLLAKZA9S2q6VfYg27vXnxi1ilIXCSnGv2y6XfEbBDGSXbKuuUxYD8yBL6HS0krIkmCfZmmY2scrSYc5kbU3fvZf6tGeJzvVOlexqzxL1e5LMwWyA8dy7H8+dqiwQ5kRWNqzmDskErAHNz/bKjO5SA6wynTuUstFadhMWQDbKbkZjec4BWu1LGz+QOQzEzxZkji2nH1YWCXMlK7I7tInkBRZCz/lX7cmNpJ+wQDrnkn72qGQCxv0M/3lNkvRsED7/yPpn5sk13WH8LMtO3D0huYa5kW1LmzFe8gKzI7N+uLuu7BjMhizMw2yDskRYWbKR68c+VZZK1/za877r0zvKHGBmZGMOpM1Ulg3z5HOOBhdlr2Dq+9JXG5QRHKHMZDB+n0XnGv620VaZE8yKbPngntJrX1hxuubLfMuBkkFYaTr3aH7VMZJBmDmZ1cfL1aWfMFuypyeLVpF+whzJ3hxv2FI=
*/