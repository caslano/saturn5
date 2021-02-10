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
ToJb+hBd+ojJ0xgAeviZPs2C8bUfXCTxdJUC9IDs9JmGAX9JwpQNffKvGb5nKn7X6lol0zBc8K+KCv2WEExhqIJSclTfAZHB3+hpS1RTlagc/bSTic0O5qkZHjIq0e0bk8OGE+AJDxJAsIhapuHm36speX5VV7A9puTtiudUpVqd6b8lqrVob12bM0TtSDkDarARoOLfzvqjdmv3HczTt/5ogA+J7J6TUIvmkJuJJpZl78ww3/JY6mAd1+idm6TRFL1AZF7hi5GBRRLlXr/3CjYQ7HK5+N77dIgIzJfxJQw+qtpJurq8xI80hfA4lIZp1zttD7r7HozylA0GO+RHc7hKlockuIcX0fwQk/kb/mWlenvZC/NIbc+sYrjr9Qb916/3vSvmh/6bq2wNYSKh2YnIyY0+mjGf0ONPWw65Rj48JA0B9DD+Blh/htZNdKlm87bLvnQd36Aw4CHWE9mbuC54i2kADKbh59S7XMYzWAfwAP9KSOpJswc7+FG9AZ/rtErMeX6yx9llHKOvGbHv7XBm+3001dBfoKGyvD5Z9TomMS0Gd6mnQk1ZXXW3qF+CYhtm9xma+jNA1Lfoa/lEHwujG4t60TiStqoUrSl7hsiVlTIqoeKEPSPuGPUCJ9Rr+kOd5DCuzSglOPt4
*/