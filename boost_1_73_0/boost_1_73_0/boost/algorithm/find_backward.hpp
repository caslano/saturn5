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
ydE1BlsyUeAJaU++dmSuNCMNTfPcQ1zXShDNS53CbPRVLP72zUqak/hhV/+FfvTEVzcVR6cYR1SrIMz9Q27zwHoPI/N1cjwKyrmQ5v0Xh4tQxU5UY+FWnMA+3r/3xL0xieeIe6h/j4fcXC3dAaCpEBIWNwo63suUR96Cm4xk1LzdFuPm1ZCbAn/CoGCJj8jNB/cfDIwUbA4Jr6nkmk2MXn+geu/Jo8UJDpqlTVkWGf5KFS1njlcdPnnxzBzJTt0=
*/