/*
   Copyright (c) T. Zachary Laine 2018.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALGORITHM_FIND_BACKWARD_HPP
#define BOOST_ALGORITHM_FIND_BACKWARD_HPP

#include <utility>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

template<typename BidiIter, typename T>
BOOST_CXX14_CONSTEXPR
BidiIter find_backward(BidiIter first, BidiIter last, const T & x)
{
    BidiIter it = last;
    while (it != first) {
        if (*--it == x)
            return it;
    }
    return last;
}

template<typename Range, typename T>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_backward(Range & range, const T & x)
{
    return ::boost::algorithm::find_backward(boost::begin(range), boost::end(range), x);
}

template<typename BidiIter, typename T>
BOOST_CXX14_CONSTEXPR
BidiIter find_not_backward(BidiIter first, BidiIter last, const T & x)
{
    BidiIter it = last;
    while (it != first) {
        if (*--it != x)
            return it;
    }
    return last;
}

template<typename Range, typename T>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_not_backward(Range & range, const T & x)
{
    return ::boost::algorithm::find_not_backward(boost::begin(range), boost::end(range), x);
}

template<typename BidiIter, typename Pred>
BOOST_CXX14_CONSTEXPR
BidiIter find_if_backward(BidiIter first, BidiIter last, Pred p)
{
    BidiIter it = last;
    while (it != first) {
        if (p(*--it))
            return it;
    }
    return last;
}

template<typename Range, typename Pred>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_if_backward(Range & range, Pred p)
{
    return ::boost::algorithm::find_if_backward(boost::begin(range), boost::end(range), p);
}

template<typename BidiIter, typename Pred>
BOOST_CXX14_CONSTEXPR
BidiIter find_if_not_backward(BidiIter first, BidiIter last, Pred p)
{
    BidiIter it = last;
    while (it != first) {
        if (!p(*--it))
            return it;
    }
    return last;
}

template<typename Range, typename Pred>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_if_not_backward(Range & range, Pred p)
{
    return ::boost::algorithm::find_if_not_backward(boost::begin(range), boost::end(range), p);
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_FIND_BACKWARD_HPP

/* find_backward.hpp
pQTX3TWjXHcbo1FKMxCwQ0Z7unU1HuV1M5jyZ/+DRktKTtcggNHemcFwkkegBR1zDNz3EyN8+4vRP2phqaU/VUot4Obpn8jL9kbdW4n+LECyG71e9dYpuwagAGy7sPtZfeROGvTD8+Wc4FTqx6+MPe2r1d8Rc5RskP8jahgIbBOGMHbrduKBL5R0Ph9IYNoYUV92dUiKnJvSC+GZOzRnma+jYyTHsmrImXZ4pZEZuH0xjnU4J0YkCkg24Tb8ZLAoV0+7bl+5huY103s0RvLQbdrqC1YmJGDbpNgaXEM7gG6pyHijXUiBmiV+xRs3KHzJFFRvNwRqJ4qVpRe3E9bk+HMbSkT9Bbj2noJRPnBB0n9z50IBVn2BPsseXvyubEYL3Ocp47zX9DbgVtXdPVo0PL7zrUrOSsFAMZ/OZaUQ5aT9tBsBfs3OvvB7YSGITYBa8NU6WnCsWh/uOSCQnoiIPdbRXAhMm3Zr7SMKPNhSVHsXnbrZUVlq99PGKzUyME1CYwX3dZ3kagphVnHKH0bBQNmFCHf8/tEyzE84Io/dn7//HBfxdJNKRukiUg==
*/