/*
   Copyright (c) T. Zachary Laine 2018.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALGORITHM_FIND_NOT_HPP
#define BOOST_ALGORITHM_FIND_NOT_HPP

#include <utility>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

template<typename InputIter, typename Sentinel, typename T>        
BOOST_CXX14_CONSTEXPR
InputIter find_not(InputIter first, Sentinel last, const T & x)
{
    for (; first != last; ++first) {
        if (*first != x)
            break;
    }
    return first;
}

template<typename Range, typename T>
BOOST_CXX14_CONSTEXPR
typename boost::range_iterator<Range>::type find_not(Range & r, const T & x)
{
    return ::boost::algorithm::find_not(boost::begin(r), boost::end(r), x);
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_FIND_NOT_HPP

/* find_not.hpp
wzsyHtEfGaVf5dY/ox9BWLv+aFJxJCjIXDsDTJGyW2EPcSs/P9rG7yQnG3gMFACZT7uqjAtkPVwIc6uVTAmGh0lTsfyj/Km1YpyUdE0JNKnEvDeu8EvSNsnz/3Qi312OHDVFcKgbjp7H8NKOzHVc3jLxccz0V8kv3vMj+e2LklNYjcob1JrM2pHlDTIcoBmRT27TEaHdcrFshgJkiXz8XiLj5w2p4lo8UBDt9rkk0Nj4g6aeeh+JN0fZuSeOdiZIJ7em3neHmseO5q7GXa/2SCfAYV6eaLQ7Z9vvC910Eu0eQ8dF3m2O5jfw3yCrt7wuczf0LTv6/OoVJ9xgw0gSL2iAg39ooDgqVrwRnYzbRiXAp0miR+xyresh7wPbSaKACvgttEOEXSvh/czLk42TljN/fdRPA81anBgZBgE5Ei0OxBADcXV5xjZelCF2vsi9KI0VAZ8uQZbUpxnl/vMvxJ97LAnwGvJgVZ/UjZD76RJvU5WRq23dyCnC84y5/aq33jwvDNMaBPjL0T69u8YeX0V6ZoZvRksVgyvK1jupw94CNNEoup/5MJTRL3hVQcRHlwbCcwG2vMybc197D2jmLw243G6GbHmlRTt8fbCb0usvkIzy5YqlUrURw3/5HIvsivUsjHjbge6KssNUNNOpRP2N8gM0n954Aa+LEpXr4wcxBIYLvvvcQLzYqpGfN4zcBT6hyjrp83N144xx
*/