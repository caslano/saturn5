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
jxHSZMuuA+mWD/o/OX2pZglaWlGsQb5/RKsMPoybNkC2oNAqkBPX6lQugEelVnZqJDrRQQvOml1y7n65ZX9/ubp02Pwr+FQOBrzm4ctKYSradxN6V7E4tqc3+ZDzQPFO1JiM/nBq1gyyBz8zzMCamyHnYXtAh9dsdJvNXhlGkzjX7uhg6jEypvPfhoNkXXUdNCZrIgdVITNXsErjWfAxxLP23QQWrBNUY1sdxOnNrsEfNeuz3a7Pz8zNAL1cmyC6Lkrtk1ftVqvdogyS4E44uwjRXdEPlmGCFMk3Rb8kQc2DDZOfxBZvhSQaBvC++gpnjszPrfeTa6A4cdyqoG7FZ64Q1yIiInQq5l8+ERAtdKPVnldnnW4LWytVVNWeHAFnm8gzGltMzcB0xZ7WmzCLoTp/9HaAR04tXBP63R/ag61MCT4MFXP3tD/svPP4dS96Rrv0+WuUHqOE8HnA38MJOj7EU1g62HMKvbXY23Z3IbK7vLR41Boyywfdx5jRjbieYla8K49znRzsOZ23RKO1utQdFoM4Gn/PPeGNxfyhV45yxLLXaumb5YlbHZK+UoqUy1BumVcOWbmyt5l7LRVGNchDPUd+NQnhjC6ghEkyhQ5R6ZAcbZq4K8hsuFWwM7Z8185+DVrmzD8pWphR
*/